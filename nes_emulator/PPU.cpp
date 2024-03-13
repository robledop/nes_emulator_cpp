#include <cassert>
#include "PPU.h"
//bool PPU::get_ppu_latch() const {
//  return this->ppu_latch;
//}
//void PPU::set_ppu_latch(bool latch) {
//  this->ppu_latch = latch;
//}
//uint16_t PPU::get_ppu_data_addr() const {
//  return this->ppu_data_addr;
//}
//void PPU::set_ppu_data_addr(uint16_t data_addr) {
//  this->ppu_data_addr = data_addr;
//}
void PPU::render_background(SDL_Renderer *renderer) {
  this->draw_tiles(renderer);
}
void PPU::render_sprites(SDL_Renderer *renderer) {
  this->draw_sprites(renderer);
  SDL_RenderPresent(renderer);
}
void PPU::draw_sprites(SDL_Renderer *renderer) {
  uint16_t sprite_pattern_table_addr;
  if (this->registers.ppu_ctrl & SPRITE_PT_ADDR_FLAG) {
	sprite_pattern_table_addr = PATTERN_TABLE_1;
  } else {
	sprite_pattern_table_addr = PATTERN_TABLE_0;
  }

  for (int i = 0; i < 256; i += 4) {
	const uint8_t sprite_y = this->oam.data[i];
	const uint16_t sprite_tile_index = sprite_pattern_table_addr + (uint16_t)(this->oam.data[i + 1] << 4);
	const uint8_t sprite_attributes = this->oam.data[i + 2];
	const uint8_t sprite_x = this->oam.data[i + 3];

	this->draw_sprite_tile(renderer,
						   (uint16_t)(sprite_x * PIXEL_WIDTH),
						   (uint16_t)(sprite_y * PIXEL_HEIGHT),
						   sprite_tile_index,
						   sprite_attributes);
  }
}
void PPU::draw_sprite_tile(SDL_Renderer *renderer, uint16_t x, uint16_t y, uint16_t tile_index, uint8_t attributes) {
  const bool flip_vertically = attributes & 0b10000000;

  if (flip_vertically) {
	for (int i = 7; i > -1; i--) {
	  const uint8_t tile_hi_byte = this->memory.data[tile_index + i];
	  const uint8_t tile_lo_byte = this->memory.data[tile_index + i + 8];

	  this->draw_sprite_tile_row(renderer, tile_lo_byte, tile_hi_byte, x, y, attributes);
	  y += PIXEL_HEIGHT;
	}
  } else {
	for (uint16_t i = 0; i < 8; i++) {
	  const uint8_t tile_hi_byte = this->memory.data[tile_index + i];
	  const uint8_t tile_lo_byte = this->memory.data[tile_index + i + 8];

	  this->draw_sprite_tile_row(renderer, tile_lo_byte, tile_hi_byte, x, y, attributes);
	  y += PIXEL_HEIGHT;
	}
  }

}
void PPU::draw_tiles(SDL_Renderer *renderer) {
  int x = 0;
  int y = 0;

  const uint16_t bg_pattern_table_addr = this->get_pattern_table();
  const uint16_t name_table_address = this->get_name_table();

  const uint16_t attribute_table_address = name_table_address + 960;

  for (uint16_t i = 0; i < NAME_TABLE_SIZE; i++) {
	const uint16_t name_table_pos = name_table_address + i;
	const uint16_t tile_index = this->memory.data[name_table_pos];

	const uint16_t pattern_pos = bg_pattern_table_addr + (tile_index * 16);

	this->draw_bg_tile(renderer,
					   x * (TILE_WIDTH * PIXEL_WIDTH),
					   y * (TILE_HEIGHT * PIXEL_HEIGHT),
					   pattern_pos,
					   attribute_table_address,
					   name_table_address + i);

	if (x >= 31) {
	  y += 1;
	  x = 0;
	} else {
	  x += 1;
	}
  }
}
uint16_t PPU::get_pattern_table() const {
  if (this->registers.ppu_ctrl & BG_PT_ADDR_FLAG) {
	return PATTERN_TABLE_1;
  } else {
	return PATTERN_TABLE_0;
  }
}
uint16_t PPU::get_name_table() const {
  switch (this->registers.ppu_ctrl & NAME_TABLE_ADDR_FLAGS) {
	case 0: return NAME_TABLE_0;
	case 1: return NAME_TABLE_1;
	case 2: return NAME_TABLE_2;
	case 3: return NAME_TABLE_3;
	default: assert(false);
	  return 0;
  }
}
void PPU::draw_bg_tile(SDL_Renderer *renderer,
					   int x,
					   int y,
					   const uint16_t pattern_pos,
					   const uint16_t attribute_table_address,
					   const uint16_t name_table_pos) {

  // https://www.nesdev.org/wiki/PPU_scrolling#Tile_and_attribute_fetching
  const uint16_t attribute_address =
	  attribute_table_address | (name_table_pos & 0x0C00) | ((name_table_pos >> 4) & 0x38)
		  | ((name_table_pos >> 2) & 0x07);

  const uint8_t attribute = this->memory.data[attribute_address];

  const uint8_t attribute_shift = ((name_table_pos & 0x40) >> 4) | (name_table_pos & 0x2);
  const uint8_t palette_selector = (attribute >> attribute_shift) & 0x3;

  const uint16_t palette_base = PPU::get_background_palette(palette_selector);

  for (uint16_t i = 0; i < 8; i++) {
	const uint8_t tile_hi_byte = this->memory.data[pattern_pos + i];
	const uint8_t tile_lo_byte = this->memory.data[pattern_pos + i + 8];

	this->draw_bg_tile_row(renderer, tile_lo_byte, tile_hi_byte, x, y, palette_base);
	y += PIXEL_HEIGHT;
  }
}
void PPU::draw_sprite_tile_row(SDL_Renderer *renderer,
							   const uint8_t tile_lo_byte,
							   const uint8_t tile_hi_byte,
							   const int x,
							   const int y,
							   const uint8_t attribute) {
  const bool flip_horizontally = attribute & 0b01000000;

  int rx = x;

  if (flip_horizontally) {
	for (int i = 7; i > -1; i--) {
	  this->draw_sprite_row_pixel(renderer, tile_lo_byte, tile_hi_byte, y, &rx, attribute, i);
	}
  } else {
	for (int i = 0; i < 8; i++) {
	  this->draw_sprite_row_pixel(renderer, tile_lo_byte, tile_hi_byte, y, &rx, attribute, i);
	}
  }

}
void PPU::draw_sprite_row_pixel(SDL_Renderer *renderer,
								const uint8_t tile_lo_byte,
								const uint8_t tile_hi_byte,
								const int y,
								int *x,
								const uint16_t attribute,
								const int bit) {
  const bool is_lo_set = tile_lo_byte & (0b10000000 >> bit);
  const bool is_hi_set = tile_hi_byte & (0b10000000 >> bit);

  Uint8 red;
  Uint8 green;
  Uint8 blue;
  const uint16_t palette_base = PPU::get_sprite_palette(attribute & 0b00000011);

  if (!is_hi_set && is_lo_set) // 1
  {
	const uint16_t index = this->memory.data[palette_base + 2];
	PPU::get_rgb_color(&red, &green, &blue, index);
	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
  } else if (is_hi_set && !is_lo_set) // 2
  {
	const uint16_t index = this->memory.data[palette_base + 1];
	PPU::get_rgb_color(&red, &green, &blue, index);
	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
  } else if (is_hi_set && is_lo_set) // 3
  {
	const uint16_t index = this->memory.data[palette_base + 3];
	PPU::get_rgb_color(&red, &green, &blue, index);
	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
  }

  SDL_Rect r;
  r.x = *x;
  r.y = y;
  r.w = PIXEL_WIDTH;
  r.h = PIXEL_HEIGHT;
  if (is_hi_set || is_lo_set) {
	SDL_RenderFillRect(renderer, &r);
  }
  *x += PIXEL_WIDTH;

}
void PPU::draw_bg_tile_row(SDL_Renderer *renderer,
						   const uint8_t tile_lo_byte,
						   const uint8_t tile_hi_byte,
						   const int x,
						   const int y,
						   const uint16_t palette_base) {
  int rx = x;
  for (int i = 0; i < 8; i++) {
	const bool is_lo_set = tile_lo_byte & (0b10000000 >> i);
	const bool is_hi_set = tile_hi_byte & (0b10000000 >> i);

	Uint8 red;
	Uint8 green;
	Uint8 blue;

	if (!is_hi_set && !is_lo_set) // 0
	{
	  const uint16_t value = this->memory.data[palette_base + 0];
	  PPU::get_rgb_color(&red, &green, &blue, value);
	  SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	} else if (!is_hi_set && is_lo_set) // 1
	{
	  const uint16_t value = this->memory.data[palette_base + 2];
	  PPU::get_rgb_color(&red, &green, &blue, value);
	  SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	} else if (is_hi_set && !is_lo_set) // 2
	{
	  const uint16_t value = this->memory.data[palette_base + 1];
	  PPU::get_rgb_color(&red, &green, &blue, value);
	  SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	} else if (is_hi_set && is_lo_set) // 3
	{
	  const uint16_t value = this->memory.data[palette_base + 3];
	  PPU::get_rgb_color(&red, &green, &blue, value);
	  SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	}

	SDL_Rect r;
	r.x = rx;
	r.y = y;
	r.w = PIXEL_WIDTH;
	r.h = PIXEL_HEIGHT;
	SDL_RenderFillRect(renderer, &r);
	rx += PIXEL_WIDTH;
  }

}
uint16_t PPU::get_sprite_palette(const uint8_t attribute) {
  switch (attribute) {
	case 0: return 0x3F10;
	case 1: return 0x3F14;
	case 2: return 0x3F18;
	case 3: return 0x3F1C;
	default: assert(false);
  }
}
uint16_t PPU::get_background_palette(const uint16_t attribute) {
  switch (attribute) {
	case 0: return 0x3F00;
	case 1: return 0x3F04;
	case 2: return 0x3F08;
	case 3: return 0x3F0C;
	default: assert(false);
  }
}
void PPU::get_rgb_color(uint8_t *r, uint8_t *g, uint8_t *b, uint16_t index) {
  const uint32_t colors = PPU::ppu_colors[index];
  *r = (colors >> 16) & 0xff;
  *g = (colors >> 8) & 0xFF;
  *b = colors & 0xFF;
}

void PPU::clear_memory() {
  memset(this->memory.data, 0, VRAM_SIZE);
  memset(this->oam.data, 0, OAM_SIZE);

  this->ppu_data_addr = 0x00;
  this->ppu_latch = false;
  this->ppu_latch = false;
}

void PPU::clear_registers() {
  this->registers.oam_addr = 0x00;
  this->registers.oam_data = 0x00;
  this->registers.oam_dma = 0x00;
  this->registers.ppu_addr = 0x00;
  this->registers.ppu_ctrl = 0x00;
  this->registers.ppu_data = 0x00;
  this->registers.ppu_mask = 0x00;
  this->registers.ppu_scroll_x = 0x00;
  this->registers.ppu_scroll_y = 0x00;
  this->registers.ppu_status = 0x00;

}

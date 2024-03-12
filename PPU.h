#ifndef NES_EMULATOR_CPP_PPU_H_
#define NES_EMULATOR_CPP_PPU_H_

#include <cstdint>
#include <SDL_render.h>
#define VRAM_SIZE 0x3FFF
#define OAM_SIZE 256

#define SCREEN_HEIGHT        240
#define SCREEN_WIDTH        256

#define TILE_HEIGHT            8
#define TILE_WIDTH            8

#define PIXEL_HEIGHT        4
#define PIXEL_WIDTH            4

#define PATTERN_TABLE_0        0
#define PATTERN_TABLE_1        0x1000

#define NAME_TABLE_0        0x2000
#define NAME_TABLE_1        0x2400
#define NAME_TABLE_2        0x2800
#define NAME_TABLE_3        0x2C00

#define PATTERN_TABLE_SIZE    0x1000
#define NAME_TABLE_SIZE        0x0400

// Background pattern table address (0: $0000; 1: $1000)
#define BG_PT_ADDR_FLAG        0b00010000

// Sprite pattern table address for 8x8 sprites
// (0: $0000; 1: $1000; ignored in 8x16 mode)
#define SPRITE_PT_ADDR_FLAG        0b00001000


// Base name table address
// (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
#define NAME_TABLE_ADDR_FLAGS 0b00000011

#define PALETTE_BASE          0X3F00

struct VRAM {
  uint8_t data[VRAM_SIZE];
};

struct OAM {
  uint8_t data[OAM_SIZE];
};

struct Registers {
  uint8_t ppu_ctrl;
  uint8_t ppu_mask;
  uint8_t ppu_status;
  uint8_t oam_addr;
  uint8_t oam_data;
  uint8_t ppu_scroll_x;
  uint8_t ppu_scroll_y;
  uint8_t ppu_addr;
  uint8_t ppu_data;
  uint8_t oam_dma;
};

class PPU {

  bool ppu_latch;
  uint16_t ppu_data_addr;
  void draw_sprites(SDL_Renderer *renderer);
  void draw_sprite_tile(SDL_Renderer *renderer, uint16_t x, uint16_t y, uint16_t tile_index, uint8_t attributes);
  void draw_tiles(SDL_Renderer *renderer);
  [[nodiscard]] uint16_t get_pattern_table() const;
  [[nodiscard]] uint16_t get_name_table() const;
  void draw_bg_tile(SDL_Renderer *renderer,
					int x,
					int y,
					uint16_t pattern_pos,
					uint16_t attribute_table_address,
					uint16_t name_table_pos);
  void draw_sprite_tile_row(SDL_Renderer *renderer,
							uint8_t tile_lo_byte,
							uint8_t tile_hi_byte,
							int x,
							int y,
							uint8_t attributes);
  void draw_sprite_row_pixel(SDL_Renderer *renderer,
							 uint8_t tile_lo_byte,
							 uint8_t tile_hi_byte,
							 int y,
							 int *x,
							 uint16_t attribute,
							 int bit);
  void draw_bg_tile_row(SDL_Renderer *renderer,
 						uint8_t tile_lo_byte,
						uint8_t tile_hi_byte,
						int x,
						int y,
						uint16_t palette_base);
  uint16_t  get_sprite_palette(uint8_t attribute);
  uint16_t get_background_palette(uint16_t attribute);
  uint16_t  get_rgb_color(uint8_t *r, uint8_t *g, uint8_t *b, uint16_t color);

 public:
  VRAM memory;
  OAM oam;
  Registers registers;
  
  [[nodiscard]] bool get_ppu_latch() const;
  void set_ppu_latch(bool ppu_latch);
  [[nodiscard]] uint16_t get_ppu_data_addr() const;
  void set_ppu_data_addr(uint16_t ppu_data_addr);

  void render_background(SDL_Renderer *renderer);
  void render_sprites(SDL_Renderer *renderer);

  constexpr static const uint32_t ppu_colors[64] =
	  {
		  0x757575, 0x271B8F, 0x0000AB, 0x47009F, 0x8F0077, 0xAB0013, 0xA70000, 0x7F0B00,
		  0x432F00, 0x004700, 0x005100, 0x003F17, 0x1B3F5F, 0x000000, 0x000000, 0x000000,
		  0xBCBCBC, 0x0073EF, 0x233BEF, 0x8300F3, 0xBF00BF, 0xE7005B, 0xDB2B00, 0xCB4F0F,
		  0x8B7300, 0x009700, 0x00AB00, 0x00933B, 0x00838B, 0x000000, 0x000000, 0x000000,
		  0xFFFFFF, 0x3FBFFF, 0x5F97FF, 0xA78BFD, 0xF77BFF, 0xFF77B7, 0xFF7763, 0xFF9B3B,
		  0xF3BF3F, 0x83D313, 0x4FDF4B, 0x58F898, 0x00EBDB, 0x000000, 0x000000, 0x000000,
		  0xFFFFFF, 0xABE7FF, 0xC7D7FF, 0xD7CBFF, 0xFFC7FF, 0xFFC7DB, 0xFFBFB3, 0xFFDBAB,
		  0xFFE7A3, 0xE3FFA3, 0xABF3BF, 0xB3FFCF, 0x9FFFF3, 0x000000, 0x000000, 0x000000
	  };
};

#endif //NES_EMULATOR_CPP_PPU_H_

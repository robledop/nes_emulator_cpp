#include <iostream>
#include "SDL2/SDL.h"
#include "NES.h"

void print_header_info(const char *rom, uint16_t *prg_size_out, uint16_t *chr_size_out) {
  printf("%s:", "Header");
  for (int i = 0; i < 4; ++i) {
	putchar(rom[i]);
  }
  puts("");
  *prg_size_out = (uint16_t)rom[4] * 1024 * 16;
  *chr_size_out = (uint16_t)rom[5] * 1024 * 8;
  printf("PRG-ROM size: %d bytes\n", *prg_size_out);
  printf("CHR-ROM size: %d bytes\n", *chr_size_out);

  const uint8_t flags_6 = rom[6];
  if (flags_6 & 0b00000001) {
	puts("Mirroring: horizontal (vertical arrangement) (CIRAM A10 = PPU A11)");
  } else {
	puts("Mirroring: vertical (horizontal arrangement) (CIRAM A10 = PPU A10)");
  }

  if (flags_6 & 0b00000010) {
	puts("Cartridge contains battery-backed PRG RAM ($6000-7FFF) or other persistent memory");
  }

  if (flags_6 & 0b00000100) {
	puts("512-byte trainer at $7000-$71FF (stored before PRG data)");
  }

  if (flags_6 & 0b00001000) {
	puts("Ignore mirroring control or above mirroring bit; instead provide four-screen VRAM");
  }

  const uint8_t mapper_low_nibble = flags_6 & 0b11110000;

  const uint8_t flags_7 = rom[7];

  printf("VS Unisystem: %d\n", flags_7 & 0b00000001);
  printf("PlayChoice-10: %d\n", flags_7 & 0b00000010);
  if (flags_7 & 0b00001000) {
	puts("flags 8-15 are in NES 2.0 format");
  }

  const uint8_t mapper_high_nibble = flags_7 & 0b11110000;
  const uint8_t mapper = mapper_low_nibble | mapper_high_nibble;

  printf("Mapper: %x\n", mapper);
  printf("PRG-RAM size: %d bytes\n", rom[8] * 1024 * 8);
  printf("TV system: %s\n", rom[9] & 0b00000001 ? "PAL" : "NTSC");

  puts("flags 10:");
  const uint8_t flags_10 = rom[10];

  switch (flags_10 & 0b00000011) {
	case 0: puts("TV system: NTSC");
	  break;
	case 2: puts("TV system: PAL");
	  break;
	default: puts("TV system: dual compatible");
	  break;
  }
}

int load_file(char **text, const char *filename, uint32_t *size_out) {
  FILE *fp = fopen(filename, "r");
  if (fp != nullptr) {
	if (fseek(fp, 0L, SEEK_END) == 0) {
	  const long bufsize = ftell(fp);
	  if (bufsize == -1) {
		fclose(fp);
		return 1;
	  }
	  *size_out = sizeof(char) * (bufsize + 1) + 100;
	  *text = static_cast<char *>(malloc(*size_out));

	  if (fseek(fp, 0L, SEEK_SET) != 0) {
		fclose(fp);
		return 1;
	  }

	  fread(*text, sizeof(char), bufsize, fp);
	  if (ferror(fp) != 0) {
		fputs("Error reading file", stderr);
	  }
	}
	fclose(fp);
	return 0;
  }
  return 1;
}

int main(const int argc, char** argv)
{
	char* rom = nullptr;
	uint32_t size = 0;

	const int result = load_file(&rom, argv[1], &size);

	if (result != 0 || rom == nullptr)
	{
		puts("There was an error while trying to load the ROM file.");
		free(rom);
		return result;
	}
	uint16_t prg_size;
	uint16_t chr_size;

	NES nes{};

	nes.cpu.clear_memory();

	print_header_info(rom, &prg_size, &chr_size);


	memcpy(&nes.cpu.memory.data[0x8000], &rom[0x10], prg_size);

	if (prg_size == 0x4000)
	{
		memcpy(&nes.cpu.memory.data[0xC000], &rom[0x10], prg_size);
	}

	nes.cpu.controller = &nes.controller;

	nes.cpu.init(prg_size);
	memcpy(nes.cpu.ppu.memory.data, &rom[prg_size + 0x10], chr_size);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow(
		EMULATOR_WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH * PIXEL_HEIGHT,
		SCREEN_HEIGHT * PIXEL_WIDTH,
		SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

	int x = 0;

	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				goto out;
			}
			nes.controller.handle_input(&event);
		}

		nes.cpu.exec(nes.cpu.memory.data[nes.cpu.pc++]);

		if (x == 4000)
		{
			nes.cpu.ppu.render_background(renderer);
			nes.cpu.ppu.render_sprites(renderer);
		}

		if (x >= 1200)
		{
			nes.cpu.ppu.registers.ppu_status ^= (0 ^ nes.cpu.ppu.registers.ppu_status) & 0b10000000;
		}

		if (x == 4001)
		{
			nes.cpu.ppu.registers.ppu_status |= 0b10000000;
			if (nes.cpu.ppu.registers.ppu_ctrl & 0b10000000)
			{
				nes.cpu.call_nmi();
			}
			x = 0;
		}
		x++;
	}

out:
	SDL_DestroyWindow(window);
	free(rom);
	return 0;
}

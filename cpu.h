
#ifndef NES_EMULATOR_CPP_CPU_H_
#define NES_EMULATOR_CPP_CPU_H_

#include <cstdint>
#include "PPU.h"
#include "Controller.h"

#define MAX_MEMORY 65536
#define STACK_BASE        0x100

#define SIGN_BIT        0x80

#define C_FLAG            0b00000001
#define Z_FLAG            0b00000010
#define I_FLAG            0b00000100
#define D_FLAG            0b00001000
#define B_FLAG            0b00010000
#define V_FLAG            0b01000000
#define N_FLAG            0b10000000
#define UNUSED_FLAG        0b00100000

#define PPU_CTRL        0x2000
#define PPU_MASK        0x2001
#define PPU_STATUS        0x2002
#define OAM_ADDR        0x2003
#define OAM_DATA        0x2004
#define PPU_SCROLL        0x2005
#define PPU_ADDR        0x2006
#define PPU_DATA        0x2007

#define OAM_DMA            0x4014

#define CONTROLLER_1    0x4016
#define CONTROLLER_2    0x4017

#define EMULATOR_WINDOW_TITLE "NES Emulator"

#define LOGGING

enum AddressMode {
  implicit,
  accumulator,
  immediate,
  zero_page,
  zero_page_x,
  zero_page_y,
  relative,
  absolute,
  absolute_x,
  absolute_y,
  indirect,
  // (Indirect,X)
  indexed_indirect,
  // (Indirect),Y
  indirect_indexed
};

struct Memory {
  uint8_t data[MAX_MEMORY];
};

class CPU {
  uint16_t nmi_prt;
  uint16_t irq_prt;

  // Accumulator
  uint8_t a;

  // Index register
  uint8_t x, y;

  // Stack pointer
  uint8_t sp;

  // Processor status
  // N, V, 1, B, D, I, Z, C
  // N = Negative
  // V = Overflow
  // 1 = Unused
  // B = BRK command 1 = BRK, 0 = IRQB
  // D = decimal mode
  // I = IRQB disable
  // Z = Zero
  // C = Carry
  uint8_t p;



  void calc_carry(uint16_t value);
  void calc_zero(uint8_t value);
  void calc_negative(uint8_t value);
  void calc_overflow(uint16_t result, uint8_t operand);
  void calc_add(uint8_t argument);
  uint8_t read_memory_at_address(uint16_t address);
  void write_memory_at_address(uint16_t address, uint8_t value);
  uint16_t get_memory_address(AddressMode address_mode);
  
  void lda(AddressMode address_mode);
  void ldx(AddressMode address_mode);
  void ldy(AddressMode address_mode);
  void adc(AddressMode address_mode);
  void AND(AddressMode address_mode);
  void asl(AddressMode address_mode);
  void bcc();
  void beq();
  void bit(AddressMode address_mode);
  void bmi();
  void bne();
  void bpl();
  void brk();
  void bvc();
  void bvs();
  void clc();
  void cld();
  void cli();
  void clv();
  void cmp(AddressMode address_mode);
  void cpx(AddressMode address_mode);
  void cpy(AddressMode address_mode);
  void dec(AddressMode address_mode);
  void dex();
  void dey();
  void eor(AddressMode address_mode);
  void inc(AddressMode address_mode);
  void inx();
  void iny();
  void jmp(AddressMode address_mode);

 public:
  // Program counter
  uint16_t pc;
  Memory memory;
  PPU ppu;
  Controller *controller;
  void exec(uint8_t opcode);
  void init(uint16_t prg_size);
  void clear_memory();
  uint8_t read_memory(uint16_t address);
  void write_memory(uint16_t address, uint8_t value);

  bool get_c_flag();
  void set_c_flag(uint8_t value);
  bool get_z_flag();
  void set_z_flag(uint8_t value);
  bool get_i_flag();
  void set_i_flag(int8_t value);
  bool get_d_flag();
  void set_d_flag(int8_t value);
  bool get_b_flag();
  void set_b_flag(int8_t value);
  bool get_v_flag();
  void set_v_flag(int8_t value);
  bool get_n_flag();
  void set_n_flag(int8_t value);

  void call_nmi();
  uint16_t stack_pop_16();
  uint8_t stack_pop_8();
  void stack_push_16(uint16_t value);
  void stack_push_8(uint8_t value);
};

#endif 

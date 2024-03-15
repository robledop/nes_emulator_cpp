#include <cassert>
#include "cpu.h"
void CPU::exec(uint8_t opcode) {
  switch (opcode) {
	case 0xA9: lda(immediate);
	  break;
	case 0xA5: lda(zero_page);
	  break;
	case 0xB5: lda(zero_page_x);
	  break;
	case 0xAD: lda(absolute);
	  break;
	case 0xBD: lda(absolute_x);
	  break;
	case 0xB9: lda(absolute_y);
	  break;
	case 0xA1: lda(indexed_indirect);
	  break;
	case 0xB1: lda(indirect_indexed);
	  break;

	case 0xA2: ldx(immediate);
	  break;
	case 0xA6: ldx(zero_page);
	  break;
	case 0xB6: ldx(zero_page_y);
	  break;
	case 0xAE: ldx(absolute);
	  break;
	case 0xBE: ldx(absolute_y);
	  break;

	case 0xA0: ldy(immediate);
	  break;
	case 0xA4: ldy(zero_page);
	  break;
	case 0xB4: ldy(zero_page_x);
	  break;
	case 0xAC: ldy(absolute);
	  break;
	case 0xBC: ldy(absolute_x);
	  break;

	case 0x69: adc(immediate);
	  break;
	case 0x65: adc(zero_page);
	  break;
	case 0x75: adc(zero_page_x);
	  break;
	case 0x6D: adc(absolute);
	  break;
	case 0x7D: adc(absolute_x);
	  break;
	case 0x79: adc(absolute_y);
	  break;
	case 0x61: adc(indexed_indirect);
	  break;
	case 0x71: adc(indirect_indexed);
	  break;

	case 0x29: AND(immediate);
	  break;
	case 0x25: AND(zero_page);
	  break;
	case 0x35: AND(zero_page_x);
	  break;
	case 0x2D: AND(absolute);
	  break;
	case 0x3D: AND(absolute_x);
	  break;
	case 0x39: AND(absolute_y);
	  break;
	case 0x21: AND(indexed_indirect);
	  break;
	case 0x31: AND(indirect_indexed);
	  break;

	case 0x0A: asl(accumulator);
	  break;
	case 0x06: asl(zero_page);
	  break;
	case 0x16: asl(zero_page_x);
	  break;
	case 0x0E: asl(absolute);
	  break;
	case 0x1E: asl(absolute_x);
	  break;

	case 0x90: bcc();
	  break;

	case 0xB0: bcs();
	  break;

	case 0xF0: beq();
	  break;

	case 0x24: bit(zero_page);
	  break;
	case 0x2C: bit(absolute);
	  break;

	case 0x30: bmi();
	  break;

	case 0xD0: bne();
	  break;
	case 0x10: bpl();
	  break;

	case 0x00: brk();
	  break;

	case 0x50: bvc();
	  break;
	case 0x70: bvs();
	  break;
	case 0x18: clc();
	  break;
	case 0xD8: cld();
	  break;
	case 0x58: cli();
	  break;
	case 0xB8: clv();
	  break;
	case 0xC9: cmp(immediate);
	  break;
	case 0xC5: cmp(zero_page);
	  break;
	case 0xD5: cmp(zero_page_x);
	  break;
	case 0xCD: cmp(absolute);
	  break;
	case 0xDD: cmp(absolute_x);
	  break;
	case 0xD9: cmp(absolute_y);
	  break;
	case 0xC1: cmp(indexed_indirect);
	  break;
	case 0xD1: cmp(indirect_indexed);
	  break;
	case 0xE0: cpx(immediate);
	  break;
	case 0xE4: cpx(zero_page);
	  break;
	case 0xEC: cpx(absolute);
	  break;
	case 0xC0: cpy(immediate);
	  break;
	case 0xC4: cpy(zero_page);
	  break;
	case 0xCC: cpy(absolute);
	  break;
	case 0xC6: dec(zero_page);
	  break;
	case 0xD6: dec(zero_page_x);
	  break;
	case 0xCE: dec(absolute);
	  break;
	case 0xDE: dec(absolute_x);
	  break;
	case 0xCA: dex();
	  break;
	case 0x88: dey();
	  break;
	case 0x49: eor(immediate);
	  break;
	case 0x45: eor(zero_page);
	  break;
	case 0x55: eor(zero_page_x);
	  break;
	case 0x4D: eor(absolute);
	  break;
	case 0x5D: eor(absolute_x);
	  break;
	case 0x59: eor(absolute_y);
	  break;
	case 0x41: eor(indexed_indirect);
	  break;
	case 0x51: eor(indirect_indexed);
	  break;
	case 0xE6: inc(zero_page);
	  break;
	case 0xF6: inc(zero_page_x);
	  break;
	case 0xEE: inc(absolute);
	  break;
	case 0xFE: inc(absolute_x);
	  break;
	case 0xE8: inx();
	  break;
	case 0xC8: iny();
	  break;
	case 0x4C: jmp(absolute);
	  break;
	case 0x6C: jmp(indirect);
	  break;
	case 0x20: jsr();
	  break;
	case 0x4A: lsr(accumulator);
	  break;
	case 0x46: lsr(zero_page);
	  break;
	case 0x56: lsr(zero_page_x);
	  break;
	case 0x4E: lsr(absolute);
	  break;
	case 0x5E: lsr(absolute_x);
	  break;
	case 0xEA:
	case 0x1A:
	case 0x3A: nop();
	  break;
	case 0x09: ora(immediate);
	  break;
	case 0x05: ora(zero_page);
	  break;
	case 0x15: ora(zero_page_x);
	  break;
	case 0x0D: ora(absolute);
	  break;
	case 0x1D: ora(absolute_x);
	  break;
	case 0x19: ora(absolute_y);
	  break;
	case 0x01: ora(indexed_indirect);
	  break;
	case 0x11: ora(indirect_indexed);
	  break;
	case 0x48: pha();
	  break;
	case 0x08: php();
	  break;
	case 0x68: pla();
	  break;
	case 0x28: plp();
	  break;
	case 0x2A: rol(accumulator);
	  break;
	case 0x26: rol(zero_page);
	  break;
	case 0x36: rol(zero_page_x);
	  break;
	case 0x2E: rol(absolute);
	  break;
	case 0x3E: rol(absolute_x);
	  break;
	case 0x6A: ror(accumulator);
	  break;
	case 0x66: ror(zero_page);
	  break;
	case 0x76: ror(zero_page_x);
	  break;
	case 0x6E: ror(absolute);
	  break;
	case 0x7E: ror(absolute_x);
	  break;
	case 0x40: rti();
	  break;
	case 0x60: rts();
	  break;
	case 0xE9: sbc(immediate);
	  break;
	case 0xE5: sbc(zero_page);
	  break;
	case 0xF5: sbc(zero_page_x);
	  break;
	case 0xED: sbc(absolute);
	  break;
	case 0xFD: sbc(absolute_x);
	  break;
	case 0xF9: sbc(absolute_y);
	  break;
	case 0xE1: sbc(indexed_indirect);
	  break;
	case 0xF1: sbc(indirect_indexed);
	  break;
	case 0x38: sec();
	  break;
	case 0xF8: sed();
	  break;
	case 0x78: sei();
	  break;
	case 0x85: sta(zero_page);
	  break;
	case 0x95: sta(zero_page_x);
	  break;
	case 0x8D: sta(absolute);
	  break;
	case 0x9D: sta(absolute_x);
	  break;
	case 0x99: sta(absolute_y);
	  break;
	case 0x81: sta(indexed_indirect);
	  break;
	case 0x91: sta(indirect_indexed);
	  break;
	case 0x86: stx(zero_page);
	  break;
	case 0x96: stx(zero_page_y);
	  break;
	case 0x8E: stx(absolute);
	  break;
	case 0x84: sty(zero_page);
	  break;
	case 0x94: sty(zero_page_x);
	  break;
	case 0x8C: sty(absolute);
	  break;
	case 0xAA: tax();
	  break;
	case 0xA8: tay();
	  break;
	case 0xBA: tsx();
	  break;
	case 0x8A: txa();
	  break;
	case 0x9A: txs();
	  break;
	case 0x98: tya();
	  break;

	default: this->pc++;
	  printf("Unsupported opcode:%x\nPC:%x\n", opcode, this->pc);
  }
}

void CPU::init(uint16_t prg_size) {
  this->sp = 0xFF;
  this->p = 0b00100000;
  this->a = 0x00;
  this->x = 0x00;
  this->y = 0x00;

  this->pc = ((uint16_t)(this->read_memory(0x8000 + prg_size - 3) << 8)) |
	  this->read_memory(0x8000 + prg_size - 4);

  this->nmi_prt =
	  ((uint16_t)(this->read_memory(0x8000 + prg_size - 5) << 8)) |
		  this->read_memory(0x8000 + prg_size - 6);

  this->irq_prt =
	  ((uint16_t)(this->read_memory(0x8000 + prg_size - 1) << 8)) |
		  this->read_memory(0x8000 + prg_size - 2);

  this->ppu.clear_memory();
  this->ppu.clear_registers();
  this->controller->init();
}

void CPU::clear_memory() {
  memset(&this->memory, 0, MAX_MEMORY);
}
void CPU::call_nmi() {
  this->stack_push_16(this->pc);
  this->stack_push_8(this->p);
  this->pc = this->nmi_prt;
}
bool CPU::get_c_flag() const {
  return this->p & C_FLAG;
}
void CPU::set_c_flag(uint8_t value) {
  this->p ^= (-value ^ this->p) & C_FLAG;
}
bool CPU::get_z_flag() const {
  return this->p & Z_FLAG;
}
void CPU::set_z_flag(const uint8_t value) {
  this->p ^= (-value ^ this->p) & Z_FLAG;
}
bool CPU::get_i_flag() const {
  return this->p & I_FLAG;
}
void CPU::set_i_flag(const int8_t value) {
  this->p ^= (-value ^ this->p) & I_FLAG;
}
bool CPU::get_d_flag() const {
  return this->p & D_FLAG;
}
void CPU::set_d_flag(const int8_t value) {
  this->p ^= (-value ^ this->p) & D_FLAG;
}
bool CPU::get_b_flag() const {
  return this->p & B_FLAG;
}
void CPU::set_b_flag(const int8_t value) {
  this->p ^= (-value ^ this->p) & B_FLAG;
}
bool CPU::get_v_flag() const {
  return this->p & V_FLAG;
}
void CPU::set_v_flag(const int8_t value) {
  this->p ^= (-value ^ this->p) & V_FLAG;
}
bool CPU::get_n_flag() const {
  return this->p & N_FLAG;
}
void CPU::set_n_flag(const int8_t value) {
  this->p ^= (-value ^ this->p) & N_FLAG;
}
uint16_t CPU::stack_pop_16() {
  const uint16_t result =
	  (uint16_t)(this->read_memory(STACK_BASE + (this->sp + 2)) << 8) |
		  (uint16_t)
  this->read_memory(STACK_BASE + (this->sp + 1));
  this->sp += 2;
  return result;
}

uint8_t CPU::stack_pop_8() {
  this->sp++;
  return read_memory(STACK_BASE + this->sp);
}

void CPU::stack_push_16(const uint16_t value) {
  this->write_memory(STACK_BASE + this->sp, (value >> 8) & 0xFF);
  this->write_memory(STACK_BASE + (this->sp - 1), value & 0xFF);
  this->sp -= 2;

}
void CPU::stack_push_8(const uint8_t value) {
  this->write_memory(STACK_BASE + this->sp, value);
  this->sp--;
}
void CPU::calc_carry(uint16_t value) {
  if (value & 0xFF00) {
	this->set_c_flag(1);
  } else {
	this->set_c_flag(0);
  }

}
void CPU::calc_zero(uint8_t value) {
  if (value == 0x00) {
	this->set_z_flag(1);
  } else {
	this->set_z_flag(0);
  }
}
void CPU::calc_negative(uint8_t value) {
  if ((value & 0b10000000) != 0) {
	this->set_n_flag(1);
  } else {
	this->set_n_flag(0);
  }
}

// http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
// Two numbers that have the same sign are added, and the result has a different sign
void CPU::calc_overflow(uint16_t result, uint8_t operand) {
  const uint8_t a_sign = this->a & (uint8_t)0x80;
  const uint8_t operand_sign = operand & (uint8_t)0x80;
  const uint8_t result_sign = result & 0x80;

  if ((a_sign == operand_sign) && a_sign != result_sign) {
	this->set_v_flag(1);
  } else {
	this->set_v_flag(0);
  }
}
void CPU::calc_add(uint8_t argument) {
  const uint16_t result = this->a + argument + (this->get_c_flag() ? 1 : 0);
  this->calc_carry(result);
  this->calc_overflow(result, argument);
  this->a = result & 0xFF;
  this->calc_zero(this->a);
  this->calc_negative(this->a);
}

uint8_t CPU::read_memory_at_address(uint16_t address) {
  return this->memory.data[address];
}

void CPU::write_memory_at_address(uint16_t address, uint8_t value) {
  this->memory.data[address] = value;
}
uint16_t CPU::get_memory_address(AddressMode address_mode) {
  switch (address_mode) {
	case implicit: assert(false);
	case accumulator: assert(false);

	case immediate: return this->pc++;

	case zero_page: {
	  const uint8_t value = this->read_memory(this->pc);
	  this->pc++;
	  return value;
	}

	case zero_page_x: {
	  const uint8_t value = this->read_memory(this->pc);
	  this->pc++;
	  return (value + this->x) & 0x00FF;
	}

	case zero_page_y: {
	  const uint8_t value = this->read_memory(this->pc);
	  this->pc++;
	  return (value + this->y) & 0x00FF;
	}

	case relative: {
	  const uint8_t value = this->read_memory(this->pc);
	  this->pc++;
	  return value;
	}

	case absolute: {
	  const uint8_t low_byte = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t high_byte = this->read_memory(this->pc);
	  this->pc++;
	  return ((uint16_t)(high_byte << 8)) | low_byte;
	}

	case absolute_x: {
	  const uint8_t low_byte = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t high_byte = this->read_memory(this->pc);
	  this->pc++;
	  uint16_t address = ((uint16_t)(high_byte << 8)) | low_byte;
	  address += this->x;
	  return address;
	}

	case absolute_y: {
	  const uint8_t low_byte = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t high_byte = this->read_memory(this->pc);
	  this->pc++;
	  uint16_t address = ((uint16_t)(high_byte << 8)) | low_byte;
	  address += this->y;
	  return address;
	}

	case indirect: {
	  const uint8_t low_byte = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t high_byte = this->read_memory(this->pc);
	  this->pc++;
	  const uint16_t address = ((uint16_t)(high_byte << 8)) | low_byte;

	  const uint8_t indirect_lo_byte = this->read_memory(address);
	  const uint8_t indirect_hi_byte = this->read_memory(address + 1);

	  const uint16_t indirect_address = ((uint16_t)(indirect_hi_byte << 8)) | indirect_lo_byte;

	  return indirect_address;
	}

	case indexed_indirect: {

	  const uint8_t vector = this->read_memory(this->pc);
	  this->pc++;
	  // AND it with 0xFF to wrap around if it goes over 0xFF
	  const uint8_t low_byte = this->read_memory((vector + this->x) & 0xFF);
	  const uint8_t high_byte = this->read_memory((vector + this->x + 1) & 0xFF);
	  return ((uint16_t)(high_byte << 8)) | low_byte;
	}

	case indirect_indexed: {
	  const uint8_t vector = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t low_byte = this->read_memory(vector);
	  const uint8_t high_byte = this->read_memory((vector + 1) & 0xFF);

	  return (((uint16_t)(high_byte << 8)) | low_byte) + this->y;
	}
  }

  return 0;
}
uint8_t CPU::read_memory(uint16_t address) {
  switch (address) {
	case PPU_CTRL:
	case PPU_MASK:
	case PPU_SCROLL:
	  // Do nothing. Write-only registers
	  return 0;

	case PPU_STATUS: this->ppu.ppu_latch = false;
	  return this->ppu.registers.ppu_status;
	case OAM_ADDR: return this->ppu.registers.oam_addr;
	case OAM_DATA: return this->ppu.registers.oam_data;
	case PPU_ADDR: return this->ppu.registers.ppu_addr;
	case PPU_DATA: return this->ppu.registers.ppu_data;
	case CONTROLLER_1: return this->controller->read_next_button();
	default: return this->read_memory_at_address(address);
  }
}
void CPU::write_memory(uint16_t address, const uint8_t value) {
  switch (address) {
	case PPU_CTRL: this->ppu.registers.ppu_ctrl = value;
	  break;
	case PPU_MASK: this->ppu.registers.ppu_mask = value;
	  break;
	case PPU_STATUS:
	  // Do nothing. PPU_STATUS is read-only
	  break;
	case OAM_ADDR: this->ppu.registers.oam_addr = value;
	  break;
	case OAM_DATA: this->ppu.registers.oam_data = value;
	  break;

	case PPU_SCROLL: {
	  if (this->ppu.ppu_latch) {
		this->ppu.registers.ppu_scroll_y = value;
		this->ppu.ppu_latch = false;
	  } else {
		this->ppu.registers.ppu_scroll_x = value;
		this->ppu.ppu_latch = true;
	  }
	}
	  break;

	case PPU_ADDR: {
	  if (this->ppu.ppu_latch) {
		this->ppu.ppu_data_addr |= (uint16_t)value;
		this->ppu.ppu_latch = false;
	  } else {
		this->ppu.ppu_data_addr = (uint16_t)(value << 8);
		this->ppu.ppu_latch = true;
	  }
	  assert(this->ppu.ppu_data_addr < VRAM_SIZE);
	}
	  break;

	case PPU_DATA: assert(this->ppu.ppu_data_addr <= VRAM_SIZE - 1);
	  this->ppu.memory.data[this->ppu.ppu_data_addr] = value;
	  if (this->ppu.registers.ppu_ctrl & 0b00000100) {
		this->ppu.ppu_data_addr += 32;
	  } else {
		this->ppu.ppu_data_addr += 1;
	  }
	  break;

	case OAM_DMA: {
	  for (uint16_t i = 0; i < 256; ++i) {
		const uint16_t oam_copy_address = (uint16_t)(value << 8) + i;
		this->ppu.oam.data[i] = this->read_memory(oam_copy_address);
	  }
	}
	  break;

	case CONTROLLER_1: this->controller->write(value);
	  break;
	default: this->write_memory_at_address(address, value);
  }
}
void CPU::lda(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  this->a = this->read_memory(address);

  this->calc_zero(this->a);
  this->calc_negative(this->a);

#ifdef LOGGING
  printf("LDA %x\n", this->a);
#endif
}
void CPU::ldx(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  this->x = this->read_memory(address);
  this->calc_zero(this->x);
  this->calc_negative(this->x);
#ifdef LOGGING
  printf("LDX %x\n", this->x);
#endif

}
void CPU::ldy(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  this->y = this->read_memory(address);
  this->calc_zero(this->y);
  this->calc_negative(this->y);
#ifdef LOGGING
  printf("LDY %x\n", this->y);
#endif
}

// Add with carry
void CPU::adc(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);
  this->calc_add(mem);

#ifdef LOGGING
  printf("ADC %x\n", mem);
#endif
}

// Logical AND
void CPU::AND(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t value = this->read_memory(address);
  this->a &= value;
  this->calc_negative(this->a);
  this->calc_zero(this->a);
#ifdef LOGGING
  printf("AND %x\n", this->read_memory(address));
#endif
}

// Arithmetic shift left
void CPU::asl(AddressMode address_mode) {
  if (address_mode == accumulator) {
	this->set_c_flag(((this->a & 0b10000000) ? 1 : 0));
	this->a <<= 1;

	this->calc_negative(this->a);
	this->calc_zero(this->a);
#ifdef LOGGING
	puts("ASL");
#endif
  } else {
	const uint16_t address = this->get_memory_address(address_mode);
	const uint8_t value = this->read_memory(address);
	this->set_c_flag((value & 0b10000000 ? 1 : 0));
	const auto new_value = (uint8_t)(value << 1);
	this->write_memory(address, new_value);

	this->calc_negative(new_value);
	this->calc_zero(new_value);

#ifdef LOGGING
	printf("ASL %x <%x>\n", address, new_value);
#endif
  }
}

// Branch on carry clear
void CPU::bcc() {
  if (!this->get_c_flag()) {
	const uint16_t address = this->get_memory_address(AddressMode::relative);
	this->pc += (char)address;
  } else {
	this->pc++;
  }
#ifdef LOGGING
  printf("BCC %x\n", this->pc);
#endif
}
void CPU::beq() {
  if (this->get_z_flag()) {
	const uint16_t address = this->get_memory_address(AddressMode::relative);
	this->pc += (char)address;
  } else {
	this->pc++;
  }

#ifdef LOGGING
  printf("BEQ %x\n", this->pc);
#endif
}
void CPU::bit(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);
  const uint8_t result = this->a & mem;

  this->set_n_flag(mem & 0b10000000 ? 1 : 0);
  this->set_v_flag(mem & 0b01000000 ? 1 : 0);
  this->set_z_flag(result == 0 ? 1 : 0);

#ifdef LOGGING
  printf("BIT %x\n", address);
#endif
}
void CPU::bmi() {
  if (this->get_n_flag()) {
	const uint16_t address = this->get_memory_address(AddressMode::relative);
	this->pc += (char)address;
  } else {
	this->pc++;
  }
#ifdef LOGGING
  printf("BMI %x\n", this->pc);
#endif
}
void CPU::bne() {
  if (!this->get_z_flag()) {
	const uint16_t address = this->get_memory_address(AddressMode::relative);
	this->pc += (char)address;
  } else {
	this->pc++;
  }
#ifdef LOGGING
  printf("BNE %x\n", this->pc);
#endif

}
void CPU::bpl() {
  if (!this->get_n_flag()) {
	const uint16_t address = this->get_memory_address(AddressMode::relative);
	this->pc += (char)address;
#ifdef LOGGING
	printf("BPL %x\n", address);
#endif
  } else {
	this->pc++;
#ifdef LOGGING
	printf("BPL %x\n", this->pc);
#endif
  }

}
void CPU::brk() {
  this->stack_push_16(this->pc + 1);
  this->set_b_flag(1);
  this->set_i_flag(1);
  this->stack_push_8(this->p);

  this->pc = this->irq_prt;

#ifdef LOGGING
  printf("BRK\n");
#endif

}
void CPU::bvc() {
  if (!this->get_v_flag()) {
	const uint16_t address = this->get_memory_address(AddressMode::relative);
	this->pc += (char)address;
  } else {
	this->pc++;
  }
#ifdef LOGGING
  printf("BVC %x\n", this->pc);
#endif

}
void CPU::bvs() {
  if (this->get_v_flag()) {
	const uint16_t address = this->get_memory_address(AddressMode::relative);
	this->pc += (char)address;
  } else {
	this->pc++;
  }

#ifdef LOGGING
  printf("BVS %x\n", this->pc);
#endif
}

void CPU::clc() {
  this->set_c_flag(0);
#ifdef LOGGING
  printf("CLC\n");
#endif
}

void CPU::cld() {
  this->set_d_flag(0);
#ifdef LOGGING
  printf("CLD\n");
#endif
}
void CPU::cli() {
  this->set_i_flag(0);
#ifdef LOGGING
  printf("CLI\n");
#endif
}
void CPU::clv() {
  this->set_v_flag(0);
#ifdef LOGGING
  printf("CLV\n");
#endif
}
void CPU::cmp(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);
  const int result = this->a - mem;

  this->set_c_flag(result >= 0 ? 1 : 0);
  this->calc_negative((uint8_t)result);
  this->calc_zero((uint8_t)result);

#ifdef LOGGING
  printf("CMP %x\n", mem);
#endif

}
void CPU::cpx(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);

  const int result = this->x - mem;

  this->set_c_flag(result >= 0 ? 1 : 0);
  this->calc_negative((uint8_t)result);
  this->calc_zero((uint8_t)result);

#ifdef LOGGING
  printf("CPX %x\n", mem);
#endif
}
void CPU::cpy(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);

  const int result = this->y - mem;

  this->set_c_flag(result >= 0 ? 1 : 0);
  this->calc_negative((uint8_t)result);
  this->calc_zero((uint8_t)result);

#ifdef LOGGING
  printf("CPY %x\n", mem);
#endif
}
void CPU::dec(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);
  const uint8_t new_value = mem - 1;
  this->write_memory(address, new_value);
  this->calc_negative(new_value);
  this->calc_zero(new_value);

#ifdef LOGGING
  printf("DEC %x\n", address);
#endif

}
void CPU::dex() {
  this->x -= 1;
  this->calc_negative(this->x);
  this->calc_zero(this->x);

#ifdef LOGGING
  puts("DEX");
#endif

}
void CPU::dey() {
  this->y -= 1;
  this->calc_negative(this->y);
  this->calc_zero(this->y);

#ifdef LOGGING
  puts("DEY");
#endif

}
void CPU::eor(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);
  this->a ^= mem;
  this->calc_negative(this->a);
  this->calc_zero(this->a);

#ifdef LOGGING
  printf("EOR %x\n", mem);
#endif
}

void CPU::inc(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);
  const uint8_t new_value = mem + 1;
  this->write_memory(address, new_value);
  this->calc_negative(new_value);
  this->calc_zero(new_value);

#ifdef LOGGING
  printf("INC %x\n", address);
#endif
}
void CPU::inx() {
  this->x += 1;
  this->calc_negative(this->x);
  this->calc_zero(this->x);

#ifdef LOGGING
  puts("INX");
#endif

}
void CPU::iny() {
  this->y += 1;
  this->calc_negative(this->y);
  this->calc_zero(this->y);

#ifdef LOGGING
  puts("INY");
#endif

}
void CPU::jmp(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);

  // An original 6502 has a bug where it does not correctly fetch the target address
  // if the indirect vector falls on a page boundary (e.g. $xxFF where xx is
  // any value from $00 to $FF). In this case fetches the LSB from $xxFF as
  // expected but takes the MSB from $xx00. This is fixed in some later chips
  // like the 65SC02 so for compatibility always ensure the indirect vector is
  // not at the end of the page.

  //assert(!(address_mode == indirect && (address & 0x00FF) == 0x00FF));

  this->pc = address;

#ifdef LOGGING
  puts("JMP");
#endif
}

void CPU::jsr() {
  this->stack_push_16(this->pc + 1);
  const uint16_t address = this->get_memory_address(AddressMode::absolute);
  this->pc = address;

#ifdef LOGGING
  printf("JSR %x\n", address);
#endif
}

void CPU::lsr(AddressMode address_mode) {
  if (address_mode == accumulator) {
	this->set_c_flag((this->a & 0b00000001) ? 1 : 0);
	this->a >>= 1;
	this->calc_negative(this->a);
	this->calc_zero(this->a);

#ifdef LOGGING
	printf("LSR\n");
#endif
  } else {
	const uint16_t address = this->get_memory_address(address_mode);
	uint8_t mem = this->read_memory(address);
	this->set_c_flag((mem & 0b00000001) ? 1 : 0);
	this->write_memory(address, mem >> 1);
	mem = this->read_memory(address);
	this->calc_negative(mem);
	this->calc_zero(mem);

#ifdef LOGGING
	printf("LSR %x\n", address);
#endif
  }
}

void CPU::nop() {
#ifdef LOGGING
  puts("NOP");
#endif
}

void CPU::ora(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  this->a |= this->read_memory(address);
  this->calc_negative(this->a);
  this->calc_zero(this->a);

#ifdef LOGGING
  printf("ORA %x\n", address);
#endif
}
void CPU::pha() {
  this->stack_push_8(this->a);
#ifdef LOGGING
  puts("PHA");
#endif
}
void CPU::php() {
  this->stack_push_8(this->p | UNUSED_FLAG | B_FLAG);
#ifdef LOGGING
  puts("PHP");
#endif
}
void CPU::pla() {
  this->a = this->stack_pop_8();
  this->calc_negative(this->a);
  this->calc_zero(this->a);

#ifdef LOGGING
  puts("PLA");
#endif

}
void CPU::plp() {
  this->p = this->stack_pop_8();

#ifdef LOGGING
  puts("PLP");
#endif

}
void CPU::rol(AddressMode address_mode) {
  const bool current_carry_flag = this->get_c_flag();
  if (address_mode == accumulator) {
	this->set_c_flag((this->a & 0b10000000) ? 1 : 0);
	this->a <<= 1;
	this->a |= current_carry_flag ? 1 : 0;
	this->calc_zero(this->a);
	this->calc_negative(this->a);

#ifdef LOGGING
	puts("ROL");
#endif
  } else {
	const uint16_t address = this->get_memory_address(address_mode);
	const uint8_t mem = this->read_memory(address);
	this->set_c_flag((mem & 0b10000000) ? 1 : 0);
	auto new_value = (uint8_t)(mem << 1);
	new_value |= current_carry_flag ? 1 : 0;
	this->write_memory(address, new_value);
	this->calc_zero(new_value);
	this->calc_negative(new_value);

#ifdef LOGGING
	printf("ROL %x\n", address);
#endif
  }

}
void CPU::ror(AddressMode address_mode) {
  const bool current_carry_flag = this->get_c_flag();
  if (address_mode == accumulator) {
	this->set_c_flag((this->a & 0b00000001) ? 1 : 0);
	this->a >>= 1;
	this->a |= current_carry_flag ? 0b10000000 : 0;
	this->calc_negative(this->a);
	this->calc_zero(this->a);

#ifdef LOGGING
	puts("ROR");
#endif
  } else {
	const uint16_t address = this->get_memory_address(address_mode);
	const uint8_t mem = this->read_memory(address);
	this->set_c_flag((mem & 0b00000001) ? 1 : 0);
	uint8_t new_value = mem >> 1;
	new_value |= current_carry_flag ? 0b10000000 : 0;
	this->write_memory(address, new_value);
	this->calc_negative(new_value);
	this->calc_zero(new_value);

#ifdef LOGGING
	printf("ROR %x\n", address);
#endif
  }

}
void CPU::rti() {
  this->p = this->stack_pop_8();
  this->pc = this->stack_pop_16();

#ifdef LOGGING
  puts("RTI");
#endif

}
void CPU::rts() {
  const uint16_t value = this->stack_pop_16();
  this->pc = value + 1;

#ifdef LOGGING
  puts("RTS");
#endif

}
void CPU::sbc(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);
  this->calc_add(~mem);

#ifdef LOGGING
  printf("SBC %x\n", address);
#endif
}
void CPU::sec() {
  this->set_c_flag(1);

#ifdef LOGGING
  puts("SEC");
#endif

}
void CPU::sed() {

  this->set_d_flag(1);

#ifdef LOGGING
  puts("SED");
#endif
}
void CPU::sei() {
  this->set_i_flag(1);

#ifdef LOGGING
  puts("SEI");
#endif
}
void CPU::sta(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
#ifdef LOGGING
  printf("STA %x (%x)\n", address, this->a);
#endif
  write_memory(address, this->a);
}

void CPU::stx(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  this->write_memory(address, this->x);

#ifdef LOGGING
  printf("STX %x\n", address);
#endif

}
void CPU::sty(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  this->write_memory(address, this->y);

#ifdef LOGGING
  printf("STY %x\n", address);
#endif

}
void CPU::tax() {
  this->x = this->a;
  this->calc_zero(this->x);
  this->calc_negative(this->x);

#ifdef LOGGING
  puts("TAX");
#endif

}
void CPU::tay() {
  this->y = this->a;
  this->calc_zero(this->y);
  this->calc_negative(this->y);

#ifdef LOGGING
  puts("TAY");
#endif

}
void CPU::tsx() {
  this->x = this->sp;
  this->calc_zero(this->x);
  this->calc_negative(this->x);

#ifdef LOGGING
  puts("TSX");
#endif

}
void CPU::txa() {
  this->a = this->x;
  this->calc_zero(this->a);
  this->calc_negative(this->a);

#ifdef LOGGING
  puts("TXA");
#endif

}
void CPU::txs() {
  this->sp = this->x;

#ifdef LOGGING
  puts("TXS");
#endif

}
void CPU::tya() {
  this->a = this->y;
  this->calc_zero(this->a);
  this->calc_negative(this->a);

#ifdef LOGGING
  puts("TYA");
#endif

}
void CPU::bcs() {
  if (this->get_c_flag()) {
	const uint16_t address = this->get_memory_address(relative);
	this->pc += (char)address;
  } else {
	this->pc++;
  }

#ifdef LOGGING
  printf("BCS %x\n", this->pc);
#endif

}





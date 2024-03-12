#include <cassert>
#include "cpu.h"
void CPU::exec(uint8_t opcode) {

}
void CPU::init(uint16_t prg_size) {

}
void CPU::clear_memory() {

}
void CPU::call_nmi() {

}
bool CPU::get_c_flag() {
  return false;
}
void CPU::set_c_flag(uint8_t value) {

}
bool CPU::get_z_flag() {
  return false;
}
void CPU::set_z_flag(const uint8_t value) {

}
bool CPU::get_i_flag() {
  return false;
}
void CPU::set_i_flag(const int8_t value) {

}
bool CPU::get_d_flag() {
  return false;
}
void CPU::set_d_flag(const int8_t value) {

}
bool CPU::get_b_flag() {
  return false;
}
void CPU::set_b_flag(const int8_t value) {

}
bool CPU::get_v_flag() {
  return false;
}
void CPU::set_v_flag(const int8_t value) {

}
bool CPU::get_n_flag() {
  return false;
}
void CPU::set_n_flag(const int8_t value) {

}
uint16_t CPU::stack_pop_16() {
  const uint16_t result =
	  (uint16_t)(this->read_memory(STACK_BASE + (this->sp + 2)) << 8) | (uint16_t)
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
  const int8_t a_sign = this->a & 0x80;
  const int8_t operand_sign = operand & (short)0x80;
  const int8_t result_sign = result & 0x80;

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
	  break;

	case accumulator: break;

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
	  const uint8_t low_uint8_t = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t high_uint8_t = this->read_memory(this->pc);
	  this->pc++;
	  return ((uint16_t)(high_uint8_t << 8)) | low_uint8_t;
	}

	case absolute_x: {
	  const uint8_t low_uint8_t = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t high_uint8_t = this->read_memory(this->pc);
	  this->pc++;
	  uint16_t address = ((uint16_t)(high_uint8_t << 8)) | low_uint8_t;
	  address += this->x;
	  return address;
	}

	case absolute_y: {
	  const uint8_t low_uint8_t = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t high_uint8_t = this->read_memory(this->pc);
	  this->pc++;
	  uint16_t address = ((uint16_t)(high_uint8_t << 8)) | low_uint8_t;
	  address += this->y;
	  return address;
	}

	case indirect: {
	  const uint8_t low_uint8_t = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t high_uint8_t = this->read_memory(this->pc);
	  this->pc++;
	  const uint16_t address = ((uint16_t)(high_uint8_t << 8)) | low_uint8_t;

	  const uint8_t indirect_lo_uint8_t = this->read_memory(address);
	  const uint8_t indirect_hi_uint8_t = this->read_memory(address + 1);

	  const uint16_t indirect_address = ((uint16_t)(indirect_hi_uint8_t << 8)) | indirect_lo_uint8_t;

	  return indirect_address;
	}

	case indexed_indirect: {

	  const uint8_t vector = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t low_uint8_t = this->read_memory((vector + this->x) & 0xFF);
	  const uint8_t high_uint8_t = this->read_memory((vector + this->x + 1) & 0xFF);
	  return ((uint16_t)(high_uint8_t << 8)) | low_uint8_t;
	}

	case indirect_indexed: {
	  const uint8_t vector = this->read_memory(this->pc);
	  this->pc++;
	  const uint8_t low_uint8_t = this->read_memory(vector);
	  const uint8_t high_uint8_t = this->read_memory((vector + 1) & 0xFF);

	  return (((uint16_t)(high_uint8_t << 8)) | low_uint8_t) + this->y;
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

	case PPU_STATUS: this->ppu.set_ppu_latch(false);
	  return this->ppu.registers.ppu_status;
	case OAM_ADDR: return this->ppu.registers.oam_addr;
	case OAM_DATA: return this->ppu.registers.oam_data;
	case PPU_ADDR: return this->ppu.registers.ppu_addr;
	case PPU_DATA: return this->ppu.registers.ppu_data;
	case CONTROLLER_1: return this->controller->read_next_button();
	default: return read_memory_at_address(address);
  }
}
void CPU::write_memory(uint16_t address, uint8_t value) {
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
	  if (this->ppu.get_ppu_latch()) {
		this->ppu.registers.ppu_scroll_y = value;
		this->ppu.set_ppu_latch(false);
	  } else {
		this->ppu.registers.ppu_scroll_x = value;
		this->ppu.set_ppu_latch(true);
	  }
	}
	  break;

	case PPU_ADDR: {
	  if (this->ppu.get_ppu_latch()) {
		this->ppu.set_ppu_data_addr(this->ppu.get_ppu_data_addr() | (uint16_t)value);
		this->ppu.set_ppu_latch(false);
	  } else {
		this->ppu.set_ppu_data_addr((uint16_t)(value << 8));
		this->ppu.set_ppu_latch(true);
	  }
	  assert(this->ppu.get_ppu_data_addr() < VRAM_SIZE);
	}
	  break;

	case PPU_DATA: assert(this->ppu.get_ppu_data_addr() <= VRAM_SIZE - 1);
	  this->ppu.memory.data[this->ppu.get_ppu_data_addr()] = value;
	  if (this->ppu.registers.ppu_ctrl & 0b00000100) {
		this->ppu.set_ppu_data_addr(this->ppu.get_ppu_data_addr() + 32);
	  } else {
		this->ppu.set_ppu_data_addr(this->ppu.get_ppu_data_addr() + 1);
	  }
	  break;

	case OAM_DMA: {
	  for (uint16_t i = 0; i < 256; ++i) {
		const uint16_t oam_copy_address = (uint16_t)(value << 8) + i;
		this->ppu.oam.data[i] = read_memory(oam_copy_address);
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
  this->y = read_memory(address);
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
  printf("ADC %x\n", memory);
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
	const uint16_t address = get_memory_address(AddressMode::relative);
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
	const uint16_t address = get_memory_address(AddressMode::relative);
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
  this->set_c_flag(AddressMode::implicit);
#ifdef LOGGING
  printf("CLC\n");
#endif
}

void CPU::cld() {
  this->set_d_flag(AddressMode::implicit);
#ifdef LOGGING
  printf("CLD\n");
#endif
}
void CPU::cli() {
  this->set_i_flag(AddressMode::implicit);
#ifdef LOGGING
  printf("CLI\n");
#endif
}
void CPU::clv() {
  this->set_v_flag(AddressMode::implicit);
#ifdef LOGGING
  printf("CLV\n");
#endif
}
void CPU::cmp(AddressMode address_mode) {
  const uint16_t address = this->get_memory_address(address_mode);
  const uint8_t mem = this->read_memory(address);
  const uint8_t result = this->a - mem;

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

  const int result = this->x - (int)mem;

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

  const int result = this->y - (int)mem;

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



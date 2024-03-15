#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#include "gtest/gtest.h"

#include "../nes_emulator/cpu.h"
#include "../nes_emulator/cpu.cpp"
#include "../nes_emulator/NES.h"
#include "../nes_emulator/Controller.cpp"
#include "../nes_emulator/PPU.cpp"

class LDATestsFixture : public ::testing::Test {
 protected:
  void SetUp() override {
	nes = new NES{};
	nes->cpu.clear_memory();

	// reset vector
	nes->cpu.memory.data[0xFFFC] = 0x00;
	nes->cpu.memory.data[0xFFFD] = 0x80;

	nes->cpu.init(0x8000);
	nes->cpu.pc = 0x8001;
  }
  void TearDown() override {
	delete nes;
  }
  NES *nes;
};
TEST_F(LDATestsFixture, ImmediatePositiveNumber) {
  // immediate value
  nes->cpu.memory.data[0x8001] = 0x11;

  // LDA immediate
  nes->cpu.exec(0xA9);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x11);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, ImmediateNegativeNumber) {
  // immediate value
  nes->cpu.memory.data[0x8001] = -10;

  // LDA immediate
  nes->cpu.exec(0xA9);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0xF6);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_TRUE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, ImmediateZero) {

  // immediate value
  nes->cpu.memory.data[0x8001] = 0x00;

  // LDA immediate
  nes->cpu.exec(0xA9);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x00);
  ASSERT_TRUE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, ZeroPagePositiveNumber) {
  // pointer
  nes->cpu.memory.data[0x8001] = 0x55;

  // value
  nes->cpu.memory.data[0x0055] = 0x11;

  // LDA zero page
  nes->cpu.exec(0xA5);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x11);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, ZeroPageNegativeNumber) {
  // pointer
  nes->cpu.memory.data[0x8001] = 0x55;

  // value
  nes->cpu.memory.data[0x0055] = -10;

  // LDA zero page
  nes->cpu.exec(0xA5);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0xF6);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_TRUE(nes->cpu.get_n_flag());
}

TEST_F(LDATestsFixture, ZeroPageZero) {
  // pointer
  nes->cpu.memory.data[0x8001] = 0x55;

  // value
  nes->cpu.memory.data[0x0055] = 0x00;

  // LDA zero page
  nes->cpu.exec(0xA5);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x00);
  ASSERT_TRUE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}

TEST_F(LDATestsFixture, ZeroPageXPositiveNumber) {
  // pointer
  nes->cpu.memory.data[0x8001] = 0x55;

  // value
  nes->cpu.memory.data[0x0065] = 0x11;

  nes->cpu.x = 0x10;
  // LDA zero page x
  nes->cpu.exec(0xB5);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x11);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}

TEST_F(LDATestsFixture, ZeroPageXNegativeNumber) {
  // pointer
  nes->cpu.memory.data[0x8001] = 0x55;

  // value
  nes->cpu.memory.data[0x0065] = -10;

  nes->cpu.x = 0x10;
  // LDA zero page x
  nes->cpu.exec(0xB5);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0xF6);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_TRUE(nes->cpu.get_n_flag());
}

TEST_F(LDATestsFixture, ZeroPageXZero) {
  // pointer
  nes->cpu.memory.data[0x8001] = 0x55;

  // value
  nes->cpu.memory.data[0x0065] = 0x00;

  nes->cpu.x = 0x10;
  // LDA zero page x
  nes->cpu.exec(0xB5);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x00);
  ASSERT_TRUE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}

TEST_F(LDATestsFixture, AbsolutePositiveNumber) {
  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;
  // value
  nes->cpu.memory.data[0x5501] = 0x11;

  // LDA absolute
  nes->cpu.exec(0xAD);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0x11);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}

TEST_F(LDATestsFixture, AbsoluteNegativeNumber) {
  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;
  // value
  nes->cpu.memory.data[0x5501] = -10;

  // LDA absolute
  nes->cpu.exec(0xAD);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0xF6);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_TRUE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, AbsoluteZero) {
  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;
  // value
  nes->cpu.memory.data[0x5501] = 0x00;

  // LDA absolute
  nes->cpu.exec(0xAD);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0x00);
  ASSERT_TRUE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, AbsoluteXPositiveNumber) {
  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;

  // 0x5501 + 0x10 = 0x5511
  // This is the value that will be loaded into the accumulator
  nes->cpu.memory.data[0x5511] = 0x50;

  // LDA absolute x uses the x register to offset the address
  // 0x5501 + 0x10 = 0x5511
  nes->cpu.x = 0x10;

  // LDA absolute x
  nes->cpu.exec(0xBD);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0x50);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, AbsoluteXNegativeNumber) {
  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;

  // 0x5501 + 0x10 = 0x5511
  // This is the value that will be loaded into the accumulator
  nes->cpu.memory.data[0x5511] = -10;

  nes->cpu.pc = 0x8001;

  // LDA absolute x uses the x register to offset the address
  // 0x5501 + 0x10 = 0x5511
  nes->cpu.x = 0x10;

  // LDA absolute x
  nes->cpu.exec(0xBD);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0xF6); // 0xF6 is -10 in 2's complement
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_TRUE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, AbsoluteXZero) {
  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;
  // value
  nes->cpu.memory.data[0x5501] = 0x00;

  nes->cpu.x = 0x10;
  // LDA absolute x
  nes->cpu.exec(0xBD);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0x00);
  ASSERT_TRUE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}

TEST_F(LDATestsFixture, AbsoluteYPositiveNumber) {
  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;

  // 0x5501 + 0x10 = 0x5511
  // This is the value that will be loaded into the accumulator
  nes->cpu.memory.data[0x5511] = 0x50;

  // LDA absolute y uses the y register to offset the address
  // 0x5501 + 0x10 = 0x5511
  nes->cpu.y = 0x10;

  // LDA absolute y
  nes->cpu.exec(0xB9);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0x50);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, AbsoluteYNegativeNumber) {
  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;

  // 0x5501 + 0x10 = 0x5511
  // This is the value that will be loaded into the accumulator
  nes->cpu.memory.data[0x5511] = -10;

  // LDA absolute y uses the y register to offset the address
  // 0x5501 + 0x10 = 0x5511
  nes->cpu.y = 0x10;

  // LDA absolute y
  nes->cpu.exec(0xB9);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0xF6); // 0xF6 is -10 in 2's complement
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_TRUE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, AbsoluteYZero) {
  nes->cpu.clear_memory();

  // low byte
  nes->cpu.memory.data[0x8001] = 0x01;
  // high byte
  nes->cpu.memory.data[0x8002] = 0x55;

  // 0x5501 + 0x10 = 0x5511
  // This is the value that will be loaded into the accumulator
  nes->cpu.memory.data[0x5511] = 0x00;

  // LDA absolute y uses the y register to offset the address
  // 0x5501 + 0x10 = 0x5511
  nes->cpu.y = 0x10;

  // LDA absolute y
  nes->cpu.exec(0xB9);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8003);
  ASSERT_EQ(nes->cpu.a, 0x00);
  ASSERT_TRUE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, IndirectXPositiveNumber) {
  nes->cpu.clear_memory();
  
  // first part of the vector
  nes->cpu.memory.data[0x8001] = 0x02;

  // 0x02 + 0x10 = 0x12
  // low byte
  nes->cpu.memory.data[0x12] = 0x11;
  // high byte
  nes->cpu.memory.data[0x13] = 0x01;

  // value
  nes->cpu.memory.data[0x0111] = 0x55;

  // LDA indirect x uses the x register to offset the first part of the vector
  // 0x02 + 0x10 = 0x12
  nes->cpu.x = 0x10;
  
  // LDA indirect x
  nes->cpu.exec(0xA1);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x55);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, IndirectXNegativeNumber) {
  nes->cpu.clear_memory();

  // first part of the vector
  nes->cpu.memory.data[0x8001] = 0x02;

  // 0x02 + 0x10 = 0x12
  // low byte
  nes->cpu.memory.data[0x12] = 0x11;
  // high byte
  nes->cpu.memory.data[0x13] = 0x01;

  // value
  nes->cpu.memory.data[0x0111] = -10;

  // LDA indirect x uses the x register to offset the first part of the vector
  // 0x02 + 0x10 = 0x12
  nes->cpu.x = 0x10;

  // LDA indirect x
  nes->cpu.exec(0xA1);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0xF6); // 0xF6 is -10 in 2's complement
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_TRUE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, IndirectXZero) {
  nes->cpu.clear_memory();

  // first part of the vector
  nes->cpu.memory.data[0x8001] = 0x02;

  // 0x02 + 0x10 = 0x12
  // low byte
  nes->cpu.memory.data[0x12] = 0x11;
  // high byte
  nes->cpu.memory.data[0x13] = 0x01;

  // value
  nes->cpu.memory.data[0x0111] = 0;

  // LDA indirect x uses the x register to offset the first part of the vector
  // 0x02 + 0x10 = 0x12
  nes->cpu.x = 0x10;

  // LDA indirect x
  nes->cpu.exec(0xA1);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x00);
  ASSERT_TRUE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, IndirectYPositiveNumber) {
  nes->cpu.clear_memory();

  // Zero page pointer
  nes->cpu.memory.data[0x8001] = 0x02;

  // low byte
  nes->cpu.memory.data[0x02] = 0x11;
  
  // high byte
  nes->cpu.memory.data[0x03] = 0x01;

  // 0x0111 + 0x10 = 0x0121
  nes->cpu.memory.data[0x0121] = 0x55;

  // LDA indirect y uses the y register to offset the address we get from the zero-page pointer
  // First part of the pointer is 0x02, so we go to 0x02, fetch the low byte, go to 0x03, fetch the high byte.
  // In this case the address is 0x0111, we add 0x10 from the Y register to it and get 0x0121. That's
  // the address we will use to load the value into the accumulator
  nes->cpu.y = 0x10;
  
  // LDA indirect y
  nes->cpu.exec(0xB1);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x55);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, IndirectYNegativeNumber) {
  nes->cpu.clear_memory();

  // Zero page pointer
  nes->cpu.memory.data[0x8001] = 0x02;

  // low byte
  nes->cpu.memory.data[0x02] = 0x11;

  // high byte
  nes->cpu.memory.data[0x03] = 0x01;

  // 0x0111 + 0x10 = 0x0121
  nes->cpu.memory.data[0x0121] = -10;

  // LDA indirect y uses the y register to offset the address we get from the zero-page pointer
  // First part of the pointer is 0x02, so we go to 0x02, fetch the low byte, go to 0x03, fetch the high byte.
  // In this case the address is 0x0111, we add 0x10 from the Y register to it and get 0x0121. That's
  // the address we will use to load the value into the accumulator
  nes->cpu.y = 0x10;

  // LDA indirect y
  nes->cpu.exec(0xB1);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0xF6); // 0xF6 is -10 in 2's complement
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_TRUE(nes->cpu.get_n_flag());
}

TEST_F(LDATestsFixture, IndirectYZero) {
  nes->cpu.clear_memory();

  // Zero page pointer
  nes->cpu.memory.data[0x8001] = 0x02;

  // low byte
  nes->cpu.memory.data[0x02] = 0x11;

  // high byte
  nes->cpu.memory.data[0x03] = 0x01;

  // 0x0111 + 0x10 = 0x0121
  nes->cpu.memory.data[0x0121] = 0;

  // LDA indirect y uses the y register to offset the address we get from the zero-page pointer
  // First part of the pointer is 0x02, so we go to 0x02, fetch the low byte, go to 0x03, fetch the high byte.
  // In this case the address is 0x0111, we add 0x10 from the Y register to it and get 0x0121. That's
  // the address we will use to load the value into the accumulator
  nes->cpu.y = 0x10;
  
  // LDA indirect y
  nes->cpu.exec(0xB1);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x00);
  ASSERT_TRUE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}
TEST_F(LDATestsFixture, ZeroPageXBoundary) {
  nes->cpu.clear_memory();

  // pointer
  nes->cpu.memory.data[0x8001] = 0xFF;

  // 0xFF + 0x01 = 0x00 because of the wrap-around at the boundary
  nes->cpu.memory.data[0x0000] = 0x55;

  nes->cpu.x = 0x01;
  // LDA zero page x
  nes->cpu.exec(0xB5);

  ASSERT_EQ(nes->cpu.sp, 0xFF);
  ASSERT_EQ(nes->cpu.pc, 0x8002);
  ASSERT_EQ(nes->cpu.a, 0x55);
  ASSERT_FALSE(nes->cpu.get_z_flag());
  ASSERT_FALSE(nes->cpu.get_n_flag());
}

#pragma clang diagnostic pop
#ifndef NES_EMULATOR_CPP_NES_H_
#define NES_EMULATOR_CPP_NES_H_

#include "cpu.h"

class NES {
 public:
  CPU cpu;
  Controller controller;
};

#endif //NES_EMULATOR_CPP_NES_H_

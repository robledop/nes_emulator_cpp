#ifndef NES_EMULATOR_CPP_CONTROLLER_H_
#define NES_EMULATOR_CPP_CONTROLLER_H_

#include <cstdint>
#include <SDL_events.h>
class Controller {
 public:
  bool latch;
  uint8_t current_read;
  uint8_t buttons[8];
  void init();
  uint8_t read_next_button();
  void handle_input(const SDL_Event *event);
  void write(uint8_t value);
};

#endif //NES_EMULATOR_CPP_CONTROLLER_H_

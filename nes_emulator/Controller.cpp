#include "Controller.h"
void Controller::init() {
  this->current_read = 0;
  for (unsigned char &button : this->buttons) {
	button = 0;
  }
}
uint8_t Controller::read_next_button() {
  const uint8_t button_value = this->buttons[this->current_read++];
  this->current_read %= 8;
  return button_value;
}
void Controller::handle_input(const SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
	switch (event->key.keysym.sym) {
	  case SDLK_z: this->buttons[0] = 1; // A
		break;
	  case SDLK_x: this->buttons[1] = 1; // B
		break;
	  case SDLK_SPACE: this->buttons[2] = 1; // Select
		break;
	  case SDLK_RETURN: this->buttons[3] = 1; // Start
		break;
	  case SDLK_UP: this->buttons[4] = 1; // Up
		break;
	  case SDLK_DOWN: this->buttons[5] = 1; // Down
		break;
	  case SDLK_LEFT: this->buttons[6] = 1; // Left
		break;
	  case SDLK_RIGHT: this->buttons[7] = 1; // Right
		break;
	  default: break;
	}
  } else if (event->type == SDL_KEYUP) {
	switch (event->key.keysym.sym) {
	  case SDLK_z: this->buttons[0] = 0; // A
		break;
	  case SDLK_x: this->buttons[1] = 0; // B
		break;
	  case SDLK_SPACE: this->buttons[2] = 0; // Select
		break;
	  case SDLK_RETURN: this->buttons[3] = 0; // Start 
		break;
	  case SDLK_UP: this->buttons[4] = 0; // Up
		break;
	  case SDLK_DOWN: this->buttons[5] = 0; // Down
		break;
	  case SDLK_LEFT: this->buttons[6] = 0; // Left
		break;
	  case SDLK_RIGHT: this->buttons[7] = 0; // Right
		break;
	  default: break;
	}
  }
}
void Controller::write(const uint8_t value) {
  if (this->latch && value == 0) {
	this->current_read = 0;
  }

  this->latch = value;
}

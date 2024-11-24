
#include <button.h>

Button::Button(struct gpio_dt_spec* spec, struct gpio_callback* callback,
               ChessColor color, ButtonType type) {
  this->spec = spec;
  this->callback = callback;
  this->color = color;
  this->type = type;
}

Button::~Button() {
  this->spec = nullptr;
  this->callback = nullptr;
  this->color = ChessColor::White;
  this->type = ButtonType::Up;
}
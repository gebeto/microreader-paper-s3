#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <Arduino.h>

#include "../rendering/TextRenderer.h"
#include "../resources/fonts/FontManager.h"

class TouchButton {
  String title = "";
  int16_t x, y, w, h;
  uint16_t margin_x = 0;
  uint16_t margin_y = 0;

 public:
  TouchButton(int16_t x, int16_t y, int16_t w, int16_t h);
  TouchButton(String title, int16_t x, int16_t y, int16_t w, int16_t h);

  void set_margin(uint16_t margin);
  void set_margin_x(uint16_t margin_x);
  void set_margin_y(uint16_t margin_y);
  bool overlap(int16_t touchX, int16_t touchY);
  void render(TextRenderer& textRenderer);
};

#endif
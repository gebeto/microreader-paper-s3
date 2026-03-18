#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <Arduino.h>

#include "../rendering/TextRenderer.h"
#include "../resources/fonts/FontManager.h"


struct Point {
  int16_t x;
  int16_t y;
};

struct Size {
  int16_t width;
  int16_t height;
};

struct Rect {
  Point position;
  Size size;
};

struct Sides {
  int16_t left;
  int16_t right;
  int16_t top;
  int16_t bottom;
};

class TouchButton {
  String title = "";
  int16_t x, y, w, h;

  uint16_t border_width = 2;
  Sides margin;

  uint16_t Icon_w = 0;
  uint16_t Icon_h = 0;
  const unsigned char* Icon;

 public:
  TouchButton(int16_t x, int16_t y, int16_t w, int16_t h);
  TouchButton(String title, int16_t x, int16_t y, int16_t w, int16_t h);

  void set_border_width(uint16_t border_width);
  void set_margin(uint16_t margin);
  void set_margins(uint16_t left, uint16_t right, uint16_t top, uint16_t bottom);
  void set_margin_x(uint16_t margin_x);
  void set_margin_y(uint16_t margin_y);

  void set_icon(const unsigned char* Icon, uint16_t w, uint16_t h);

  bool overlap(int16_t touchX, int16_t touchY);
  void render(TextRenderer& textRenderer);
};

#endif
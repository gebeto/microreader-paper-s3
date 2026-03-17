#include "TouchButton.h"

TouchButton::TouchButton(int16_t x, int16_t y, int16_t w, int16_t h) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

TouchButton::TouchButton(String title, int16_t x, int16_t y, int16_t w, int16_t h) {
  this->title = title;
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

void TouchButton::set_icon(const unsigned char* Icon, uint16_t w, uint16_t h) {
  this->Icon = Icon;
  this->Icon_w = w;
  this->Icon_h = h;
}

void TouchButton::set_margin(uint16_t margin) {
  this->margin_x = margin;
  this->margin_y = margin;
}

void TouchButton::set_margin_x(uint16_t margin_x) {
  this->margin_x = margin_x;
}

void TouchButton::set_margin_y(uint16_t margin_y) {
  this->margin_y = margin_y;
}

bool TouchButton::overlap(int16_t touchX, int16_t touchY) {
  return touchX > this->x && touchX < this->x + this->w && touchY > this->y && touchY < this->y + this->h;
}

void TouchButton::render(TextRenderer& textRenderer) {
  textRenderer.drawRectIn(x + margin_x, y + margin_y, w - margin_x * 2, h - margin_y * 2, 2, true);

  int16_t textX, textY;
  uint16_t textW, textH;
  textRenderer.setFont(getTitleFont());
  textRenderer.getTextBounds(title.c_str(), 0, 0, &textX, &textY, &textW, &textH);
  int16_t centerX = this->x + this->w / 2 - textW / 2;
  int16_t indicatorY = (this->y + this->h / 2) + textH / 2 - 7;
  textRenderer.setCursor(centerX, indicatorY);
  textRenderer.print(title);
  // textRenderer.drawRect(centerX, indicatorY - textH, textW, textH, 1);

  if (this->Icon && this->Icon_w && this->Icon_h) {
    int iconCenterX = x + this->w/2 - this->Icon_w/2 + 4;
    int iconCenterY = y + this->h/2 - this->Icon_h/2;
    textRenderer.drawImage(this->Icon, iconCenterX, iconCenterY, this->Icon_w, this->Icon_h);
  }
}
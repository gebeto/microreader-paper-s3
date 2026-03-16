#ifndef CHAPTERS_SCREEN_H
#define CHAPTERS_SCREEN_H

#include <Arduino.h>

#include "../../core/EInkDisplay.h"
#include "../../core/TouchButton.h"
#include "../../rendering/TextRenderer.h"
#include "Screen.h"

class UIManager;

class ChaptersScreen : public Screen {
 public:
  ChaptersScreen(EInkDisplay& display, TextRenderer& renderer, UIManager& uiManager);

  void begin() override {}
  void activate() override;
  void show() override;
  void handleButtons(class Buttons& buttons) override;

 private:
  void render();
  void selectNext();
  void selectPrev();
  void confirm();

  int getChapterCount() const;
  String getChapterLabel(int index) const;
  void buildFilteredChapterList();
  int getActualChapterIndex(int filteredIndex) const;

  EInkDisplay& display;
  TextRenderer& textRenderer;
  UIManager& uiManager;

  int16_t lastTouchX = -1;
  int16_t lastTouchY = -1;
  bool touchPressed = false;
  TouchButton* buttonPrev;
  TouchButton* buttonNext;
  TouchButton* buttonSelect;
  TouchButton* buttonBack;

  int selectedIndex = 0;
  
  // Filtered list of non-empty chapter indices
  static constexpr int MAX_CHAPTERS = 200;
  int filteredChapters[MAX_CHAPTERS];
  int filteredCount = 0;
  int indexByUnfiltered[MAX_CHAPTERS];
};

#endif

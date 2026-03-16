#include "ChaptersScreen.h"

#include <resources/fonts/FontManager.h>

#include "../../core/Buttons.h"
#include "../UIManager.h"
#include "TextViewerScreen.h"

ChaptersScreen::ChaptersScreen(EInkDisplay& display, TextRenderer& renderer, UIManager& uiManager)
    : display(display),
      textRenderer(renderer),
      uiManager(uiManager),
      buttonPrev(new TouchButton("↑", 180, EInkDisplay::DISPLAY_HEIGHT - 180, 180, 90)),
      buttonNext(new TouchButton("↓", 180, EInkDisplay::DISPLAY_HEIGHT - 90, 180, 90)),
      buttonSelect(new TouchButton("Select", 360, EInkDisplay::DISPLAY_HEIGHT - 180, 180, 180)),
      buttonBack(new TouchButton("←", 0, EInkDisplay::DISPLAY_HEIGHT - 180, 180, 180)) {
  buttonPrev->set_margin(10);
  buttonNext->set_margin(10);
  buttonSelect->set_margin(10);
  buttonBack->set_margin(10);
}

void ChaptersScreen::activate() {
  buildFilteredChapterList();
  selectedIndex = 0;
}

void ChaptersScreen::handleButtons(Buttons& buttons) {
  int16_t touchX, touchY;
  const bool touching = buttons.getTouchPosition(touchX, touchY);

  if (touching) {
    if (!touchPressed) {
      Serial.printf("Press");
      touchPressed = true;
      if (buttonPrev->overlap(touchX, touchY)) {
        Serial.printf("UP\n");
        selectPrev();
      } else if (buttonNext->overlap(touchX, touchY)) {
        Serial.printf("DOWN\n");
        selectNext();
      } else if (buttonBack->overlap(touchX, touchY)) {
        Serial.printf("BACK\n");
        uiManager.showScreen(UIManager::ScreenId::Settings);
      } else if (buttonSelect->overlap(touchX, touchY)) {
        Serial.printf("SELECT\n");
        confirm();
      }
    }
  }

  if (buttons.wasTouchReleased()) {
    touchPressed = false;
    lastTouchX = -1;
    lastTouchY = -1;
  }

  return;

  if (buttons.isPressed(Buttons::BACK)) {
    uiManager.showScreen(UIManager::ScreenId::Settings);
  } else if (buttons.isPressed(Buttons::LEFT)) {
    selectNext();
  } else if (buttons.isPressed(Buttons::RIGHT)) {
    selectPrev();
  } else if (buttons.isPressed(Buttons::CONFIRM)) {
    confirm();
  }
}

void ChaptersScreen::show() {
  render();
  buttonPrev->render(textRenderer);
  buttonSelect->render(textRenderer);
  buttonNext->render(textRenderer);
  buttonBack->render(textRenderer);
  display.displayBuffer(EInkDisplay::FAST_REFRESH);
}

int ChaptersScreen::getChapterCount() const {
  return filteredCount;
}

void ChaptersScreen::buildFilteredChapterList() {
  filteredCount = 0;
  Screen* s = uiManager.getScreen(UIManager::ScreenId::TextViewer);
  TextViewerScreen* tv = static_cast<TextViewerScreen*>(s);
  if (!tv)
    return;

  int totalChapters = tv->getChapterCount();
  for (int i = 0; i < totalChapters && filteredCount < MAX_CHAPTERS; i++) {
    if (!tv->isChapterEmpty(i)) {
      filteredChapters[filteredCount++] = i;
    }
  }
}

int ChaptersScreen::getActualChapterIndex(int filteredIndex) const {
  if (filteredIndex < 0 || filteredIndex >= filteredCount)
    return 0;
  return filteredChapters[filteredIndex];
}

String ChaptersScreen::getChapterLabel(int index) const {
  Screen* s = uiManager.getScreen(UIManager::ScreenId::TextViewer);
  TextViewerScreen* tv = static_cast<TextViewerScreen*>(s);
  if (!tv)
    return String("");

  int actualIndex = getActualChapterIndex(index);
  String name = tv->getChapterName(actualIndex);
  if (name.length() == 0) {
    return String("Chapter ") + String(index + 1);
  }

  if (name.length() > 40) {
    name = name.substring(0, 37) + "...";
  }
  return name;
}

void ChaptersScreen::render() {
  display.clearScreen(0xFF);
  textRenderer.setTextColor(TextRenderer::COLOR_BLACK);
  textRenderer.setFont(getTitleFont());

  textRenderer.setFrameBuffer(display.getFrameBuffer());
  textRenderer.setBitmapType(TextRenderer::BITMAP_BW);

  uiManager.renderStatusHeader(textRenderer);

  textRenderer.setFont(getTitleFont());

  const int16_t pageW = (int16_t)EInkDisplay::DISPLAY_WIDTH;
  const int16_t pageH = (int16_t)EInkDisplay::DISPLAY_HEIGHT;

  {
    const char* title = "Chapters";
    int16_t x1, y1;
    uint16_t w, h;
    textRenderer.getTextBounds(title, 0, 0, &x1, &y1, &w, &h);
    int16_t centerX = (pageW - (int)w) / 2;
    textRenderer.setCursor(centerX, 75);
    textRenderer.print(title);
  }

  textRenderer.setFont(getMainFont());

  int count = getChapterCount();
  if (count <= 0) {
    return;
  }

  const int lineHeight = 28;
  int maxLines = 16;
  if (count < maxLines)
    maxLines = count;

  int startIndex = 0;
  if (selectedIndex >= maxLines) {
    startIndex = selectedIndex - (maxLines - 1);
  }

  int totalHeight = maxLines * lineHeight;
  int startY = (pageH - totalHeight) / 2;

  for (int i = 0; i < maxLines; ++i) {
    int idx = startIndex + i;
    String line = getChapterLabel(idx);
    if (idx == selectedIndex) {
      line = String("> ") + line + String(" <");
    } else {
      line = String("  ") + line + String("  ");
    }

    int16_t x1, y1;
    uint16_t w, h;
    textRenderer.getTextBounds(line.c_str(), 0, 0, &x1, &y1, &w, &h);
    int16_t centerX = (pageW - (int)w) / 2;
    int16_t rowY = startY + i * lineHeight;
    textRenderer.setCursor(centerX, rowY);
    textRenderer.print(line);
  }
}

void ChaptersScreen::selectNext() {
  int count = getChapterCount();
  if (count <= 0)
    return;
  selectedIndex++;
  if (selectedIndex >= count)
    selectedIndex = 0;
  show();
}

void ChaptersScreen::selectPrev() {
  int count = getChapterCount();
  if (count <= 0)
    return;
  selectedIndex--;
  if (selectedIndex < 0)
    selectedIndex = count - 1;
  show();
}

void ChaptersScreen::confirm() {
  Screen* s = uiManager.getScreen(UIManager::ScreenId::TextViewer);
  TextViewerScreen* tv = static_cast<TextViewerScreen*>(s);
  if (!tv)
    return;

  int actualIndex = getActualChapterIndex(selectedIndex);
  tv->goToChapterStart(actualIndex);
  uiManager.showScreen(UIManager::ScreenId::TextViewer);
}

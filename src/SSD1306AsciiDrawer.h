#ifndef __SSD1306AsciiDrawer_h__
#define __SSD1306AsciiDrawer_h__

#include <MenuLib.h>
#include "SSD1306AsciiWire.h"

#define NORMAL_FONT X11fixed7x14
#define HEADER_FONT X11fixed7x14B
#define ITEMS_PER_SCREEN 3

class SSD1306AsciiDrawer : public MenuItemDrawer {
  private:
    SSD1306AsciiWire& oled;

    void drawMenu(Menu* menu);
    //void drawAction(Action<T>* action);
    void drawSelector(NumericSelectorUint8* selector);
    void drawSelector(NumericSelectorInt16* selector);
    void drawSelector(NumericSelectorList* selector);
    uint8_t colSecondary;
    uint8_t selectedLine;

  public:
    SSD1306AsciiDrawer(SSD1306AsciiWire &oled, uint8_t colSecondary = 12*7)  : oled(oled) {
      this->colSecondary = colSecondary;
    }
    void draw(MenuItem* item);

};

#endif

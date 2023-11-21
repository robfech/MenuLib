#ifndef __SSD1306AsciiDrawer_h__
#define __SSD1306AsciiDrawer_h__

#include <MenuLib.h>
#include "SSD1306AsciiWire.h"

#define NORMAL_FONT X11fixed7x14
#define HEADER_FONT X11fixed7x14B

class SSD1306AsciiDrawer : public MenuItemDrawer {
  protected:
    SSD1306AsciiWire& oled;

    // uint8_t displayRows = oled.displayRows()/oled.fontRows();
    // uint8_t itemsPerScreen = displayRows - 1;

  private:

      void drawMenu(Menu* menu);
      //void drawAction(Action<T>* action);
      void drawSelector(NumericSelector* selector);

  public:
    SSD1306AsciiDrawer(SSD1306AsciiWire &oled): oled(oled) {}
    void draw(MenuItem* item);
};

#endif

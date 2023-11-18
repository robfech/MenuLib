#ifndef __ssd1306_drawer_h__
#define __ssd1306_drawer_h__

#include <MenuLib.h>
#include <SSD1306Wire.h>

#define SELECTORSSTART 16
#define SELECTORHEIGHT 10
#define SELECTORFONTMARGIN  2

#define RECT_W 76
#define RECT_H 14
#define RECT_Y 18

#define RECT_X (DISPLAY_WIDTH - RECT_W) / 2
#define TEXT_Y RECT_Y

class SSD1306Drawer : public MenuItemDrawer {

	protected:
		SSD1306Wire& lcd;

		uint8_t items_per_screen;
		
		
		uint8_t getNumLength(uint8_t num) {
			uint8_t numLength = 0, tmp;
			
			if(num == 0) return 1;
		
			// Init
			tmp = abs(num);
			
			while(tmp != 0) {
				tmp = tmp / 10;
				
				numLength++;
			}
			
			if(num < 0) numLength++;

			
			return numLength;
		}

		void drawCenterText(MenuItem* item, uint8_t y) {
			if (item->isTextFlash()) {
				const FlashString* text = reinterpret_cast<const FlashString*>(item->getText());
				
        lcd.setTextAlignment(TEXT_ALIGN_CENTER);
        lcd.drawString(DISPLAY_WIDTH/2, y, text);		
			} else {
				const char* text = item->getText();

        lcd.setTextAlignment(TEXT_ALIGN_CENTER);
        lcd.drawString(DISPLAY_WIDTH/2, y, text);
      }
      			
		}
		void drawCenterNumber(uint8_t num, uint8_t y,  uint8_t from = 0, uint8_t to = 0) {
      lcd.setTextAlignment(TEXT_ALIGN_CENTER);
      lcd.drawString(DISPLAY_WIDTH/2, y, String(num));
		}
	 
		void drawMenu(Menu* menu) {
			uint8_t i = 0, y;
			char* secText;

			drawCenterText(menu, 0);
			lcd.drawLine(0, 14, DISPLAY_WIDTH, 14) ;
	
			ListEntry *e = menu->getCollection(), *first = e;
	
			if (!e) return;

			// Each screen contains X entry; when the third is reached, the next X will be shown
			// Find the right place where to start by scanning from the top.
			do {
				// Skip disabled items
				if (e->item->isEnabled()) {					
					if (i % items_per_screen == 0)
						first = e;

					i++;
				}
				
				if (e == menu->getSelectedListEntry())
					break;

				e = e->next;
			} while(e);


			e = first;
			i = 0;

			// Now actually draw the entries
			while (e && i < items_per_screen) {
				if (e->item->isEnabled()) {

					y = SELECTORSSTART + SELECTORHEIGHT * i;

					if(e == menu->getSelectedListEntry()) {
            lcd.setColor(WHITE);
            lcd.fillRect(0, y, DISPLAY_WIDTH, SELECTORHEIGHT);
						lcd.setColor(INVERSE);
					} else
						lcd.setColor(WHITE);

					secText = (char*)e->item->getSecondaryText();

					if(secText) {
						// Draw secondary text
            lcd.setTextAlignment(TEXT_ALIGN_LEFT);
            lcd.drawString(DISPLAY_WIDTH - lcd.getStringWidth(secText) - 1, y - SELECTORFONTMARGIN, secText);					
					}
					
					// Draw item's text
					if (e->item->isTextFlash()) {
						const FlashString* text = reinterpret_cast<const FlashString*>(e->item->getText());
            lcd.setTextAlignment(TEXT_ALIGN_LEFT);
            lcd.drawString(1, y - SELECTORFONTMARGIN, text);						
					} else {
						const char* text = e->item->getText();
            lcd.setTextAlignment(TEXT_ALIGN_LEFT);
            lcd.drawString(1, y - SELECTORFONTMARGIN, text);
					}

					i++;
				}

				e = e->next;
			}
			
			lcd.setColor(WHITE);
		}

		void drawSelector(NumericSelector* selector) {
			// Draw title
			drawCenterText(selector, 0);
			lcd.drawLine(0, 14, DISPLAY_WIDTH, 14) ;
			
			// Draw a rect around the value
			lcd.setColor(WHITE);
			lcd.drawRect(RECT_X, RECT_Y, RECT_W, RECT_H);
		 
			// Some decoration
      lcd.setTextAlignment(TEXT_ALIGN_LEFT);
      lcd.drawString(RECT_X + 2, TEXT_Y, "<");			
			
			// Guess the x pos to center the value number
			if (selector->getTypeId() == 's') {                    //numeric selector
        drawCenterNumber(selector->getValue(), TEXT_Y);
      } else if (selector->getTypeId() == 't') {            //array selector
        const char* text = selector->getSecondaryText();
        lcd.setTextAlignment(TEXT_ALIGN_CENTER);
        lcd.drawString(DISPLAY_WIDTH/2, TEXT_Y, text);		            
      }
			
			// Still some decorations
      lcd.setTextAlignment(TEXT_ALIGN_LEFT);
      lcd.drawString(RECT_X + RECT_W - 8, TEXT_Y, ">");			
		}
	
		// Override this to extend functionalities
		void virtual drawOther(MenuItem* item) {};

	public:

		SSD1306Drawer(SSD1306Wire& lcd, uint8_t num_items) : lcd(lcd), items_per_screen(num_items) {}

		void draw(MenuItem* item) {
			if(!item) return;
			
			lcd.clear();

			switch(item->getTypeId()) {
				case 'm':
					drawMenu((Menu*)item);
					break;

				// Actions and Check Boxes does not need to be drawn
				// case 'a':
				// case 'c':
				case 't': //array selector
				case 's': //numeric selector
					drawSelector((NumericSelector*)item);
					break;					
				default:
					drawOther(item);
			}

			lcd.display();
		}
};

#endif

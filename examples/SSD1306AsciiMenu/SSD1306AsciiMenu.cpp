#include <Arduino.h>

// #include <Wire.h>
// #include "SSD1306Ascii.h"
// #include "SSD1306AsciiWire.h"
#include <MenuLib.h>
#include "SSD1306AsciiDrawer.h"

#define I2C_ADDRESS 0x3C
SSD1306AsciiWire oled;

Menu* root = new Menu(NULL, NULL);
SSD1306AsciiDrawer* dr = new SSD1306AsciiDrawer(oled);
MenuController* menu = new MenuController(root, dr);


uint8_t test_uint8 = 10;
int16_t test_int16 = 1000;
int16_t test_deci = 0;
char cmd;
bool led_active = false;

const char *test_arr[]={"AAAA", "BBBB", "CCCC", "DDDD"};
uint8_t test_arr_val = 0;
uint8_t test_arr_max = 3;

void test_action();

typedef enum button_event_t {NONE, BTN_DECR, BTN_DECR_FAST, BTN_INCR, BTN_INCR_FAST, BTN_SEL, BTN_ESC} button_event_t;

button_event_t buttonEvent() {
  cmd = Serial.read();
  switch(cmd) {
      case 'a': return BTN_DECR;
      case 'd': return BTN_INCR;
      case 'q': return BTN_DECR_FAST;
      case 'e': return BTN_INCR_FAST;
      case ' ': return BTN_SEL;
      case 's': return BTN_ESC;
      default:
        return NONE;
  }
}

void numberSelectedCallback(bool confirmed) {
    if (confirmed) {
        // Number selected and confirmed
        // Do something with the selected value eg. save in EEPROM
        Serial.println(F(">>confirmed<<"));
    } else {
        // Number selected but not confirmed
        // Do something else eg. update brightness of LED
    }
}

void checkboxCallback(bool change) {
  pinMode(LED_BUILTIN, OUTPUT);
  if (led_active) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup() {

  Serial.begin(9600);

  Wire.begin();
  Wire.setClock(400000L);

  oled.begin(&Adafruit128x64, I2C_ADDRESS);

  oled.setFont(NORMAL_FONT);
  oled.clear();

  root->setText(F("Menu"));

  root->addItem(new Action(root, F("Action"), test_action));
  Menu* sub = new Menu(root, F("Sub Menu"));
      sub->addItem(new Action(sub, F("Action"), test_action));
      sub->addItem(new CheckBox(sub, F("LED"), led_active, checkboxCallback));
      sub->addItem(new NumericSelectorUint8(sub, F("uInt8"), test_uint8, 0, 255, 1, 10, F("ms"), numberSelectedCallback));
      sub->addItem(new NumericSelectorInt16(sub, F("int16"), test_int16, 0, 10000, 10, 1000, 0, F("mm"), numberSelectedCallback));
      sub->addItem(new NumericSelectorInt16(sub, F("intDec"), test_deci, -100, 100, 1, 20, 2, F("kg"), numberSelectedCallback));
      sub->addItem(new NumericSelectorList(sub, F("list"), test_arr_val, test_arr_max, test_arr));

      root->addItem(sub);

  menu->draw();
}

void loop() {
  if(Serial.available() > 0) {

    switch (buttonEvent()) {
      case NONE: break;
      case BTN_DECR: menu->decr(); break;
      case BTN_DECR_FAST: menu->decrFast(); break;
      case BTN_INCR: menu->incr(); break;
      case BTN_INCR_FAST: menu->incrFast(); break;
      case BTN_SEL: menu->select(); break;
      case BTN_ESC: menu->esc(); break;
    }

    menu->draw();
  }
}

void test_action() {
  oled.clear();
  oled.print(F("Action: "));
  for (int i=0; i < 10; i++) {
    // if select or return button is pushed exit the function and go back to menu
    button_event_t event = buttonEvent();
    if ((event == BTN_ESC) || (event == BTN_SEL)) break;

    oled.print(F("."));
    delay(200);
  }
}

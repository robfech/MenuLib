#include <Arduino.h>

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <MenuLib.h>
#include "SSD1306AsciiDrawer.h"

#define I2C_ADDRESS 0x3C
SSD1306AsciiWire oled;

void menuSelectedCallback(bool);
Menu* root = new Menu(NULL, NULL, menuSelectedCallback);
SSD1306AsciiDrawer* dr = new SSD1306AsciiDrawer(oled);
MenuController* menu = new MenuController(root, dr);


uint8_t test = 10;
char cmd;
bool led_active = false;

const char *test_arr[]={"AAAA", "BBBB", "CCCC", "DDDD"};
uint8_t test_arr_val = 0;
uint8_t test_arr_max = 3;

void test_action();

menu_event_t buttonEvent() {
  cmd = Serial.read();
  switch(cmd) {
      case 'a': return MENU_PREV;
      case 'd': return MENU_NEXT;
      case ' ': return MENU_SELECT;
      case 's': return MENU_BACK;
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

void menuSelectedCallback(bool selected) {
  if (selected) oled.clear();
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

  root->addItem(new Action(root, F("Do something"), NULL));
  Menu* sub = new Menu(root, F("Sub Menu"), menuSelectedCallback);
      sub->addItem(new Action(sub, F("Action"), test_action));
      sub->addItem(new CheckBox(sub, F("LED"), led_active, checkboxCallback));
      sub->addItem(new NumericSelector(sub, F("Test value"), test, 0, 244, numberSelectedCallback));
      sub->addItem(new NumericSelector(sub, F("Test value"), test_arr_val, 0, test_arr_max, NULL, test_arr));

      root->addItem(sub);

  menu->draw();
}

void loop() {
  if(Serial.available() > 0) {

    switch (buttonEvent()) {
      case NONE: break;
      case MENU_PREV: menu->prev(); break;
      case MENU_NEXT: menu->next(); break;
      case MENU_SELECT: menu->select(); break;
      case MENU_BACK: menu->back(); break;
    }

    menu->draw();
  }
}

void test_action() {
  oled.clear();
  oled.print(F("Action: "));
  for (int i=0; i < 10; i++) {
    // if select or return button is pushed exit the function and go back to menu
    menu_event_t event = buttonEvent();
    if ((event == MENU_BACK) || (event == MENU_SELECT)) break;

    oled.print(F("."));
    delay(200);
  }
}

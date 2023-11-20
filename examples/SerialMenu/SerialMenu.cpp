#include <Arduino.h>

#include <MenuLib.h>

Menu* root = new Menu(NULL, NULL);
SerialDrawer* dr = new SerialDrawer();
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

void setup() {

  Serial.begin(9600);

  root->setText(F("Menu"));

  root->addItem(new Action(root, F("Do something"), NULL));
  Menu* sub = new Menu(root, F("Sub Menu"));
      sub->addItem(new Action(sub, F("Action"), test_action));
      sub->addItem(new CheckBox(sub, F("LED"), led_active));
      sub->addItem(new NumericSelector(sub, F("Test value"), test, 0, 244));
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
  Serial.print(F("Action: "));
  for (int i=0; i < 10; i++) {
    // if select or return button is pushed exit the function and go back to menu
    menu_event_t event = buttonEvent();
    if ((event == MENU_BACK) || (event == MENU_SELECT)) break;

    Serial.print(F("."));
    delay(200);
  }
  Serial.print("\n");
}

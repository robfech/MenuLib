#include <Arduino.h>

#include <MenuLib.h>

Menu* root = new Menu(NULL, NULL);
SerialDrawer* dr = new SerialDrawer();
MenuController* menu = new MenuController(root, dr);


uint8_t test = 10;
char cmd;

const char *test_arr[]={"AAAA", "BBBB", "CCCC", "DDDD"};
uint8_t test_arr_val = 0;
uint8_t test_arr_max = 3;

void setup() {

  Serial.begin(9600);

  root->setText(F("Menu"));

  root->addItem(new Action(root, F("Do something"), NULL));
  Menu* sub = new Menu(root, F("Sub Menu"));
      sub->addItem(new Action(sub, F("Aaa"), NULL));
      sub->addItem(new Action(sub, F("bbb"), NULL));
      sub->addItem(new NumericSelector(sub, F("Test value"), test, 0, 244));
      sub->addItem(new NumericSelector(sub, F("Test value"), test_arr_val, 0, test_arr_max, NULL, test_arr));

      root->addItem(sub);

  menu->draw();
}

void loop() {
  if(Serial.available() > 0) {
    cmd = Serial.read();


    switch(cmd) {
        case 'w': menu->prev(); break;
        case 's': menu->next(); break;

        case ' ': menu->select(); break;
        case 'x': menu->back(); break;

        default:
          Serial.print("Unknow command ");
          Serial.println(cmd);
    }

    menu->draw();
  }
}

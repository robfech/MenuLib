#include <Wire.h>

#include <MenuLib.h>

#include <SSD1306Drawer.h>
#include <SSD1306Wire.h>

const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = SDA;
const int SDC_PIN = SCL;

SSD1306Wire lcd = SSD1306Wire(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);

Menu* root = new Menu(NULL, NULL);
SSD1306Drawer* dr = new SSD1306Drawer(lcd, 4);
MenuController* menu = new MenuController(root, dr);

uint8_t testval = 2;
bool testbool = false;

//--photo values---
      //---exposure
      const char *arr_p_exp[]={"Auto", "7.9", "7.7", "6.1", "4.6", "2.7", "1.0", "1/3", "1/5", "1/10", "1/15", "1/30", "1/50", "1/60", "1/80", "1/125", "1/140", "1/250", "1/320", "1/500", "1/752", "1/1244", "1/2138", "1/3675", "1/6316", "1/8147"};
      uint8_t arr_p_exp_val = 0;
      uint8_t arr_p_exp_max = 25;
      //---iso
      const char *arr_p_iso[]={"Auto", "100", "200", "400", "800", "1600", "3200", "6400", "12800", "25600"};
      uint8_t arr_p_iso_val = 0;
      uint8_t arr_p_iso_max = 9;
      //---awb
      bool chb_p_awb = false;
      //---auto knee
      //////////////////////////////////////////////////
      //---saturation
      const char *arr_p_sat[]={"Dafault", "Yes"};
      uint8_t arr_p_sat_val = 0;
      uint8_t arr_p_sat_max = 1;
      //---sharpness
      const char *arr_p_sha[]={"Video", "Fast Still", "LowISO Still", "HighISO Still", "Default"};
      uint8_t arr_p_sha_val = 0;
      uint8_t arr_p_sha_max = 4;
      //---create raw
      bool chb_p_raw = false;

bool chb_v_4g_file = false;

char cmd;

void somevoid() {
  Serial.println("somevoid");
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("START");

  Wire.begin(SDA_PIN, SDC_PIN);


  lcd.init();                                         // initialize dispaly
  lcd.setFont(ArialMT_Plain_10);
  lcd.setTextAlignment(TEXT_ALIGN_CENTER);
  lcd.flipScreenVertically();
  lcd.displayOn();
  lcd.clear();
  lcd.setContrast(255);
  lcd.display();

  root->setText(F("Xiaomi Yi Config"));

  Menu* photoset = new Menu(root, F("Photo Settings"));
    photoset->addItem(new NumericSelector(photoset, F("Exposure"), arr_p_exp_val, 0, arr_p_exp_max, NULL, arr_p_exp));
    photoset->addItem(new NumericSelector(photoset, F("ISO"), arr_p_iso_val, 0, arr_p_iso_max, NULL, arr_p_iso));
    photoset->addItem(new CheckBox(photoset, F("AWB"), chb_p_awb));
    photoset->addItem(new Action(photoset, F("Auto Knee"), NULL));
    photoset->addItem(new NumericSelector(photoset, F("Saturation"), arr_p_sat_val, 0, arr_p_sat_max, NULL, arr_p_sat));
    photoset->addItem(new NumericSelector(photoset, F("Sharpness"), arr_p_sha_val, 0, arr_p_sha_max, NULL, arr_p_sha));
    photoset->addItem(new CheckBox(photoset, F("Create RAW"), chb_p_raw));
    root->addItem(photoset);

  Menu* videoset = new Menu(root, F("Video Settings"));
    videoset->addItem(new Action(videoset, F("NR"), NULL));
    videoset->addItem(new Action(videoset, F("AAA"), NULL));
    videoset->addItem(new Action(videoset, F("Gamma"), NULL));
    videoset->addItem(new Action(videoset, F("Auto Knee"), NULL));
    videoset->addItem(new Action(videoset, F("Saturation"), NULL));
    videoset->addItem(new Action(videoset, F("Sharpness"), NULL));
    videoset->addItem(new Action(videoset, F("Resolution"), NULL));
    videoset->addItem(new Action(videoset, F("SuperView"), NULL));
    videoset->addItem(new Action(videoset, F("Bitrate all"), NULL));
    videoset->addItem(new CheckBox(videoset, F("4Gb files"), chb_v_4g_file));
    root->addItem(videoset);

  Menu* otherset = new Menu(root, F("Other Settings"));
    otherset->addItem(new Action(otherset, F("Do something 1"), somevoid));
    otherset->addItem(new CheckBox(otherset, F("CheckBox 2"), testbool));
    otherset->addItem(new NumericSelector(otherset, F("NumericSelect 3"), testval, 0, 100));
    otherset->addItem(new Action(otherset, F("Do something 4"), somevoid));
    root->addItem(otherset);

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
          break;
          //Serial.print("Unknow command ");
          //Serial.println(cmd);
    }

    menu->draw();
  }

}

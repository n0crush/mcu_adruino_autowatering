
#include <LiquidCrystal.h>
#include <string.h>

void welcome(char[], char[]);
void show_setup();
void show_detail();

short getButtonStatus();
void print_change();

// function prototype
//---------------------------------

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// declare var ----------------------------------------------------

short min_active = 40;

short button = 7 ;                                     // get digital input from pin 7st
short digital_output = 8;                              // digital signal output in pin 8st

// float h_input = 1.65;                             // temporory input     OLDER
// int humi =  (h_input*100)/H_MAX;                  // humidity            OLDER

short humi;// =  (h_input*100)/H_MAX;                  // humidity

char x0[]   = "-.- CCK12DT1 -.-";
char x1[]   = " Auto Watering ";
char sts[]  = "OFF";

short hh=23; short mm=59;  // pseudo

//-------
short analog_input = A0;
float voltage;
short value;

float analog_max_input = 2.2;
//-------

// declare var ----------------------------------------------------

//----------------------------------

void setup() {
  pinMode(button, INPUT);                         // D7

  pinMode(digital_output, OUTPUT);                // D8
  //

  lcd.begin(16, 2);                               // declare LCD 1602
  Serial.begin(9600);                             // debugging

  show_setup();                                   // show setup menu one time in the begining
                                                  // reset Adruino to setup again.
}

//----------------------------------

void welcome(char x0[] , char x1[]){                   // welcome
                                                      // addition effect, string, etc...
  lcd.setCursor(0, 0);
  lcd.print(x0);
  lcd.setCursor(0, 1);
  lcd.print(x1);

}

  //--------- unit func
  short getButtonStatus(){
    //
    short buttonStatus;
    buttonStatus = digitalRead(button);
    return buttonStatus;
  }


  void print_change(){                            // change on setup
       lcd.setCursor(0, 0);

       lcd.print("MinAct: ");
       lcd.print(min_active);lcd.print("%");

       delay(200);                                // adjust

  }
  //---------




void show_setup(){
  lcd.setCursor(0, 0);
  lcd.print("1-Select MinAct");

  lcd.setCursor(0, 1);
  lcd.print("2-Skip( default)");
  delay(3000);                                   // adjust

  lcd.clear();

  short i;
  for(i=0; i<=5; ++i){                           // blink cursor
     lcd.noCursor();
     delay(300);
     lcd.cursor();
     delay(300);
  }

  short st;
  for(i=0; i<100; ++i){                             // time = i_max * delay
    st = getButtonStatus();
    if(st==1){                                       // if(st){}
      min_active += 5;                              // increase 5 percent in one press
      print_change();
    }

    // Serial.println(st);                              // debugging
    // Serial.println(min_active);                     // debugging

    delay(100);                                        // adjust waiting time for pressing
  }
}

/*
int voltage_to_percent(int value){

  int h;

  value = analogRead(analog_input);

  voltage = (value/1023.0) / 5.0;                 // get voltage on range of 0 -> 1023 encoded with 5V
  voltage -= 1;                                   // minimum of voltage given by humidity sensor

  h = (voltage / analog_max_input) * 100;         // to percent

  // catch exception
  if (h<0) h = 0;
  if (h>100) h = 100;

  h = 100 - h;                                    // decrease -.-

  return h;

}
*/

void show_detail(){

    // int value;
  
    value = analogRead(analog_input);

    voltage = (value/1023.0) * 5.0;                    // get voltage on range of 0 -> 1023
    voltage -= 1;                                     // minimum of voltage given by humidity sensor

    //Serial.println(volt);                            // debuging

    //humi= (voltage/2.2) * 100;                         // percent     OLDER
    humi= (voltage/analog_max_input) * 100;                         // percent    LOOKBACK HERE IF FAIL

    if(humi<0){ humi = 0;}
    if(humi>100){ humi = 100;}

    humi = 100 - humi;

    // ^^ ***
//----------------

  lcd.setCursor(0, 0);
  lcd.print("CurH:");
  lcd.print(humi);
  lcd.print("% Sts:");
  lcd.print(sts);
  //

  lcd.setCursor(0, 1);
  lcd.print("MinActive: ");
  lcd.print(min_active);lcd.print("%  ");

  //---------------                                         // check output for relay
  if(humi >= min_active){
    digitalWrite(digital_output, LOW);
    // delay(200);  look back here if fail
  }else{
    digitalWrite(digital_output, HIGH);
  }
  //---------------


  //lcd.print(hh); lcd.print(":"); lcd.print(mm);               
  // MinAct:00% hh:mm           // come with RTC module

  delay(500);                                               // adjust here
}

void loop() {

  //Serial.println(humi);                                   // debugging

  /*
  welcome(x0, x1);
  delay(1000);
  */

  //--------------------------
  show_detail();

}

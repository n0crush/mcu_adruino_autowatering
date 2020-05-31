#include <LiquidCrystal.h>


//function prototype---------------
void welcome(char[], char[]);
void show_setup();
void show_detail();

//---------------------------------
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// declare var ----------------------------------------------------
const float H_MAX = 3.3;                              // adjust
int MIN_ACT = 40;
int MAX_ACT = 80;

short button = 7;                                     // get digital input from pin 7st
short led = 8;                                        // get digital output from pin 8st

int humi;

char x0[] = "-.- CCK12DT1 -.-";
char x1[] = " Auto Watering ";
char sts[] = "OFF";

//
short analog_input = A0;                              //
float voltage;
int value;

float analog_max_input = 2.2;                         // maximum value given by output of humidity sensor

// declare var ----------------------------------------------------

//----------------------------------

void setup() {
  pinMode(button, INPUT);

  pinMode(led, OUTPUT);
  //

  lcd.begin(16, 2);                               // declare LCD 1602
  Serial.begin(9600);                             // debug

  welcome(x0, x1);
  //delay(5000);
  
  show_setup();

}
//----------------------------------

  //unit func-----------------------
  short getButtonStatus(){
    //
    short buttonStatus;
    buttonStatus = digitalRead(button);
    return buttonStatus;
  }
  

  void print_change(){

    lcd.setCursor(0, 0);
    lcd.print("MinAct: ");
    if(MIN_ACT <= 100){
      lcd.print(MIN_ACT);lcd.print("%");
    }else{
      lcd.print("FULL");
      lcd.clear();
      MIN_ACT = 0;
    }
    delay(50);

  }
  //-------------------------------
  
void show_setup(){
  lcd.setCursor(0, 0);
  lcd.print("1-Select MinAct");
  
  lcd.setCursor(0, 1);
  lcd.print("2-Skip( default)");
  delay(3000);

  {// prompt---------------------------------
    lcd.clear();
    lcd.print("Choose MinAct");
    
    for(short i=0; i<5; ++i){
      lcd.display();
      delay(300);
      lcd.noDisplay();
      delay(300);
    }
    
    lcd.display();
    lcd.clear();
  }//----------------------------------------
  
  short i;
  for(i=0; i<=5; ++i){
    lcd.noCursor();
    delay(300);
    lcd.cursor();
    delay(300);
    
    if(getButtonStatus()){
      break;
    }
    
  }
  /*
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">>");
    lcd.clear();
  }
  */

  
  //test button
  short st;
  for(i=0; i<100; ++i){
    st = getButtonStatus();
    if(st == 1){                                      // if(st){}
      MIN_ACT += 5;                                   // 5 percent in a press
    }
    
    delay(50);  
    print_change();
    delay(50);  
    // Serial.println(st);                            // debug
    // Serial.println(MIN_ACT);                       // debug
  }
}

void welcome(char x0[] , char x1[]){
  short i;
  for(i=0; i<=5; ++i){
    lcd.setCursor(0, 0);
    lcd.print(x0);
    lcd.setCursor(0, 1);
    lcd.print(x1);
    delay(500);
    lcd.clear();
    delay(100);
  }

  
  {// resource-------------------------------
    lcd.setCursor(15, 0);
    lcd.print("github.com/n0crush");
    for (short pos = 0; pos < (18+15); pos++) {
      lcd.scrollDisplayLeft();
      delay(350);
    }
  lcd.clear();
  }//----------------------------------------

}

/*
int read_analog_input(int value){
  int h;

  //  value = analogRead(analog_input);

  voltage = (value/1023.0) / 5.0;                 // get voltage by standard: 0 -> 1023
  voltage -= 1;

  h = (voltage / analog_max_input) * 100;      // percent
  
  // catch exception
  if (h<0) h = 0;
  if (h>100) h = 100;

  h = 100 - h;

  return h;

}
*/

void show_detail(){
    
    value = analogRead(analog_input);
       
    voltage = (value / 1023.0) * 5.0;                           // get voltage standard: 0 -> 1023
    voltage -= 1;

    //Serial.println(voltage);                                  // debug

    humi = (voltage / analog_max_input) * 100;                  // percent


    if(humi < 0){
      humi = 0;
    }
    if(humi > 100){
      humi = 100;
    }
    
    humi= 100 - humi;

//----------------

  lcd.setCursor(0, 0);
  lcd.print("CurH:");
  lcd.print(humi);
  lcd.print("% Sts:");
  lcd.print(sts);
  //
  
  lcd.setCursor(0, 1);
  lcd.print("MinActive: ");
  lcd.print(MIN_ACT);
  lcd.print("%  ");
  //

  //---------------
  if(humi <= MIN_ACT){
    digitalWrite(led, HIGH);
    sts[0] = 'O'; sts[1] = 'N'; sts[2] = ' '; sts[3] = ' ';
  }else if (humi >= MAX_ACT){                                     // maximum humidity to stop pump
    delay(200);
    digitalWrite(led, LOW);
    sts[0] = 'O'; sts[1] = 'F'; sts[2] = 'F';
  }


  /*
  else{
    digitalWrite(led, LOW);
    sts[0] = 'O'; sts[1] = 'F'; sts[2] = 'F';
    delay(200);
  }
  */
  //---------------

  
  //lcd.print(hh); lcd.print(":"); lcd.print(mm);            // MinAct:00% hh:mm    --   come with RTC module
  
  delay(500);                                               // adjust here
}

void loop() {
  
  //Serial.println(humi);                                   // debug
  //--------------------------
  
  show_detail();
  
}

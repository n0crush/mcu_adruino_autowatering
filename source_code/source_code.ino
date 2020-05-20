#include <LiquidCrystal.h>
#include <string.h>

void welcome(char[], char[]);
void show_setup();
void show_detail();

// function prototype
//---------------------------------
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const float H_MAX = 3.3;                          // adj
//const int MIN_ACT = 40;                         // const ver
int MIN_ACT = 40;
int button = 7 ;                                  // get digital input from pin 7st

float h_input = 1.65;                             // temporory input
int humi =  (h_input*100)/H_MAX;                  // humidity


char x0[] = "-.- CCK12DT1 -.-";
char x1[] = " Auto Watering ";
char sts[] = "OFF";
int hh=23;
int mm=59;
//----------------------------------

void setup() {
  pinMode(button, INPUT);
  //

  lcd.begin(16, 2);                               // declare LCD 1602
  Serial.begin(9600);                             // debugging
  show_setup();

}
//----------------------------------
int getButtonStatus(){
  //
  short buttonStatus;
  buttonStatus = digitalRead(button);
  return buttonStatus;
}
  
  //--------- unit func
  void print_change(){
       lcd.setCursor(0, 0);
       lcd.print("MinAct: ");
       lcd.print(MIN_ACT);lcd.print("%");

       delay(200);

  }
  //---------
  
void show_setup(){
  lcd.setCursor(0, 0);
  lcd.print("1-Select MinAct");
  
  lcd.setCursor(0, 1);
  lcd.print("2-Skip( default)");
  delay(3000);

  lcd.clear();
  short i;
  for(i=0; i<=5; ++i){
     lcd.noCursor();
     delay(300);
     lcd.cursor();
     delay(300);
  }
  
  //test button
  
  short st;
  for(i=0; i<100; ++i){
    st = getButtonStatus();
    if(st==1){                                       //if(st){}
      MIN_ACT += 5;
      print_change();
    }
    // Serial.println(st);                          // debugging
    // Serial.println(MIN_ACT);                     // debugging
    delay(100);
  }
}

void welcome(char x0[] , char x1[]){
  lcd.setCursor(0, 0);
  lcd.print(x0);
  lcd.setCursor(0, 1);
  lcd.print(x1);
}
void show_detail(){
  lcd.setCursor(0, 0);
  lcd.print("CurH:");
  lcd.print(humi);
  lcd.print("% Sts:");
  lcd.print(sts);
  //
  
  lcd.setCursor(0, 1);
  lcd.print("MinActive: ");
  lcd.print(MIN_ACT);lcd.print("%  ");
  
  //lcd.print(hh); lcd.print(":"); lcd.print(mm);               // MinAct:00% hh:mm           // come with RTC module

  
  
  //lcd.print("                ");    clsr
  delay(3000);
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

#include <LiquidCrystal.h>
#include <string.h>

void welcome(char[], char[]);
void show_setup();
void show_detail();

// function prototype
//---------------------------------
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const float H_MAX = 3.3;                          // adj
const int MIN_ACT = 40;

float h_input = 1.65;                             // temporory input
int humi =  (h_input*100)/H_MAX;                  // humidity


char x0[] = "-.- CCK12DT1 -.-";
char x1[] = " Auto Watering ";
char sts[] = "OFF";
int hh=23;
int mm=59;
//----------------------------------

void setup() {

  lcd.begin(16, 2);                               // declare LCD 1602
  //Serial.begin(9600);
  show_setup();

}
//----------------------------------
int getButtonStatus(){
  //
}

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
  lcd.print("MinAct:");
  lcd.print(MIN_ACT);lcd.print("% ");
  lcd.print(hh); lcd.print(":"); lcd.print(mm);
  //MinAct:00% hh:mm
  
  
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

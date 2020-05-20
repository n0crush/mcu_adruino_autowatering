int a_input = A0;
float volt;
int h;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
    int value = analogRead(a_input);
  // volt = (value/1023.0) * 5.0;     //adruino
   // volt = (value/1023.0) * (value+1);      // kit
    volt = (value/1023.0) * (5/(2.25));      // kit
   // volt -= 1;
    
    Serial.println(volt);
    // h = ((volt)/(2.25)) * 90;       // value exactly
    h = ((volt)/(5/(2.25))) * 100; 
    if(h<0){h = 0;}
    if(h>100){ h = 100;}
    
    h = 100 - h;
   // h = h+((h*5)/100);                // +- 5% 
   // h+=26;
    // h = volt * (1.2/100.0)*100;
    

    Serial.println(h);
    
    delay(500);
}

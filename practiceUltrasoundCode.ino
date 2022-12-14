//introduce lcd variables and library
#include <LiquidCrystal.h>
int Contrast = 25;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//introduce sensor variables and pins
#define ECHOPIN 10
#define TRIGPIN 8

boolean runOnce = false;
long duration;
float distanceCm, distanceInch, totalCm, totalInch, distanceFt;

//setup function
void setup() {
  Serial.begin(9600);
  
  lcd.begin(10, 2);
  analogWrite(6, Contrast);
   
  pinMode(ECHOPIN, INPUT_PULLUP);
  pinMode(TRIGPIN, OUTPUT);
}

void loop() {
  
  if(runOnce == false){
    runOnce = true;
    
    for(int i = 0; i < 3; i++){
  
      digitalWrite(TRIGPIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIGPIN, HIGH);
      delayMicroseconds(15);
      digitalWrite(TRIGPIN, LOW);

    //calculate the distance
      duration = pulseIn(ECHOPIN, HIGH);
      distanceCm = duration * 0.034/2;
      distanceInch = duration * 0.0113 / 2;

  //prints all measurements to  the console
      Serial.print(distanceCm);
      Serial.println(" cm");
      Serial.print(distanceInch);
      Serial.println(" in");


  //check if it is a false reading
      if (distanceCm != 0 && distanceInch != 0){
        totalCm += distanceCm;
        totalInch += distanceInch;
    }
    else{
       i -= 1;
      }

   }
  
   distanceCm = totalCm / 3;
   distanceInch = totalInch / 3;

   //print final distance
   Serial.print(distanceCm);
   Serial.println(" cm");
   Serial.print(distanceInch);
   Serial.println(" in");

  //lcd print final distance
   lcd.setCursor(1,0);
   lcd.print(distanceCm);
   lcd.print(" cm");
   lcd.setCursor(1,1);
   lcd.print(distanceInch);
   lcd.print(" in");
      
  }
}

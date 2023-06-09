#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

#define trigPin 7 //Sensor Echo pin connected to Arduino pin 13
#define echoPin 6 //Sensor Trip pin connected to Arduino pin 12

int t=0;
char i = 0;
float time, distance, initial=999;
float arr[50];


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  ADMUX = 0x43;
	ADCSRA = 0x84;


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //--------------------------------- LCD INIT
  lcd.init();
  lcd.backlight();
  lcd.setCursor (0,0);
  lcd.print ("    ARDUINO     ");
  lcd.setCursor (0,1);
  lcd.print ("Level Sensor");
  //---------------------------------
  Serial.begin(9600);
  delay (3000);
  

}

// the loop function runs over and over again forever
void loop(void) {

 
  delay(10);
  t++;
  //input
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time=pulseIn(echoPin, HIGH);
  



  //pre-processing (taking avg)-----------------
  arr[i++]=time;
  if (i==50) {i=0;}

  time=0;
  for (char j = 0; j < 50; j++) {
    time = time + arr[j];
  }  
  time=time/50;
  distance = (time/2) / 29.1;



  //output to terminal --------------------------
  if (t==50) {

      if (distance < initial) {  initial = distance;}

      distance = round(initial - distance)+100;

      t=0;
      printD();

  }

}

void printD() {

  if (distance < 0) {
    return;
  }

  Serial.print("Distance: ");
  Serial.println(distance); 
  lcd.setCursor (0,0);
  lcd.print("    Level:    ");
  lcd.setCursor (0,1);
  lcd.print("       ");
  lcd.print(distance);
  lcd.println("       ");            
}

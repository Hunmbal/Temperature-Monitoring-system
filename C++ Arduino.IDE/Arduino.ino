#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int t=0;
int sensor = A3;
char i = 0, mode = 0;
float temp, out;
float arr[100], max = -55, min = 155;


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  mode=0;
  ADMUX = 0x43;
	ADCSRA = 0x84;


  pinMode(sensor,INPUT);

  //--------------------------------- LCD INIT
  lcd.init();
  lcd.backlight();
  lcd.setCursor (0,0);
  lcd.print ("    ARDUINO     ");
  lcd.setCursor (0,1);
  lcd.print ("TEMPRETURE METER");
  //---------------------------------
  Serial.begin(9600);
  delay (3000);
  

}

// the loop function runs over and over again forever
void loop(void) {

  delay(10);
  t++;

  //input + conversion
  temp=(analogRead(sensor)*5)/10;



  //pre-processing (taking avg)-----------------
  arr[i++]=temp;
  if (i==100) {i=0;}

  temp=0;
  for (char j = 0; j < 100; j++) {
    temp = temp + arr[j];
  }  
  temp=temp/100;
  //ML formula
  temp=(0.3*temp+20);


  //output to terminal --------------------------
  if (t%50==0) {
      if (Serial.available()) {
        mode = Serial.read();
      }

      //recording max and min ----------------------

      Serial.print("Crrent: ");
      Serial.print(temp);
      Serial.print(" ");
      Serial.print("Max: ");
      Serial.print(max);   
      Serial.print(" ");
      Serial.print("Min: ");
      Serial.print(min);
      Serial.println(" ");    

  }


  //output to display --------------------------
  if (t==100) { 
    if (temp > max) { max = temp; }
    if (temp < min) { min = temp; }

    //output to led
    switch(mode) {
      case '1':
        printMax(); break;
      case '2':
        printMin(); break;
      default:
        printCur(); break;
    }
    t=0;
  }

}



void printCur() {
  
  lcd.setCursor (0,0);
  lcd.print("  Current Temp: ");
  lcd.setCursor (0,1);
  lcd.print("     ");
  lcd.print(temp);
  lcd.println(" C     ");            
}

void printMax() {
  
  lcd.setCursor (0,0);
  lcd.print("    Max Temp:  ");
  lcd.setCursor (0,1);
  lcd.print("     ");
  lcd.print(max);
  lcd.println(" C     ");            
}

void printMin() {
  
  lcd.setCursor (0,0);
  lcd.print("    Min Temp:   ");
  lcd.setCursor (0,1);
  lcd.print("     ");
  lcd.print(min);
  lcd.println(" C     ");            
}
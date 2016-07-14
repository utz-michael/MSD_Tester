
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
 
int analogPin = 0;
const int ledPin =  13;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
unsigned long previousmicros = 0;        // will store last time LED was updated
long interval = 1;           // interval at which to blink (milliseconds)
long RPM = 1000; 
long RPM_old = 0;
int analog = 0;
int analog_old = 0;
void setup() {
  lcd.begin(16,2);
  pinMode(ledPin, OUTPUT);
 lcd.setCursor(0,0);  
 lcd.print("MSD Tester");
 lcd.setCursor(0,1);
 lcd.print("           U/Min");
}

void loop() {
  //RPM = analogRead(analogPin)*10;
  analog = constrain (analogRead(analogPin),1,1000);
  if ( analog >= analog_old + 10 || analog <= analog_old - 10 ){
    RPM = analog * 10;
  interval =1000000.0/(RPM * 0.2);
  analog_old = analog;
  }
  

  if ( RPM >= RPM_old + 99 || RPM <= RPM_old - 99 ){
  lcd.setCursor(0,1);
  lcd.print("           U/Min");
  if (0 <= RPM && RPM <= 9){lcd.setCursor(8,1);}
  if (10 <= RPM && RPM <= 99){lcd.setCursor(7,1);}
  if (100 <= RPM && RPM <= 999){lcd.setCursor(6,1);}
  if (1000 <= RPM && RPM <= 9999){lcd.setCursor(5,1);}
  if (10000 <= RPM && RPM <= 99999){lcd.setCursor(4,1);}
  lcd.print(RPM);
  RPM_old = RPM;
  }
  unsigned long currentmicros = micros();

  if (currentmicros - previousmicros >= interval && ledState == HIGH) {
  
    previousmicros = currentmicros;
      ledState = LOW;
    digitalWrite(ledPin, ledState);
  }
  if (currentmicros - previousmicros >= 2 * interval && ledState == LOW) {
  
    previousmicros = currentmicros;
      ledState = HIGH;
    digitalWrite(ledPin, ledState);
  }

  
}

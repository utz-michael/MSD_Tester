
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
 //LiquidCrystal_I2C lcd(0x27,16,2);
int analogPin = 0;
const int ledPin =  13;      // the number of the LED pin


int RPM = 67; 
int RPM_old = 0;
int RPM_LCD = 1005;

void setup() {
 // lcd.init(); 
  lcd.backlight();
  lcd.begin(16,2);
  pinMode(ledPin, OUTPUT);
 lcd.setCursor(0,0);  
 lcd.print("MSD Tester");
 lcd.setCursor(0,1);
 lcd.print("           U/Min");
  Serial.begin(9600);
}

void loop() {
 RPM = map (analogRead(analogPin),0,1023,31,667);
 
Serial.print(RPM*15); 
Serial.print(" U/Min  ");
Serial.print(RPM); 
Serial.println(" Hz");
  if ( RPM >= RPM_old + 1 || RPM <= RPM_old - 1 ){
  lcd.setCursor(0,1);
  lcd.print("           U/Min");
  RPM_LCD = RPM * 15;
  if (0 <= RPM_LCD && RPM_LCD <= 9){lcd.setCursor(8,1);}
  if (10 <= RPM_LCD && RPM_LCD <= 99){lcd.setCursor(7,1);}
  if (100 <= RPM_LCD && RPM_LCD <= 999){lcd.setCursor(6,1);}
  if (1000 <= RPM_LCD && RPM_LCD <= 9999){lcd.setCursor(5,1);}
  if (10000 <= RPM_LCD && RPM_LCD <= 99999){lcd.setCursor(4,1);}
  lcd.print(RPM_LCD);
  RPM_old = RPM;
  }
  tone(ledPin,RPM);

  
}

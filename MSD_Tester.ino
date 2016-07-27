
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
 
int analogPin = 0;
const int ledPin =  4;      // the number of the LED pin


int RPM = 67; 
int RPM_old = 0;
int RPM_LCD = 1005;

const byte interruptPinUp = 2;
const byte interruptPinDown =3;
volatile unsigned long alteZeit=0, entprellZeit=300;
int fastforwardUp = 0;
int fastforwardDown = 0;

void setup() {
  pinMode(interruptPinUp, INPUT);
  pinMode(interruptPinDown, INPUT);
  digitalWrite(interruptPinUp, HIGH);
  digitalWrite(interruptPinDown, HIGH);
 
  
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
 
 
 Serial.print(RPM*15); 
 Serial.print(" U/Min  ");
 Serial.print(RPM); 
 Serial.println(" Hz");
 
if (digitalRead (interruptPinUp) == LOW ) {up();}
else {fastforwardUp=0;}
if (digitalRead (interruptPinDown) == LOW ) {down();}
else {fastforwardDown=0;}

 
  if ( RPM != RPM_old  ){
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
 
  //RPM = constrain (RPM,31,667);
  tone(ledPin,RPM);
}
  void up() {
  if((millis() - alteZeit) > entprellZeit || fastforwardUp > 50 ) { 
    
   if (RPM < 667){
 RPM ++;
 }
 if (RPM < 657 && fastforwardUp > 50){
 //RPM ++;
 RPM ++;
  }
    alteZeit = millis(); // letzte Schaltzeit merken      
  }
 else {
  fastforwardUp ++ ;
 }
 }
 


 void down() {
  if((millis() - alteZeit) > entprellZeit || fastforwardDown > 50) { 
    
   if (RPM > 31){
 RPM --  ;  
  }
    if (RPM > 41 && fastforwardDown > 50){
// RPM --  ; 
 RPM --  ;   
  }
    alteZeit = millis(); // letzte Schaltzeit merken      
  }
  else {
  fastforwardDown ++ ;
 }
}


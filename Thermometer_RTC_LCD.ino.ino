#include <max6675.h> // Thermocouple
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // LCD display
#include <RTClib.h> // RTC module 

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

 
byte thermo[8]={B00100,B01010,B01010,B01010,B01110,B11111,B11111,B01110}; // code of the thermometer symbol
byte clockSIGN[8]={B00000,B01110,B10101,B10111,B10001,B01110,B00000,B000000}; // code of the clock symbol
byte rectangle[8]={B11111,B10001,B01100,B01010,B01010,B01100,B10001,B11111};  // code of the date symbol

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// ThermoCouple
int thermo_gnd_pin = 45;
int thermo_vcc_pin = 47;
int thermo_so_pin  = 53;
int thermo_cs_pin  = 51;
int thermo_sck_pin = 49;
float avg=0;
float sum=0;
  
MAX6675 thermocouple(thermo_sck_pin, thermo_cs_pin, thermo_so_pin); // thermometer
RTC_DS3231 RTC; // RTC module

  
void setup() 
{

lcd.begin();
lcd.clear();
lcd.createChar(1, thermo); // creation of the thermometer symbol
lcd.createChar(2, clockSIGN); // creation of the clock symbol
lcd.createChar(3, rectangle); // creation of the date symbol
lcd.backlight(); // sets backlight on the screen
  lcd.setCursor(0, 0); // moves cursor to 1st row 1st character
  lcd.print("    Hello!"); //  message on the display while initializing 
  
  
  Wire.begin();
  RTC.begin();

   RTC.adjust(DateTime(2018, 12, 26, 21, 43, 00)); // here can be adjusted the date and time
   
//delay(1000);



 // wiring of the thermometer module 
  Serial.begin(9600);

  pinMode(thermo_vcc_pin, OUTPUT); 
  pinMode(thermo_gnd_pin, OUTPUT); 
  digitalWrite(thermo_vcc_pin, HIGH);
  digitalWrite(thermo_gnd_pin, LOW);



  
}

void loop() {

  // measuring temperature and count 20 measurement's average/sec
 sum=0;
 avg=0;
  for (int i=0; i<20; i++)
  {
  sum=sum+thermocouple.readCelsius();
  }

  avg=sum/20;
  
  lcd.setCursor(0, 0);
  
lcd.clear();

DateTime now = RTC.now();
lcd.setCursor(0, 0);
lcd.write(byte(2)); // displays the clock symbol before the time
    lcd.setCursor(2,0); // after the clock symbol displays the time
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    //lcd.print(':');
    //lcd.print(now.second(), DEC);  // if remove the comment sign, displays the seconds too
lcd.setCursor(10,0); // moves the cursor to 1st row's 10th character
lcd.write(byte(3)); // displays date's symbol
 
    //lcd.print(" |");
     
    //lcd.print(now.year(), DEC); // if remove the comment sign, displays the year
    //lcd.print('.');
    lcd.print(now.month(), DEC); // displays month and day
    lcd.print('.');
    lcd.print(now.day(), DEC);
    lcd.print('.');

  lcd.setCursor(0,1); // moves cursor to the 2nd row's 1st character

lcd.write(byte(1)); // displays the thermometer's symbol
  
  lcd.setCursor(5, 1); // moves cursor to 2nd row's 5th character
 

if (avg==0)
{
  lcd.println("                      ");  // if the measurements' average 0 then the screen doesn't display any data
}

 else
 {

  
  lcd.println(avg);   // else it displays the measured values average (20 sample's average/sec)
   

  lcd.print(" ");
  lcd.setCursor (10, 1); // moves the cursor to the 2nd row's 10th character
  lcd.print((char)223);  // displays the degree sign after the displayed value of the temperature average
  lcd.println("C         "); // displays "C" after degree sign

 }

delay(1000);  // delays 1sec
}

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


// Booting message
//FIRST ROW
// D
byte d1[8]={B00000,B00111,B00111,B00110,B00110,B00110,B00110,B00110}; // 1st char
byte d2[8]={B00000,B11100,B11110,B00111,B00011,B00011,B00001,B00001}; //2nd char
byte d3[8]={B00000,B00000,B00000,B00000,B10000,B10000,B10000,B10000}; //3rd char

// O
byte d4[8]={B00000,B00000,B00000,B00001,B00011,B00111,B00110,B00110}; //4th char
byte d5[8]={B00000,B01111,B11111,B10000,B10000,B00000,B00000,B00000}; //5th char
byte d6[8]={B00000,B10000,B11000,B01100,B01110,B00111,B00011,B00011}; //6th char

// SPACE
byte d7[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000}; //7th char

//B
byte d8[8]={B00000,B00111,B00111,B00110,B00110,B00110,B00110,B00111}; //8th char
byte d9[8]={B00000,B11111,B11111,B00001,B00001,B00001,B00111,B11111}; //9th char
byte d10[8]={B00000,B00000,B10000,B10000,B10000,B10000,B00000,B00000}; //10th char

//B
byte d11[8]={B00000,B00001,B00001,B00001,B00001,B00001,B00001,B00001}; //11th char
byte d12[8]={B00000,B11111,B11111,B10000,B10000,B10000,B10001,B11111}; //12th char
byte d13[8]={B00000,B11000,B11100,B01100,B01100,B01100,B11000,B11000}; //13th char

//Y
byte d14[8]={B00000,B00001,B00001,B00001,B00001,B00001,B00001,B00001}; //14th char
byte d15[8]={B00000,B10000,B10000,B10000,B10000,B10000,B10000,B11000}; //15th char
byte d16[8]={B00000,B01100,B01100,B01100,B01100,B01100,B01100,B11100}; //16th char



//SECOND ROW

//D
byte d17[8]={B00110,B00110,B00110,B00110,B00110,B00111,B00111,B00000}; //1st char
byte d18[8]={B00001,B00001,B00011,B00011,B00111,B11110,B11100,B00000}; //2nd char
byte d19[8]={B10000,B10000,B10000,B00000,B00000,B00000,B00000,B00000}; //3rd char

//O
byte d20[8]={B00110,B00110,B00111,B00011,B00001,B00000,B00000,B00000}; //4th char
byte d21[8]={B00000,B00000,B00000,B10000,B11000,B11111,B01111,B00000}; //5th char
byte d22[8]={B00011,B00011,B00111,B01110,B11100,B11000,B10000,B00000}; //6th char

//SPACE
byte d23[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000}; //7th char

//B
byte d24[8]={B00111,B00110,B00110,B00110,B00110,B00111,B00111,B00000}; //8th char
byte d25[8]={B11111,B00111,B00001,B00001,B00001,B11111,B11111,B00000}; //9th char
byte d26[8]={B00000,B00000,B10000,B10000,B10000,B10000,B00000,B00000}; //10th char

//B
byte d27[8]={B00001,B00001,B00001,B00001,B00001,B00001,B00001,B00000}; //11th char
byte d28[8]={B11111,B10001,B10000,B10000,B10000,B11111,B11111,B00000}; //12th char
byte d29[8]={B11000,B11000,B01100,B01100,B01100,B11100,B11000,B00000}; //13th char

//Y
byte d30[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000}; // 14th char
byte d31[8]={B11101,B01111,B00111,B00111,B00111,B00111,B00111,B00000}; // 15th char
byte d32[8]={B11000,B10000,B00000,B00000,B00000,B00000,B00000,B00000}; // 16th char




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


// Dobby 's Characters' creation

lcd.createChar(4, d1);
lcd.createChar(5, d2);
lcd.createChar(6, d3);
lcd.createChar(7, d4);
lcd.createChar(8, d5);
lcd.createChar(9, d6);
lcd.createChar(10, d7);
lcd.createChar(11, d8);
lcd.createChar(12, d9);
lcd.createChar(13, d10);
lcd.createChar(14, d11);
lcd.createChar(15, d12);
lcd.createChar(16, d13);
lcd.createChar(16, d14);
lcd.createChar(18, d15);
lcd.createChar(19, d16);
lcd.createChar(20, d17);
lcd.createChar(21, d18);
lcd.createChar(22, d19);
lcd.createChar(23, d20);
lcd.createChar(24, d21);
lcd.createChar(25, d22);
lcd.createChar(26, d23);
lcd.createChar(27, d24);
lcd.createChar(28, d25);
lcd.createChar(29, d26);
lcd.createChar(30, d27);
lcd.createChar(31, d28);
lcd.createChar(32, d29);
lcd.createChar(33, d30);
lcd.createChar(34, d31);
lcd.createChar(35, d32);




lcd.backlight(); // sets backlight on the screen
  lcd.setCursor(0, 0); // moves cursor to 1st row 1st character
 //!! lcd.print("    Hello!"); //  message on the display while initializing 

lcd.write(byte(4));

lcd.setCursor(1, 0);
lcd.write(byte(5));
lcd.setCursor(2, 0);
lcd.write(byte(6));
lcd.setCursor(3, 0);
lcd.write(byte(7));
lcd.setCursor(4, 0);
lcd.write(byte(8));
lcd.setCursor(5, 0);
lcd.write(byte(9));
lcd.setCursor(6, 0);
lcd.write(byte(10));
lcd.setCursor(7, 0);
lcd.write(byte(11));
lcd.setCursor(8, 0);
lcd.write(byte(12));
lcd.setCursor(9, 0);
lcd.write(byte(13));
lcd.setCursor(10, 0);
lcd.write(byte(14));
lcd.setCursor(11, 0);
lcd.write(byte(15));
lcd.setCursor(12, 0);
lcd.write(byte(16));
lcd.setCursor(13, 0);
lcd.write(byte(17));
lcd.setCursor(14, 0);
lcd.write(byte(18));
lcd.setCursor(15, 0);
lcd.write(byte(19));


lcd.setCursor(0, 1);
lcd.write(byte(20));
lcd.setCursor(1, 1);
lcd.write(byte(21));
lcd.setCursor(2, 1);
lcd.write(byte(22));
lcd.setCursor(3, 1);
lcd.write(byte(23));
lcd.setCursor(4, 1);
lcd.write(byte(24));
lcd.setCursor(5, 1);
lcd.write(byte(25));
lcd.setCursor(6, 1);
lcd.write(byte(26));
lcd.setCursor(7, 1);
lcd.write(byte(27));
lcd.setCursor(8, 1);
lcd.write(byte(28));
lcd.setCursor(9, 1);
lcd.write(byte(29));
lcd.setCursor(10, 1);
lcd.write(byte(30));
lcd.setCursor(11, 1);
lcd.write(byte(31));
lcd.setCursor(12, 1);
lcd.write(byte(32));
lcd.setCursor(13, 1);
lcd.write(byte(33));
lcd.setCursor(14, 1);
lcd.write(byte(34));
lcd.setCursor(15, 1);
lcd.write(byte(35));

 
  
  
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

#include <Wire.h>
#include "ST7036.h"
#include "bin.h"

//Hardware required:
//1: I2C LCD connected on standard pins
//2: Linear Pot connected on analog pin 1

long sensorValue = 0;  // variable to store the value coming from the sensor
long angle = 0;
ST7036 lcd = ST7036 ( 2, 16, 0x7C );                               //Gotcha with the address, needed to be shifted one to the left

//Large chars
char bn1[]={6,1,6, 1,6,32, 1,3,4, 3,3,4, 6,2,2,   6,3,1, 5,3,1, 1,1,4,   5,3,4, 5,3,4};
char bn2[]={6,2,6, 2,6,2,  5,2,2, 2,2,4, 32,6,32, 2,2,4, 5,2,4, 32,6,32, 5,3,4, 32,32,6};

void setup()
{
    lcd.init();
    lcd.on();
    lcd.setCursor(0, 0);
   
    lcd.print("Hello pot!");
    
    loadlargechars();
    
    delay(2000);
    lcd.clear();
}

void loadlargechars()
{
  uint8_t cc1[8] = { // Custom Character 1
     B8(11111),
     B8(11111),
     B8(11111),
     B8(00000),
     B8(00000),
     B8(00000),
     B8(00000),
     B8(00000)
     };

  uint8_t cc2[8] = { // Custom Character 2
     B8(00000),
     B8(00000),
     B8(00000),
     B8(00000),
     B8(00000),
     B8(11111),
     B8(11111),
     B8(11111)
     };

  uint8_t cc3[8] = { // Custom Character 3
     B8(11111),
     B8(11111),
     B8(11111),
     B8(00000),
     B8(00000),
     B8(00000),
     B8(11111),
     B8(11111)
     };

  uint8_t cc4[8] = { // Custom Character 4
     B8(11100),
     B8(11110),
     B8(11111),
     B8(11111),
     B8(11111),
     B8(11111),
     B8(11110),
     B8(11100)
     };
     
  uint8_t cc5[8] = { // Custom Character 5
     B8(00111),
     B8(01111),
     B8(11111),
     B8(11111),
     B8(11111),
     B8(11111),
     B8(01111),
     B8(00111)
     };     

  uint8_t cc6[8] = { // Custom Character 6
     B8(11111),
     B8(11111),
     B8(11111),
     B8(11111),
     B8(11111),
     B8(11111),
     B8(11111),
     B8(11111)
     };   

  uint8_t cc7[8] = { // Custom Character 7 Degree
     B8(01110),
     B8(10001),
     B8(10001),
     B8(10001),
     B8(01110),
     B8(00000),
     B8(00000),
     B8(00000)
     };  
    
    lcd.load_custom_character(1, cc1);
    lcd.load_custom_character(2, cc2);
    lcd.load_custom_character(3, cc3);
    lcd.load_custom_character(4, cc4);
    lcd.load_custom_character(5, cc5);
    lcd.load_custom_character(6, cc6);
    lcd.load_custom_character(7, cc7);
}



void loop()
{
  // read the value from the sensor:
  sensorValue = analogRead(A0);    
  // Makes the assumption that the pot turns 360 degrees, adjust the value below to compensate e.g. a 300 degree pot would be 3000
  angle = (sensorValue * 3600 / 1024); 
  display(angle);

  delay(10);
}

void display(int i) //Display the value in large characters
{
  lcd.clear();  
  //lcd.print(angle);
  PrintBigDeg(15);
  if (i == 0)
  {
    PrintBigDigit(0,8);
    PrintBigDot(11);
    PrintBigDigit(0,12);
  }
  int pos = 15;
  while(i>0)
  {
    pos -= 3;
    PrintBigDigit(i % 10,pos);
    i /= 10;
    if (pos==12){
     PrintBigDot(--pos);
    }
  }
  

}

void PrintBigDigit(uint8_t digit, uint8_t offset)
{

 // Line 1 of the one digit number
 lcd.setCursor(0,offset);
 lcd.write(bn1[digit*3]);
 lcd.write(bn1[digit*3+1]);
 lcd.write(bn1[digit*3+2]);

 // Line 2 of the one-digit number
 lcd.setCursor(1,offset);
 lcd.write(bn2[digit*3]);
 lcd.write(bn2[digit*3+1]);
 lcd.write(bn2[digit*3+2]);
}

void PrintBigDot(uint8_t offset)
{
  lcd.setCursor(1,offset);
  lcd.print('.');
}
void PrintBigDeg(int8_t offset)
{
  lcd.setCursor(0,offset);
  lcd.write(7);
}




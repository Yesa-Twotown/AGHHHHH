
int relayPinRed = 9;
int relayPinBlue= 10;
int relayPinGreen = 11;
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8 
int red = 0;
int green = 0;
int blue = 0; 

//oled libraryies
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 12
Adafruit_SSD1306 display (OLED_RESET);

//constatn variables
const int buttonPinYes = 2;                  //for the yes button                

//state variables
int buttonStateYes = 0;

//time 
int tt=500;



void setup() {  
//begin display 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setCursor(0,0);
//set relays as output
  pinMode(relayPinRed, OUTPUT);
  pinMode(relayPinGreen, OUTPUT);
  pinMode(relayPinBlue, OUTPUT);
//pins for TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);  
//setting relays to off
  digitalWrite(relayPinRed, HIGH);
  digitalWrite(relayPinGreen, HIGH);
  digitalWrite(relayPinBlue, HIGH);
//setting frequency scaling to 20%
  digitalWrite(S0, HIGH);  
  digitalWrite(S1, LOW);

//initialize the button pin
  pinMode(buttonPinYes, INPUT);

}

void loop()
{   
  int buttonStateYes = digitalRead(buttonPinYes);
  color(); 
  if (red < blue && blue < green && red < green && red <= 39)//for red
    {     
      display.setTextSize (2);
      display.setTextColor (WHITE);
      display.setCursor(0,0);
      display.println("Red Juice?");
      display.display();
      delay(5000);
      display.clearDisplay();
      display.setTextSize (2);
      display.setTextColor (WHITE);
      display.setCursor(0,0);
      display.println("Yes    No");
      display.display();
      delay(2000);
      buttonwaitYes(2);  
      display.clearDisplay();
      display.display();
      digitalWrite(relayPinRed, LOW);
      delay(500);
      digitalWrite(relayPinRed, HIGH);
      delay(500);
    }  
  else if (green < red && blue < green && blue < red)//blue
    {     
      display.setTextSize (2);
      display.setTextColor (WHITE);
      display.setCursor(0,0);
      display.println("Blue Juice?");
      display.display();
      delay(5000);
      display.clearDisplay();
      display.setTextSize (2);
      display.setTextColor (WHITE);
      display.setCursor(0,0);
      display.println("Yes    No");
      display.display();
      delay(2000);
      buttonwaitYes(2);
      display.clearDisplay();
      display.display();
      digitalWrite(relayPinBlue, LOW);
      delay(500);
      digitalWrite(relayPinBlue, HIGH);
      delay(500);
    }  
  else if (blue < red && green < blue && green < red)//for green
    {     
      display.setTextSize (2);
      display.setTextColor (WHITE);
      display.setCursor(0,0);
      display.println("Green Juice?");
      display.display();
      delay(5000);
      display.clearDisplay();
      display.setTextSize (2);
      display.setTextColor (WHITE);
      display.setCursor(0,0);
      display.println("Yes    No");
      display.display();
      delay(2000);
      buttonwaitYes(2);
      digitalWrite(relayPinGreen, LOW);
      delay(500);
      digitalWrite(relayPinGreen, HIGH);
      delay(500);
    }  
}

//button prompt to wait 
void buttonwaitYes(int buttonPinYes){
  int buttonStateYes = 0;
  while(1){
    buttonStateYes = digitalRead(buttonPinYes);
    if (buttonStateYes == HIGH){
      return;
    }
  }
}

//color calibration and detection
void color() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  red = pulseIn(sensorOut, LOW);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  green = pulseIn(sensorOut, LOW);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  blue = pulseIn(sensorOut, LOW);
  delay(100);
}

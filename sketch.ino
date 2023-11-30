//has to be put on an arduino to run

//#include <firmata.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int buttonPin1 = 2;
const int buttonPin2 = 3;

int button1Count = 0;
int button2Count = 0;
bool lastButtonState1 = LOW;
bool lastButtonState2 = LOW;

#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600);

  // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  delay(20);         
  oled.clearDisplay(); 

  oled.setTextSize(1);         
  oled.setTextColor(WHITE);    
  oled.setCursor(30, 20);      
  oled.println("Hello World"); 
  oled.display();          
}


void loop() {
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
    //if (Serial.available() > 0) {
    // Read the data from Python
    //String received_data = Serial.readStringUntil('\n');
    
    // Parse the received data
    //sscanf(received_data.c_str(), "%d,%d", &firstNumber, &secondNumber);

  //}



  if (buttonState1 != lastButtonState1 ) {
    Serial.println("Button 1 pressed!");
     //code for when it can run with python script
    // Firmata2.sendDigital(digitalRead(buttonPin1), buttonPin1);
    button1Count++;
    lastButtonState1 = buttonState1;
  }

  if (buttonState2 != lastButtonState2) {
    Serial.println("Button 2 pressed!");
     //code for when it can run with python script
    // Firmata2.sendDigital(digitalRead(buttonPin1), buttonPin1);
    button2Count++;
    lastButtonState2 = buttonState2;
  }

  // Display counts on the OLED screen
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.print("Yes Count: ");
  oled.println(button1Count);
  //oled.println(firstNumber);
  oled.setCursor(0, 20);
  oled.print("No Count: ");
  oled.println(button2Count);
  //oled.println(secondNumber);
  oled.display();

  delay(10); 
}


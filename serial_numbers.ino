#include "LedControl.h"
String inData;
// Arduino Pin 7 to DIN, 6 to Clk, 5 to LOAD, no.of devices is 1 

LedControl lc=LedControl(8,10,9,1);
void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,10);
  lc.clearDisplay(0);
  
  Serial.begin(9600);
  
  char number_string[] = "1234";
  set_numbers(number_string, sizeof(number_string));
  Serial.print("Arduino is here!");
} 

void set_numbers(char *numbers, int len) {
//  for(int i=0; i< 8; i++) {
//    lc.setDigit(0,i,0,false);
//  }
  lc.clearDisplay(0);
  for(int i=0; i< len; i++) {
    int number = numbers[len - i -2]- '0';
    if (number != "x" - "0") {
      lc.setDigit(0,i,number,false);
    }
  }
}

void loop() {
 while (Serial.available() > 0) {
        char recieved = Serial.read();
        
        // Process message when new line character is recieved
        if (recieved == '\n')
        {           
            // convert and set numbers
            char charBuf[inData.length()];
            inData.toCharArray(charBuf, inData.length());
            set_numbers(charBuf, inData.length());
            
            inData = ""; // Clear recieved buffer
        } else {
          inData += recieved; 
        }
    }
}


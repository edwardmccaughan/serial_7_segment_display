#include "LedControl.h"
String inData;
// Arduino Pin 7 to DIN, 6 to Clk, 5 to LOAD, no.of devices is 1 

LedControl lc=LedControl(8,10,9,1);
void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,10);
  lc.clearDisplay(0);
  
  Serial.begin(9600);
  Serial.print("Arduino is here!");
} 

void set_numbers(String numbers) {

  lc.clearDisplay(0);
  int length = numbers.length();
  for(int i=0; i< length; i++) {
    char currentChar = numbers.charAt(length - i -2);
    int number = currentChar -'0';
    
    
    if (number != "x" - "0") {
      lc.setDigit(0,i,number,false);
    }
  }
}

void process_command(String command) {
  set_numbers(command);
}


void loop() {
 while (Serial.available() > 0) {
        char recieved = Serial.read();
        
        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            process_command(inData);
            inData = ""; // Clear recieved buffer
        } else {
          inData += recieved;
        }
    }
}


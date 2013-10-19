#include "LedControl.h"



// Send /n terminated strings over serial to switch on LED sections
// - "n" sets the entire display to a number, x is blank
// --- "n12x34x56"
// - "d" sets a single digit. the first byte is the index of the digit, the second byte is the number
// - to set a blank digit, set the second byte to "s"
// --- "d11"
// - "l" sets a single led on or off. The first byte is the column, second is the row, third is "0" or "1"
// - to switch the led on or off
// --- "l621"


String inData;
// Arduino Pin 7 to DIN, 6 to Clk, 5 to LOAD, no.of devices is 1 
LedControl lc=LedControl(8,10,9,1);

int lc_address = 0;


void setup() {
  lc.shutdown(lc_address,false);
  lc.setIntensity(lc_address,10);
  lc.clearDisplay(lc_address);
  
  Serial.begin(9600);
  Serial.print("Arduino is here!");
  
} 

void set_numbers(String numbers) {
  lc.clearDisplay(lc_address);
  int length = numbers.length();
  for(int i=0; i< length; i++) {
    char currentChar = numbers.charAt(length - i -1);
    int number = currentChar -'0'; 
    
    if (number != "x" - "0") {
      lc.setDigit(lc_address,i,number,false);
    }
  }
}

void set_number(String param) {
  int index = param.charAt(0) -'0';
  int value = param.charAt(1);
 
  lc.setChar(lc_address,index,value,false);
}


void set_led(String param) {
  int     col = param.charAt(0) -'0';
  int     row = param.charAt(1) -'0';
  boolean value = param.substring(2,3) == "1";
  
  lc.setLed(lc_address, col, row, value);
}

void process_command(String command) {
  
  // strip off command char
  String param = command.substring(1);
  
  if (command.startsWith("n")) {
    set_numbers(param);
  } else if (command.startsWith("d")) {
    set_number(param);    
  } else if (command.startsWith("l")) {
    set_led(param);    
  }
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
          if (recieved != '\r') { //just ignore \r character
            inData += recieved;
          }
        }
    }
}


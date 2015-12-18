#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int lastmsg = 1;
String theMessage = "";
void setup(void){
  Serial.println("\n\nReceiving temperature and humidity records ...");
  Serial.begin(9600); //used for serial data communication opens the serial port and sets data rate for send/receive at 9600 bits per second
  radio.begin();
  radio.openReadingPipe(1,pipe); //reads the data from defined pipeline
  radio.startListening(); 
}
void loop(void){
  if (radio.available()){
    bool done = false;  
      done = radio.read(msg, 1); //reads the message
      char theChar = msg[0];
      if (msg[0] != 2){ 
        theMessage.concat(theChar); //if the character is not 2 concatenates the character else print the message
        }
      else {
       Serial.println(theMessage); 
       theMessage= ""; //reinitialize the message after priniting
      }
   }
}

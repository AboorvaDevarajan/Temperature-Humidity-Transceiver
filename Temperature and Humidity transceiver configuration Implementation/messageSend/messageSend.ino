#include <dht.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#define DHTPIN A0
dht DHT;
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
void setup(void){
  Serial.begin(9600); //used for serial data communication opens the serial port and sets data rate for send/receive at 9600 bits per second
  delay(300);
  Serial.println("Sending temperature and humidity records to Receiver..."); // prints the data in serial output
  radio.begin();
  radio.openWritingPipe(pipe);// writes data to pipeline uses 40 bit address pipe for transmission
}
void loop(void){
  DHT.read11(DHTPIN); // reads the current temperature and humidity using DHT
  char mssg[100];
  sprintf(mssg,"Current humidity= %d\nCurrent Temperature= %d",(int)DHT.humidity,(int)DHT.temperature); // convert the data to string
  String theMessage = mssg;
  int messageSize = theMessage.length();
  for (int i = 0; i < messageSize; i++) {
    int charToSend[1];
    charToSend[0] = theMessage.charAt(i);
    radio.write(charToSend,1); //transmits the data
  }    
  msg[0] = 2; // sending end message (2)
  radio.write(msg,1);
  radio.powerDown(); 
  delay(1000);
  radio.powerUp();
}


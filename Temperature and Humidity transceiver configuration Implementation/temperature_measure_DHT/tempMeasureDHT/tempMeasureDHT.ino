#include <dht.h>
#define DHTPIN A0
dht DHT;
void setup(){
  Serial.begin(9600);
  delay(300);//Let system settle
  Serial.println("Humidity and temperature\n\n");
  delay(700);
}
void loop(){
    DHT.read11(DHTPIN);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
  delay(800);
}// end loop()


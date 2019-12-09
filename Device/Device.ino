#include "congnghemoi.h"

Servo myServo;
DHT dht(DHTPIN, DHTTYPE);

float h = 0;
float t = 0;
int c = 3;
int p = 4;
byte incomingByte = 0b00000000;

void setup()
{
    Serial.begin(9600);
    myServo.attach(DOOR);
    dht.begin();
    
    digitalWrite(c, LOW);
    digitalWrite(p, HIGH);
}
void loop()
{
    if(Serial.available())
    {
        incomingByte = Serial.read();
        if(getID(incomingByte) == ID_DOOR && getInstruction(incomingByte) == OPEN)
            myServo.write(90);
        else if(getID(incomingByte) == ID_DOOR && getInstruction(incomingByte) == CLOSE)
            myServo.write(0);
        else
            changeDeviceStatus(incomingByte);
    }
    h = dht.readHumidity();
    t = dht.readTemperature();

    if (!isnan(h) && !isnan(t))
        Serial.println(String(t) + "*" + String(h));
    delay(1000);
}

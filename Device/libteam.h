#define ID_MASK 0b11110000
#define STATUS_MASK 0b00001111

#define ID_LED 0b00010000
#define ID_DOOR 0b000100000
#define ID_PUMP 0b00110000

#define CLOSE 0b00000001
#define OPEN 0b00000010

byte getID(byte b);
byte getStatus(byte b);
void changeDeviceStatus(byte b, int pin);


byte getID(byte b)
{
    return b & ID_MASK;
}
byte getStatus(byte b)
{
    return b & STATUS_MASK;
}

void changeDeviceStatus(byte b, int pin)
{
    byte id = getID(b);
    byte status = getStatus(b);
    digitalWrite(pin, status);
}
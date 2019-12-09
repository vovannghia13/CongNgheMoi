#ifndef CONGNGHEMOI_H
#define CONGNGHEMOI_H

#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>

#define ID_MASK 0b11110000
#define STATUS_MASK 0b00001111

#define ID_LED 0b00010000
#define ID_DOOR 0b00100000
#define ID_PUMP 0b00110000

#define CLOSE 0b00000001
#define OPEN 0b00000010

#define LED 13
#define PUMP 12
#define DOOR 9
#define DHTPIN 2
#define DHTTYPE DHT21



byte getID(byte b);
byte getStatus(byte b);
int getPin(byte b);
int getInstruction(byte b);
void changeDeviceStatus(byte b);

byte getID(byte b)
{
    return b & ID_MASK;
}
byte getStatus(byte b)
{
    return b & STATUS_MASK;
}

int getPin(byte b)
{
    byte id = getID(b);
    if (id == ID_LED)
        return LED;
    if (id == ID_PUMP)
        return PUMP;
    return -1;
}

int getInstruction(byte b)
{
    byte status = getStatus(b);
    if (status == OPEN)
        return 1;
    if (status == CLOSE)
        return 0;
    return -1;
}

void changeDeviceStatus(byte b)
{
    int pin = getPin(b);
    int status = getInstruction(b);
    
}

#endif

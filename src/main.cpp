#include <Arduino.h>
#include "QTRSensors.h"

int in1 = 2;
int in2 = 4;
int in3 = 6;
int in4 = 7;
int enA = 3;
int enB = 5;
int Emitter_pin = 8;

QTRSensors qtr;

const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];
void setup() {
// write your initialization code here
//sensor Array initialization
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]) {9, 10, 11, 12, 13}, SensorCount);
    qtr.setEmitterPin(Emitter_pin);
//serial cammunication
    Serial.begin(9600);
//motor controller initialization
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
//sensor Array calibratrion
    for (uint16_t i = 0; i < 200; i++)
    {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

    // print the calibration minimum values measured when emitters were on
    Serial.begin(9600);
    for (uint8_t i = 0; i < SensorCount; i++)
    {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    // print the calibration maximum values measured when emitters were on
    for (uint8_t i = 0; i < SensorCount; i++)
    {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);
}

void loop() {
// write your code here
    uint16_t position = qtr.readLineBlack(sensorValues);

    int gain = map(sensorValues,0,2500,0,255);


}
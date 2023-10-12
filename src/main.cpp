#include <Arduino.h>
#include "QTRSensors.h"

int in1 = 2;
int in2 = 4;
int in3 = 6;
int in4 = 7;
int enA = 3;
int enB = 5;
int Emitter_pin = 8;

// Define PID parameters
double Kp = 2.0;  // Proportional gain
double Ki = 0.0;  // Integral gain
double Kd = 1.0;  // Derivative gain
double dt = 0.01;  // Time step (adjust as needed)


// Advanced PID parameters
double maxMotorSpeed = 255;  // Maximum motor speed
double maxIntegral = maxMotorSpeed / Ki;  // Maximum integral term
double integral = 0;
double lastError = 0;
QTRSensors qtr;
//
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
void setup() {
// write your initialization code here
//sensor Array initialization
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]) {6, 7, 8, 9, 10, 11, 12, 13}, SensorCount);
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
    // Calculate error (adjust as needed based on sensor arrangement)
    double error = (sensorValues[0] - sensorValues[7]) + (sensorValues[1] - sensorValues[6]) +
                   (sensorValues[2] - sensorValues[5]) + (sensorValues[3] - sensorValues[4]);
    integral += Ki * error * dt;
    integral = constrain(integral, -maxIntegral, maxIntegral);
    // Calculate derivative
    double derivative = (error - lastError) / dt;

    // Calculate motor speeds
    double motorSpeed = Kp * error + integral + Kd * derivative;
    double leftMotorSpeed = maxMotorSpeed + motorSpeed;
    double rightMotorSpeed = maxMotorSpeed - motorSpeed;

    analogWrite(enA, leftMotorSpeed);

    analogWrite(enB, rightMotorSpeed);

    lastError = error;

    // Delay for the time step
    delay(dt * 1000);
}
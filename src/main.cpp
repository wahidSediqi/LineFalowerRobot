#include <Arduino.h>
#include "QTRSensors.h"

// Definerer pin-variabler for motorstyring og sensorer
int in1 = 4;
int enB = 3;
int in2 = 5;
int enA = 2;
int in3 = 6;
int in4 = 7;

int Emitter_pin = 16;

// Definerer PID-parametere
double Kp = 2.0;  // Proporsjonal forsterkning
double Ki = 0.0;  // Integral forsterkning
double Kd = 1.0;  // Derivert forsterkning
double dt = 0.01;  // Tidssteg (juster etter behov)

// Avanserte PID-parametere
double maxMotorSpeed = 255;  // Maksimal motorhastighet
double maxIntegral = maxMotorSpeed / Ki;  // Maksimal integralterm
double integral = 0;
double lastError = 0;
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

void setup() {
    // Initialiserer sensorene
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]) {8, 9, 10, 11, 12, 13, 14, 15}, SensorCount);
    qtr.setEmitterPin(Emitter_pin); // Valgfritt

    // Initialiserer seriell kommunikasjon
    Serial.begin(9600);

    // Initialiserer motorstyringen
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    // Kalibrerer sensorene
    for (uint16_t i = 0; i < 200; i++) {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW); // Slår av Arduinos LED for å indikere at kalibrering er ferdig

    // Skriver ut minimumsverdiene for kalibrering når emitterne var på
    Serial.begin(9600);
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    // Skriver ut maksimumsverdiene for kalibrering når emitterne var på
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);
}

void loop() {
    // Leser sensordata
    uint16_t position = qtr.readLineBlack(sensorValues);

    // Beregner feil (juster etter sensorenes plassering)
    double error = (sensorValues[0] - sensorValues[7]) + (sensorValues[1] - sensorValues[6]) +
                                                         (sensorValues[2] - sensorValues[5]) + (sensorValues[3] -
                                                                                                sensorValues[4]);//Beregner error mellom siste og første
    integral += Ki * error * dt;//integrasjonsdel
    integral = constrain(integral, -maxIntegral, maxIntegral);//kan brukes map istedenfor

    // Beregner den deriverte
    double derivative = (error - lastError) / dt;

    // Beregner motorhastigheter
    double motorSpeed = Kp * error + integral + Kd * derivative;
    double leftMotorSpeed = maxMotorSpeed + motorSpeed;
    double rightMotorSpeed = maxMotorSpeed - motorSpeed;

    // Angir motorhastigheter
    analogWrite(enA, int(leftMotorSpeed));
    analogWrite(enB, int(rightMotorSpeed));

    lastError = error;

    // Vent i tidssteg
    delay(dt * 1000);
}

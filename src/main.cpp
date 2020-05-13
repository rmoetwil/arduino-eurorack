#include <Arduino.h>
#include <SimpleTimer.h>

void cycle_on();
void cycle_off();

/**
 * Arduino based Eurorack Clock generator and more.
 * 
 * Inspired by SM Tik Tak. See https://www.youtube.com/watch?v=nBucMzlgESw
 *
 */

SimpleTimer timer;
int count = 0;

// Set the minimum and max range of the BPM input.
int maxBPM = 320;
int minBPM = 60;
int max_time = ((1 / (minBPM / 60)) * 1000);
int min_time = ((1 / (maxBPM / 60)) * 1000);
float currentBPM;
int maxPulseWidth = 90;

// Inputs
int bpmKnob = A0;
int pulseWidthKnob = A1;
int undefinedKnob = A2;

// Outputs
int output1 = 5;
int output2 = 6;
int output3 = 7;
int output4 = 2;
int output5 = 3;
int output6 = 4;

int led = 13;

void setup()
{

  //Serial.begin(9600);

  pinMode(led, OUTPUT);

  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output6, OUTPUT);

  cycle_on();
}

void loop()
{

  timer.run();
}

void cycle_off()
{
  digitalWrite(led, LOW);

  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output6, LOW);

  count++;

  if (count == 8)
  {
    count = 0;
  }
}

void cycle_on()
{
  digitalWrite(led, HIGH);

  switch (count)
  {
  case 0:
    digitalWrite(output1, HIGH);
    digitalWrite(output2, HIGH);
    digitalWrite(output3, HIGH);
    digitalWrite(output4, HIGH);
    digitalWrite(output5, HIGH);
    digitalWrite(output6, HIGH);
    break;

  case 1:
    digitalWrite(output1, HIGH);
    break;

  case 2:
    digitalWrite(output1, HIGH);
    digitalWrite(output2, HIGH);
    break;

  case 3:
    digitalWrite(output1, HIGH);
    break;

  case 4:
    digitalWrite(output1, HIGH);
    digitalWrite(output2, HIGH);
    digitalWrite(output3, HIGH);
    break;

  case 5:
    digitalWrite(output1, HIGH);
    break;

  case 6:
    digitalWrite(output1, HIGH);
    digitalWrite(output2, HIGH);
    break;

  case 7:
    digitalWrite(output1, HIGH);
    break;
  }

  int input1 = analogRead(bpmKnob);
  int input2 = analogRead(pulseWidthKnob);
  int input3 = analogRead(undefinedKnob);

  currentBPM = map(input1, 0, 1023, minBPM, maxBPM);

  float duration_percentage = map(input2, 0, 1023, 1, maxPulseWidth);

  int cycletime = (60000 / currentBPM);

  float cycle_start = cycletime;
  float cycle_stop = (cycletime * (duration_percentage / 100));

  timer.setTimeout(cycle_start, cycle_on);
  timer.setTimeout(cycle_stop, cycle_off);

  // Serial.print(" BPM: ");
  // Serial.print(currentBPM);
  // Serial.print(" Pulse Width: ");
  // Serial.print(duration_percentage);
  // Serial.print(" Unknown Knob: ");
  // Serial.println(input3);
}
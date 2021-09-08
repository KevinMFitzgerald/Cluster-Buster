#pragma once﻿
#include "ClusterBuster.h"
LMT35::LMT35()
{
  LM35_pin = 34;
  pinMode(LM35_pin, INPUT);
}
LMT35::LMT35(int r)
{
  LM35_pin = r;
  pinMode(LM35_pin, INPUT);
}
float LMT35::get_temp()
{
 float  RawValue = 0;
 double Voltage = 0;
 const int ADC_steps = 4095; // 0-4095
 const int MV_PER_CELL = 10;
 const int MV_RANGE = 3300;
 double tempC = 0;
 double tempF = 0;
  
  RawValue = analogRead(LM35_pin);
  Voltage = (float)RawValue*MV_RANGE/ADC_steps;
  Voltage = Voltage;
  tempC = Voltage/MV_PER_CELL;
  return tempC;


}
float LMT35::get_temp_adder(int a)
{
	float  RawValue = 0;
	double Voltage = 0;
	const int ADC_steps = 4095; // 0-4095
	const int MV_PER_CELL = 10;
	const int MV_RANGE = 3300;
	const int Op_Amp_Adder = a;
	double tempC = 0;
	double tempF = 0;

	RawValue = analogRead(LM35_pin);
	Voltage = (float)RawValue * MV_RANGE / ADC_steps;
	Voltage = Voltage - Op_Amp_Adder;
	tempC = Voltage / MV_PER_CELL;
	return tempC;


}
LEDS::LEDS()
{
	LEDS_pin = 0;
	pinMode(LEDS_pin, OUTPUT);

}
LEDS::LEDS(int r)
{
	LEDS_pin = r;
	pinMode(LEDS_pin, OUTPUT);
}
void LEDS::LEDS_ON()
{
	digitalWrite(LEDS_pin, HIGH);
}

void LEDS::LEDS_OFF()
{
	digitalWrite(LEDS_pin, LOW);
}

Level_Leds::Level_Leds()
{
	int pins[] = { 33,27,16,17 };

	for (int z = 0; z < (sizeof(pins)/ sizeof pins[0]); z++)
	{
		ledPins[z] = pins[z];
	}

	for (unsigned int n = 0; n < (sizeof(pins)/ sizeof pins[0]); n++)
	{
		pinMode(ledPins[n], OUTPUT);
	
	}
	for (unsigned int n = 0; n < (sizeof(pins)/ sizeof pins[0]); n++)
	{
		digitalWrite(ledPins[n], LOW);
	}
}
Level_Leds::Level_Leds(int led1, int led2, int led3, int led4)
{
	int pins[] = { led1, led2, led3, led4 };
	for (int z = 0; z < (sizeof(pins)/ sizeof pins[0]); z++)
	{
		ledPins[z] = pins[z];
	}
	for (unsigned int n = 0; n < (sizeof(pins)/ sizeof pins[0]); n++)
	{
		pinMode(ledPins[n], OUTPUT);
	}
	for (unsigned int n = 0; n < (sizeof(pins)/ sizeof pins[0]); n++)
	{
		digitalWrite(ledPins[n], LOW);
	}
}
int Level_Leds::Speed_Level(int r)
{
	const int Dc_Offset=100;
	const int ADC_Res = 4095;
	const unsigned int increment = ADC_Res / (sizeof(ledPins)/ sizeof ledPins[0]);//1024

	int Led_to_run = r / increment;//pot vaule divided by 1024, range between 0-4;
	
	for (int i = 0; i < Led_to_run; i++)
	{
		digitalWrite(ledPins[i], HIGH);
	}
	for(int i =4;i> Led_to_run;i--)
	{
		digitalWrite(ledPins[i-1], LOW);
	}
	int motorSpeed = map(r,0,4095,0,255);

	return motorSpeed;
}
void Level_Leds::Leds_Off()
{
	for (int i = 0; i < sizeof(ledPins); i++)
	{
		digitalWrite(ledPins[i], LOW);
	}
}
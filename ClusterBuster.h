#ifndef  ClusterBuster_h
#define  ClusterBuster_h
#include <Arduino.h>
class LMT35
{
private:
	int LM35_pin;
	public:
	LMT35();
	LMT35(int LM35_pin);
public:
	float get_temp();
	float get_temp_adder(int a);
	float temperature;
};

class LEDS
{
private:
	int LEDS_pin;
public:
	LEDS();
	LEDS(int LEDS_pin);
	void LEDS_ON();
	void LEDS_OFF();
};
class Level_Leds
{
private:
	int ledPins[4];
public:
	Level_Leds();
	Level_Leds(int led1, int led2, int led3, int led4);
	int Speed_Level(int r);
	void Leds_Off();
};
#endif
//
// END OF FILE
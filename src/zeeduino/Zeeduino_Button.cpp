#include "Arduino.h"

#include "Zeeduino_Button.h"


Zeeduino_Button::Zeeduino_Button(int pin)
{
	this->pin = pin;
	pressed = false;
	released = false;
	buttonState = BUTTON_STATE_UP;
	prevButtonState = buttonState;
	counter = 0;
	lastTimeSlot = 0;

	pinMode(pin, INPUT);
}

void Zeeduino_Button::processButton()
{
	// this removes transition information.
	// since the transition is an event, information about it
	// should be only available between two consecutive
	// calls to processButton().
	pressed = false;
	released = false;

	// simple debouncing algo
	if (digitalRead(pin) == BUTTON_STATE_UP)
		counter++;
	else
		counter--;

	uint32_t currentTimeSlot = millis() / 100; // every 10ms

	if (currentTimeSlot != lastTimeSlot)
	{
		// next time slot
		lastTimeSlot = currentTimeSlot;

		// update button state
		// during previous time slot
		// we counted up for whenever button was up and
		// we counted down for whenever button was down
		if(counter > 0)
			buttonState = BUTTON_STATE_UP;
		else
			buttonState = BUTTON_STATE_DOWN;

		// add button transition information
		if(prevButtonState != buttonState)
		{
			if(buttonState == BUTTON_STATE_DOWN)
				pressed = true;
			else
				released = true;

			prevButtonState = buttonState;
		}

		counter = 0;
	}
}

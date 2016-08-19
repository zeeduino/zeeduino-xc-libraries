
#ifndef ZEEDUINO_BUTTON_H_
#define ZEEDUINO_BUTTON_H_


// define what logical level corresponds to down/up button position
#define BUTTON_STATE_DOWN LOW
#define BUTTON_STATE_UP   HIGH

class Zeeduino_Button
{
public:
	Zeeduino_Button(int pin);
	int state() {return buttonState;}
	bool isPressed() {return pressed;}
	bool isReleased() {return released;}

	void processButton();

private:
	int pin;
	int buttonState;
	int prevButtonState;
	bool pressed;
	bool released;
	int32_t counter;
	uint32_t lastTimeSlot;
};


#endif /* BUTTON_H_ */

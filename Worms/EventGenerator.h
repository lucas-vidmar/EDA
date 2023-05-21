#pragma once

enum class eventType:int { Walking, Jumping, Refresh, Quit, Empty };

class EventGenerator
{
public:
	EventGenerator();
	~EventGenerator();

	virtual eventType getEvent() = 0;
	virtual void setEvent() = 0;
	virtual bool NotQuit(void)= 0;
	virtual bool HayEvento(void) = 0;



};


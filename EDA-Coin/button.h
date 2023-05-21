#pragma once

#include "drawableObject.h"

enum buttonStates { Pressed, NotPressed };

class button : public drawableObject {
public:
	/*Default Builder*/
	button() {
		texture = NULL;
		pressedTexture = NULL;
		posX = 0;
		posY = 0;
		sizeX = 0;
		sizeY = 0;
		state = buttonStates::NotPressed;
		text = NULL;
		font = NULL;
	}
	/*Builder*/
	button(const char* texture_, const char* pressed_, double posX_, double posY_, double sizeX_, double sizeY_, const char* text_, ALLEGRO_FONT* font_) {
		texture = al_load_bitmap(texture_);
		pressedTexture = al_load_bitmap(pressed_);
		if (texture == nullptr)
			delete this;
		posX = posX_;
		posY = posY_;
		sizeX = sizeX_;
		sizeY = sizeY_;
		text = text_;
		font = font_;
		state = buttonStates::NotPressed;
	}
	/*Destroyer*/
	~button() {}

	/*Setter*/
	void set_state(bool state_) { state = state_; }
	void toggle_state(void) { state = !state; }
	void change_text(const char* newtext) { text = newtext; }

	/*Getters*/
	bool get_state(void) { return state; }
	const char* get_text(void) { return text; }

	/*Methods*/
	void drawObject();
	void dedrawObject() { return; }
	void pressButton(void);
	void releaseButton(void);


private:
	ALLEGRO_BITMAP* pressedTexture;
	bool state;
	const char* text;
	ALLEGRO_FONT* font;
};


#include "WinMessage.h"

void WinMessage::draw(RenderWindow &window)
{
	window.draw(this->backgroundSprite_);
}

void WinMessage::events(RenderWindow &window)
{
	Event event;
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	while (window.pollEvent(event))
	{
		if (event.type == Event::MouseButtonPressed)
			if (event.key.code == Mouse::Left)
			{
				this->isMessage = false;
				window.clear();
			}
	}
}

bool WinMessage::getIsMessage()
{
	return this->isMessage;
}

WinMessage::WinMessage(bool status)
{
	this->isMessage = true;
	if(status)
	{
        this->backgroundImage_.loadFromFile("images/window_win.png");
        this->backgroundSprite_.setTexture(this->backgroundImage_);
	}
	else
        {
            this->backgroundImage_.loadFromFile("images/window_lose.png");
            this->backgroundSprite_.setTexture(this->backgroundImage_);
        }
}

WinMessage::~WinMessage()
{
}

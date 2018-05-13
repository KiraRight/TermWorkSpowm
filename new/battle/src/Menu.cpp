#include "Menu.h"

void Menu::drawMenu(RenderWindow &window)
{
	this->isMenu = true;
	window.draw(this->backgroundSprite_);
	for (unsigned int i = 0; i < this->buttons_.size(); i++)
	{
		window.draw(this->buttons_[i]);
	}
}

void Menu::setMenu()
{
	this->buttons_.clear();
	int tabulation = 187;
	Sprite temp;
	temp.setTexture(this->startGame_);
	temp.setPosition(tabulation, 100.0);
	this->buttons_.push_back(temp);
	temp.setTexture(this->exit_);
	temp.setPosition(tabulation, 220.0);
	this->buttons_.push_back(temp);
}

void Menu::menuEvent(RenderWindow &window)
{
	Event event;
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			this->isMenu = false;
			window.close();
		}
		if (event.type == Event::MouseButtonPressed)                        //âûáîð ïîçèöèè
			if (event.key.code == Mouse::Left)
			{
				for (unsigned int n = 0; n < this->buttons_.size(); n++)
					if (this->buttons_[n].getGlobalBounds().contains(pos.x, pos.y))
					{
						switch (n)
						{
						case 0:
							this->isMenu = false;
							this->numberButton_ = 1;          //1-Start, 2-About
							window.clear();
							break;
						case 1:
							this->isMenu = false;
							window.close();
						}
					}
			}
	}
}

bool Menu::getState()
{
	return this->isMenu;
}

Sprite Menu::getBackgroundSprite()
{
	return this->backgroundSprite_;
}

int Menu::getNumberButton()
{
	return this->numberButton_;
}

Menu::Menu()
{
	this->backgroundImage_.loadFromFile("images/window.png");
	this->backgroundSprite_.setTexture(this->backgroundImage_);
	this->backgroundSprite_.setPosition(0, 0);
	this->startGame_.loadFromFile("images/StartGame.png");
	this->exit_.loadFromFile("images/Exit.png");
	this->isMenu = false;
	this->numberButton_ = 0;
}


Menu::~Menu()
{
}

#ifndef WINMASSAGE_H
#define WINMASSAGE_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class WinMessage
{
public:
	void draw(RenderWindow &window);
	void events(RenderWindow &window);
	bool getIsMessage();

	WinMessage(bool status);
	~WinMessage();
private:
	Texture backgroundImage_;
	Sprite backgroundSprite_;
	bool isMessage;
};

#endif // WINMASSAGE_H

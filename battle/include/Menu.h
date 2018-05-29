#ifndef MENU_H
#define MENU_H


#include <SFML/Graphics.hpp>
#include<vector>

using namespace std;
using namespace sf;

class Menu
{
public:
	void drawMenu(RenderWindow &window);
	void setMenu();
	void menuEvent(RenderWindow &window);
	bool getState();
	Sprite getBackgroundSprite();
	int getNumberButton();


	Menu();
	~Menu();
private:
	vector<Sprite> buttons_;
	Texture startGame_, exit_, rules_;
	Texture backgroundImage_;
	Sprite backgroundSprite_;
	bool isMenu;
	int numberButton_;
};

#endif // MENU_H

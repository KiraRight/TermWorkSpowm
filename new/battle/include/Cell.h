#ifndef CELL_H
#define CELL_H

class Cell
{
public:
	Cell(int x, int y);
	~Cell();

	void setShip();
	void clean();
	bool getBusyness();
	bool checkShip();
	void setBusy();
	bool getWalked();
	void setWalked();

private:
	bool isShip_;
	bool walked_;
	bool busy_;
	int x_;
	int y_;
};


#endif // CELL_H

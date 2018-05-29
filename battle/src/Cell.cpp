#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->busy_ = false;
	this->isShip_ = false;
	this->walked_ = false;
	this->x_ = x;
	this->y_ = y;
}


Cell::~Cell()
{
}

void Cell::setShip()
{
	this->isShip_ = true;
	this->busy_ = true;
}

void Cell::clean()
{
	this->busy_ = false;
	this->isShip_ = false;
	this->walked_ = false;
}

bool Cell::getBusyness()
{
	return this->busy_;
}

bool Cell::checkShip()
{
	return this->isShip_;
}

void Cell::setBusy()
{
	this->busy_ = true;
}

bool Cell::getWalked()
{
	return this->walked_;
}

void Cell::setWalked()
{
	this->walked_ = true;
}

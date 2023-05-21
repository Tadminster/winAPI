#pragma once

class TrumpCard
{
private:
	string shape;
	int number;

public:
	TrumpCard(int shape, int number)
	{
		if (shape == 0)
			this->shape = "¢¾";
		else if (shape == 1)
			this->shape = "¡ß";
		else if (shape == 2)
			this->shape = "¢¼";
		else if (shape == 3)
			this->shape = "¢À";
		this->number = number;
	}

	int getNumber() const
	{
		return this->number;
	}

	string getShape() const
	{
		return this->shape;
	}
};

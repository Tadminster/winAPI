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
			this->shape = "��";
		else if (shape == 1)
			this->shape = "��";
		else if (shape == 2)
			this->shape = "��";
		else if (shape == 3)
			this->shape = "��";
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

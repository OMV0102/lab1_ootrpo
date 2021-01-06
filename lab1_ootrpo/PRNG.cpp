// реализация класса PRNG (Pseudo Random Number Generator)
#include "PRNG.h"

// конструктор
PRNG::PRNG(){}

// деструктор
PRNG::~PRNG(){}

bool PRNG::GetSequence(int size, vector<double>*sequence, string *errorMessage)
{
	*errorMessage = "";
	try
	{
		if(size < 1) throw new exception("Размер последовательности не должен быть меньше 1!");
		default_random_engine engine;
		engine.seed(time(0));
		gamma_distribution<> gamma(1.5, 1.0); // альфа = v+1, бетта = 1, v: 0.5   4   6
		vector<double> values(size); // вектор с size элементами (по дефолту нули)

		for(int i = 0; i < size; i++)
		{
			values[i] = gamma(engine);
		}
		*sequence = values;
	}
	catch(const char *error)
	{
		*errorMessage = error;
		return false;
	}
	return true;
}
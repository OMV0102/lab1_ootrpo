// реализаци€ класса PRNG (Pseudo Random Number Generator)
// генератор последовательности по закону распредлени€ ѕирсона типа II
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
		if(size < 1) throw "–азмер последовательности не должен быть меньше 1!";
		default_random_engine engine;
		engine.seed(time(0));
		gamma_distribution<> gamma(this->alpha, this->beta);
		vector<double> values(size); // вектор размером size (по дефолту нули)

		for(int i = 0; i < size; i++)
		{
			double g1 = gamma(engine);
			double g2 = gamma(engine);
			values[i] = (2.0 * g1) / (g1 + g2) - 1.0;
		}
		*sequence = values;
		values.~vector();
	}
	catch(const char *msg)
	{
		*errorMessage = string(msg);
		return false;
	}
	return true;
}

double PRNG::GetV()
{
	return this->v;
}
bool PRNG::SetV(double vNew)
{
	if(vNew < 0.0)
		return false;
	else
		this->v = vNew;

	return true;
}

double PRNG::GetAlpha()
{
	return this->alpha;
}
bool PRNG::SetAlpha(double alphaNew)
{
	if(alphaNew < 0.0 || (fabs(alphaNew) < this->delta))
		return false;
	else
		this->alpha = alphaNew;

	return true;
}

double PRNG::GetBeta()
{
	return this->beta;
}
bool PRNG::SetBeta(double betaNew)
{
	if(betaNew < 0.0 || (fabs(betaNew) < this->delta))
		return false;
	else
		this->beta = betaNew;

	return true;
}
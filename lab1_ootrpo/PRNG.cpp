// ���������� ������ PRNG (Pseudo Random Number Generator)
#include "PRNG.h"

// �����������
PRNG::PRNG(){}

// ����������
PRNG::~PRNG(){}

bool PRNG::GetSequence(int size, vector<double>*sequence, string *errorMessage)
{
	*errorMessage = "";
	try
	{
		if(size < 1) throw new exception("������ ������������������ �� ������ ���� ������ 1!");
		default_random_engine engine;
		engine.seed(time(0));
		gamma_distribution<> gamma(1.5, 1.0); // ����� = v+1, ����� = 1, v: 0.5   4   6
		vector<double> values(size); // ������ � size ���������� (�� ������� ����)

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
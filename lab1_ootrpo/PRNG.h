// определение класса PRNG (Pseudo Random Number Generator)
// генератор последовательности по закону распредления Пирсона типа II
#include <random>
#include <ctime>
#include <math.h>
#include <vector>
using namespace std;

class PRNG
{
	public:
	PRNG(unsigned int seedNew); // конструктор
	PRNG(); // конструктор по умолчанию
	~PRNG(); // деструктор по умолчанию
	
	unsigned int GetSeed(); // получить начальное значение генерации
	double GetV(); // параметр формы;
	double GetAlpha(); // альфа - параметр масштаба гамма-функции
	double GetBeta(); // бета - параметр формы гамма-функции (лямбда)
	bool SetV(double vNew); // по умолчанию v = 0.5
	bool SetAlpha(double alphaNew); // по умолчанию a = v + 1.0
	bool SetBeta(double betaNew); // по умолчанию бета = 1.0
	bool GetSequence(int size, vector<double> *sequence, string *errorMessage);
	

	private:
	double v = 0.5; // параметр формы; при v = 0.5 полукруговое распределение
	double alpha = v + 1.0; // параметр масштаба гамма-функции
	double beta = 1.0; // параметр формы гамма-функции (лямбда)
	unsigned int seed = time(0);
};
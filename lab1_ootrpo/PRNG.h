// ����������� ������ PRNG (Pseudo Random Number Generator)
#include <random>
#include <ctime>
using namespace std;

class PRNG
{
	public:
	PRNG(); // �����������
	~PRNG(); // ����������
	bool GetSequence(int size, vector<double> *sequence, string *errorMessage);

	//private:

};
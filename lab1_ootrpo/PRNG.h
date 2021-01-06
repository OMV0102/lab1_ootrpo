// ����������� ������ PRNG (Pseudo Random Number Generator)
// ��������� ������������������ �� ������ ������������ ������� ���� II
#include <random>
#include <ctime>
#include <math.h>
#include <vector>
using namespace std;

class PRNG
{
	public:
	PRNG(); // �����������
	~PRNG(); // ����������
	double GetV(); // �������� �����;
	double GetAlpha(); // ����� - �������� �������� �����-�������
	double GetBeta(); // ���� - �������� ����� �����-������� (������)
	bool SetV(double vNew); // �� ��������� v = 0.5
	bool SetAlpha(double alphaNew); // �� ��������� a = v + 1.0
	bool SetBeta(double betaNew); // �� ��������� ���� = 1.0
	bool GetSequence(int size, vector<double> *sequence, string *errorMessage);
	

	private:
	double v = 0.5; // �������� �����; ��� v = 0.5 ������������ �������������
	double alpha = v + 1.0; // �������� �������� �����-�������
	double beta = 1.0; // �������� ����� �����-������� (������)
	
	public:
	double delta = 1e-5; // �������� ����������� ������� �����
};
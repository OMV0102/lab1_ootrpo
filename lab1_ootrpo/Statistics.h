// ���������� ������ Statistics
// ������� �������������� �������������
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

class Statistics
{
	public:
	Statistics(); // ����������� �� ���������
	~Statistics(); // ���������� �� ���������

	double SumElements(std::vector<double> elements);
	double SumElementsAbs(vector<double> elements);

	private:
};
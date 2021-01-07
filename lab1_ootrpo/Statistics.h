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
	double MeanElements(vector<double> elements);
	double GetTrimmedMean(vector<double> elements, double percent);
	double GetDispersion(vector<double> elements);
	double GetMedian(vector<double> elements);
	vector<double> SortVector(vector<double> elements, bool sortMode);

	private:
	
};
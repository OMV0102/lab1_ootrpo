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

	vector<double> SortVector(vector<double> elements, bool sortMode);
	double SumElements(std::vector<double> elements);
	double GetMean(vector<double> elements);
	double GetMedian(vector<double> elements);
	double GetTrimmedMean(vector<double> elements, double percent);
	double GetWinsorizedMean(vector<double> elements, double percent);

	private:
	
};
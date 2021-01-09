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

	public:
	vector<double> SortVector(vector<double> elements, bool sortMode);
	double SumElements(std::vector<double> elements);
	double GetMean(vector<double> elements);
	double GetDispersion(vector<double> elements);
	double GetMedian(vector<double> elements);
	double GetTrimmedMean(vector<double> elements, double percent);
	double GetWinsorizedMean(vector<double> elements, double percent);
	void DivideOnIntervals(vector<double> elements);

	private:
	double GammLn(double x); // ���������� ��������� ����� - ������� ��� x > 0
	double Gamma(double x); // ���������� ����� - ������� ��� x > 0
	static const int cofSize = 8; // ������ ������� �������������
	static double cof[cofSize]; // ������� ������������� ��� GammaLn

	public:
	double Beta(double x, double y); // ���������� ���� - ������� ��� x > 0, y > 0
	
};
// ���������� ������ Statistics
// ������� �������������� �������������
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

static struct intervalStruct
{
	double left; // ������ ������� ���������
	double right; // ������� ������� ���������
	int elemNumber = 0; // ���������� ��������� ������������������ � ���������
};

class Statistics
{
	public:
	Statistics(); // ����������� �� ���������
	~Statistics(); // ���������� �� ���������

	// ���� ������
	public:
	private:
	static const int cofSize = 8; // ������ ������� �������������
	static double cof[cofSize]; // ������� ������������� ��� GammaLn

	// ������ ������
	public:
	vector<double> SortVector(vector<double> elements, bool sortMode);
	double SumElements(std::vector<double> elements);
	double GetMean(vector<double> elements);
	double GetDispersion(vector<double> elements);
	double GetMedian(vector<double> elements);
	double GetTrimmedMean(vector<double> elements, double percent);
	double GetWinsorizedMean(vector<double> elements, double percent);
	vector<intervalStruct> DivideOnIntervals(vector<double> elements);
	bool CheckNonZeroInterval(vector<double> elements, int intervalNum, vector<intervalStruct> *intervals);
	double Beta(double x, double y); // ���������� ���� - ������� ��� x > 0, y > 0
	
	private:
	double GammLn(double x); // ���������� ��������� ����� - ������� ��� x > 0
	double Gamma(double x); // ���������� ����� - ������� ��� x > 0	
};
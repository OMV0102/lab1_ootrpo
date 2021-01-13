// ����������� ������ Statistics
// ������� �������������� �������������
#include "Statistics.h"
using namespace std;

// �����������
Statistics::Statistics(double vParam)
{
    this->v = vParam;
    this->betaValue = this->Beta(vParam + 1.0, vParam + 1.0);
}
// ���������� �� ���������
Statistics::~Statistics(){}

// ���������� ������������������
// ���� true - �� �����������; false - �� �������� 
vector<double> Statistics::SortVector(vector<double> elements, bool sortMode)
{
    if(sortMode == true)
        sort(elements.begin(), elements.end()); // ���������� �� �����������
    else
        sort(elements.begin(), elements.end(), greater<double>()); // ���������� �� ��������
    
    return elements;
}

// ���������� ����� ���������
double Statistics::SumElements(vector<double> elements)
{
    double sum = 0.0;
    for_each(elements.begin(), elements.end(), [&](double elem)
    {
        sum += elem;
    });
    return sum;
}

// ���������� ������� �������������� ��������� ������������������ (���. ��������)
double Statistics::GetMean(vector<double> elements)
{
    double mean = 0.0;
    mean = this->SumElements(elements) / (double) elements.size();
    return mean;
}

// ������� ��������� �������� ������������������
double Statistics::GetDispersion(vector<double> elements)
{
    double mean = this->GetMean(elements);
    double disp = 0.0;
    int N = elements.size();
    // ������� ���. �������� ��� sum(elem[i]^2)/N - mean^2
    for(int i = 0; i < N; i++)
    {
        disp += pow(elements[i] - mean, 2.0);
    }
    disp /= (double) N;

    return disp;
}

// ������� ������� ������������������
double Statistics::GetMedian(vector<double> elements)
{
    double median = 0.0;
    int N = elements.size();
    if(N % 2 != 0) // ��� ��������� ����� ���������
        median = elements.at(N / 2); // ������� � ��������� ������������������
    else // ��� ������� ����� ���������
    {
        // ������� �������������� ���� ����������� ���������
        median = (elements.at(N/2 - 1) + elements.at(N/2)) / 2.0;
    }

    return median;
}

// ������� ���������� �������� c ��������� %
double Statistics::GetTrimmedMean(vector<double> elements, double alpha)
{
    double trMean = 0.0;
    int k = (int)(elements.size() * alpha);
    if((2*k + 1) > elements.size()) throw "���������� ��������� ������� ����, ����� ��������� ��������� ������� ��� ��������� �������� ��������!";
    elements = this->SortVector(elements, true);
    // �������� k ��������� � ������ � �����
    for(int i = 0; i < k; i++)
    {
        elements.erase(elements.begin());
        elements.pop_back();
    }
    // ������� �������� �������� ��� ��������� ���������
    trMean = this->GetMean(elements);
    return trMean;
}

// ������� ���������������� �������� c ��������� %
double Statistics::GetWinsorizedMean(vector<double> elements, double alpha)
{
    double trMean = 0.0;
    int N = elements.size();
    int k = (int) (N * alpha);
    if((2*k) > elements.size()) throw "���������� ��������� ������� ����, ����� ��������� ��������������� ������� ��� ��������� ��������!";
    elements = this->SortVector(elements, true);
    // ������ k ��������� � ������ � ����� �� k+1 (��� N-k-1)
    for(int i = 0; i < k; i++)
    {
        elements[i] = elements[k];
        elements[N-1-i] = elements[N-1-k];
    }
    // ������� �������� �������� ��� ��������� ���������
    trMean = this->GetMean(elements);
    return trMean;
}

// ������� ��������� ������������������ �� ��������� ��� �������� ��^2
vector<intervalStruct> Statistics::DivideOnIntervals(vector<double> elements)
{
    vector<intervalStruct> intervals;
    int elemNum = elements.size(); // ���������� ��������� � ������������������
    int intervalNum = 2; // ���������� ����������

    // ����������� ���������� ���������� ����������
    if(elemNum >= 40 && elemNum <= 100)
        intervalNum = 10;
    else if(elemNum >=100  && elemNum <= 500)
        intervalNum = 15;
    else if(elemNum >= 500 && elemNum <= 1000)
        intervalNum = 20;
    else if(elemNum >= 1000 && elemNum <= 10000)
        intervalNum = 25;
    else if(elemNum >= 10000)
        intervalNum = 30;

    while(true)
    {
        bool res = CheckNonZeroInterval(elements, intervalNum, &intervals);
        if(res == true)
            break;
        else
        {
            intervalNum--;
            if(intervalNum == 1) break; // ��� �������� ��� 2 ��������� (��������� �� �������������� �����)
        }
    }

    return intervals;

}

// ��������, ��� � ������ ��������� ���� ���� �� ���� ���������
// ���� ���-�� ���������� ����� ������� (return true), �� � intervals ���� ������� ����������
bool Statistics::CheckNonZeroInterval(vector<double> elements, int intervalNum, vector<intervalStruct> *intervals)
{
    double intervalSize = 0.0; // ������ ������ ���������
    vector<intervalStruct> vectorTemp; // ��������� ������ ��� �������� ����������
    intervalStruct temp;
    bool result = true; // ��������� ���������� ������������������ �� ���������
    int elemNumAll = elements.size(); // ���������� ��������� � ������������������
    intervalSize = abs((elements[elemNumAll - 1] - elements[0]) / (double) intervalNum);
    elements = SortVector(elements, true); // ��������� �������� �� �����������
    
    
    int i = 0; // i ������ �� ����������
    while(result == true && i < intervalNum)
    {
        temp.elemNumber = 0;
        temp.left = elements[0] + i * intervalSize;
        temp.right = elements[0] + (double)(i+1) * intervalSize;
        int j = 0;
        if(i == 0)// ������ �������[0] ������������������ � ����� ������ ����� � ������ ���������
        {
            temp.elemNumber++;
            j = 1;
        }
        else 
            j = 0;

        for(j; j < elemNumAll; j++)
        {
            if(temp.left < elements[j] && elements[j] <= temp.right)
                temp.elemNumber++;
        }
        vectorTemp.push_back(temp);
        if(temp.elemNumber < 1) result = false;
        i++;
    }
    if(result == true) *intervals = vectorTemp;

    return result;
}

// �������� ��������������� ������������������ ������� ��-������� �������
// n - ���������� ��������� � �������������� ������������������
bool Statistics::CheckChiSquaredTest(vector<intervalStruct> intervals, int n, double alpha)
{
    double s = 0.0; // ����������� ���������� ��������
    int N = intervals.size(); // ���������� ����������
    double p = 0.0; // �����������
    double pSum = 0.0; // ����� ������������ ����
    bool result = false; // ��������� �������� ���������� �� ��������
    for(int i = 0; i < N; i++)
    {
        p = Probability(intervals[i].left, intervals[i].right, pow(2.0, 20.0));
        s += (pow(((double)intervals[i].elemNumber/ (double)n) - p, 2.0) / p) * (double) n;
        pSum += p; // ��� ������� ����� ���� p ������ ���� ����� 1
    }

    // �������� ������������ �������� � ������������ ���������� � �������
    double sMax = GetLimitValueChiSquared(N - 1, alpha);
    if(s < sMax)
        result = true;
    else
        result = false;

    return result;
}

double Statistics::GetLimitValueChiSquared(int r, double alpha)
{
    if(0 < r || r > 30) return 0.0; // ���� ������� ������� �� �� 0 �� 30, �� �� ������
    int aSize = size(this->valuesChiSquared[0]);
    int aIndex = -1;
    double result = 0.0;
    double delta = 1e-4; // �������� ����������� ������� �����

    for(int i = 0; i < aSize; i++)
    {
        if((valuesChiSquared[0][i] - alpha) < delta)
        {
            aIndex = i;
            break;
        }
    }
    if(aIndex < 0)  return 0.0;
    result = valuesChiSquared[r][aIndex];
    return result;
}

// ���������� �������� ������� ��������� ������������� ������� II ����
// (�������� v � beta ��� ����������� � ������� ������)
double Statistics::f(double x)
{
    double result = 0.0;
    result = 1.0 - pow(x, 2.0);
    result /= 4.0;
    result = pow(result, this->v);
    result /= (2.0 * this->betaValue);

    return result;
}

// ���������� ����������� (������� �������� ���������� ��������������)
double Statistics::Probability(double a, double b, int stepCount)
{
    double sum = 0.0;
    double diff = abs(b - a);
    double step = diff / (double) stepCount;
    for(int i = 0; i < stepCount; i++)
    {
        sum += this->f(a + (double)i * step);
    }
    sum += (this->f(a) + this->f(b)) / 2.0;
    sum *= step;

    return sum;
}

// �������� �����-�������
double Statistics::GammLn(double x)
{
    double y, ser, *co;
    int j;
    // ���������� �������������������
    ser = cof[1];
    y = x;
    co = cof + 2;
    for(j = 2; j < cofSize; j++)
    {
        y += 1.;
        ser += (*co) / y;
        co++;
    }
    // � ������ ������ �������
    y = x + 5.5;
    y -= (x + 0.5) * log(y);
    y = -y + log(cof[0] *ser / x);
    return y;
}

// ������� ������������� ��� GammaLn
double Statistics::cof[cofSize] = {
    2.5066282746310005,
    1.0000000000190015,
    76.18009172947146,
    -86.50532032941677,
    24.01409824083091,
    -1.231739572450155,
    0.1208650973866179e-2,
    -0.5395239384953e-5};

// �����-�������
double Statistics::Gamma(double x)
{
    return(exp(GammLn(x)));
}

// ����-�������
double Statistics::Beta(double x, double y)
{
    return(exp(GammLn(x) + GammLn(y) - GammLn(x + y)));
}

// ������� ���������� ��������
double Statistics::valuesChiSquared[31][11] =
{
    {0.5, 0.4, 0.3, 0.2, 0.1, 0.05, 0.025, 0.01, 0.005, 0.001, 0.0005},
    {0.454936423, 0.708326301, 1.074194171, 1.642374415, 2.705543454, 3.841458821, 5.023886187, 6.634896601, 7.879438577, 10.82756617, 12.11566515},
    {1.386294361, 1.832581464, 2.407945609, 3.218875825, 4.605170186, 5.991464547, 7.377758908, 9.210340372, 10.59663473, 13.81551056, 15.20180492},
    {2.365973884, 2.946166073, 3.664870783, 4.641627676, 6.251388631, 7.814727903, 9.348403604, 11.34486673, 12.83815647, 16.2662362, 17.72999623},
    {3.35669398, 4.044626491, 4.878432967, 5.988616694, 7.77944034, 9.487729037, 11.14328678, 13.27670414, 14.860259, 18.46682695, 19.997355},
    {4.351460191, 5.131867074, 6.064429984, 7.289276127, 9.2363569, 11.07049769, 12.83250199, 15.08627247, 16.74960234, 20.51500565, 22.10532678},
    {5.348120627, 6.210757195, 7.231135332, 8.55805972, 10.64464068, 12.59158724, 14.44937534, 16.81189383, 18.54758418, 22.45774448, 24.10279899},
    {6.345811196, 7.283207633, 8.383430829, 9.8032499, 12.01703662, 14.06714045, 16.01276427, 18.47530691, 20.27773987, 24.32188635, 26.01776771},
    {7.344121498, 8.350525468, 9.524458193, 11.03009143, 13.36156614, 15.50731306, 17.53454614, 20.09023503, 21.95495499, 26.12448156, 27.8680464},
    {8.342832692, 9.413640094, 10.65637201, 12.24214547, 14.68365657, 16.9189776, 19.0227678, 21.66599433, 23.58935078, 27.87716487, 29.6658081},
    {9.341817766, 10.47323623, 11.78072263, 13.44195757, 15.98717917, 18.30703805, 20.48317735, 23.20925116, 25.18817957, 29.58829845, 31.41981251},
    {10.34099807, 11.52983384, 12.8986682, 14.63142051, 17.27500852, 19.67513757, 21.92004926, 24.72497031, 26.75684892, 31.26413362, 33.136615},
    {11.34032238, 12.58383797, 14.01110017, 15.81198622, 18.54934779, 21.02606982, 23.33666416, 26.21696731, 28.29951882, 32.90949041, 34.82127464},
    {12.33975588, 13.63557099, 15.11872165, 16.98479702, 19.81192931, 22.36203249, 24.73560488, 27.68824961, 29.81947122, 34.52817897, 36.47779372},
    {13.33927415, 14.68529426, 16.22209861, 18.15077056, 21.06414421, 23.6847913, 26.11894805, 29.14123774, 31.31934962, 36.12327368, 38.10940393},
    {14.33885951, 15.73322295, 17.3216945, 19.31065711, 22.30712958, 24.99579014, 27.48839286, 30.57791417, 32.80132065, 37.69729822, 39.71875979},
    {15.33849889, 16.77953671, 18.41789439, 20.46507929, 23.54182892, 26.2962276, 28.84535072, 31.99992691, 34.26718654, 39.25235479, 41.30807372},
    {16.33818238, 17.82438726, 19.51102235, 21.61456053, 24.76903534, 27.58711164, 30.19100912, 33.40866361, 35.71846566, 40.79021671, 42.87921296},
    {17.33790237, 18.86790412, 20.60135411, 22.75954582, 25.98942308, 28.86929943, 31.52637844, 34.80530573, 37.15645146, 42.31239633, 44.43377074},
    {18.3376529, 19.91019886, 21.68912658, 23.90041722, 27.20357103, 30.14352721, 32.85232686, 36.19086913, 38.58225655, 43.82019596, 45.97311956},
    {19.33742923, 20.95136838, 22.77454507, 25.03750564, 28.41198058, 31.41043284, 34.1696069, 37.56623479, 39.99684631, 45.31474662, 47.49845189},
    {20.33722756, 21.99149749, 23.8577889, 26.17109994, 29.61508944, 32.67057334, 35.47887591, 38.93217268, 41.40106477, 46.79703804, 49.0108116},
    {21.33704481, 23.0306609, 24.93901574, 27.30145403, 30.81328234, 33.92443847, 36.78071208, 40.28936044, 42.795655, 48.26794229, 50.51111876},
    {22.33687842, 24.06892481, 26.01836513, 28.42879252, 32.00689968, 35.17246163, 38.07562725, 41.63839812, 44.18127525, 49.72823247, 52.00018929},
    {23.33672631, 25.10634822, 27.09596128, 29.55331524, 33.19624429, 36.4150285, 39.36407703, 42.97982014, 45.55851194, 51.17859778, 53.47875077},
    {24.3365867, 26.14298397, 28.17191525, 30.67520089, 34.38158702, 37.65248413, 40.64646912, 44.3141049, 46.92789016, 52.61965578, 54.94745532},
    {25.33645812, 27.1788796, 29.24632692, 31.79461007, 35.56317127, 38.88513866, 41.9231701, 45.64168267, 48.28988233, 54.05196239, 56.40689012},
    {26.33633931, 28.21407808, 30.31928642, 32.9116877, 36.74121675, 40.11327207, 43.19451097, 46.96294212, 49.6449153, 55.47602021, 57.85758614},
    {27.3362292, 29.24861837, 31.39087545, 34.02656512, 37.91592254, 41.33713815, 44.46079184, 48.27823577, 50.99337627, 56.89228539, 59.30002543},
    {28.33612687, 30.28253595, 32.46116834, 35.1393618, 39.08746977, 42.5569678, 45.7222858, 49.58788447, 52.33561779, 58.30117349, 60.73464717},
    {29.33603152, 31.31586324, 33.53023293, 36.25018678, 40.25602374, 43.77297183, 46.97924224, 50.89218131, 53.67196193, 59.7030643, 62.16185287}
};
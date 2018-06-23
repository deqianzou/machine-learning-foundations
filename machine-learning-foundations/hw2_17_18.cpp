#include<DataReader.h>
#include<algorithm>

int DdecisionStump(int s, double theta, double x)
{
	return s * (x - theta > 0.000001 ? 1 : 0);
}

void getRandData(vector<double> &x, vector<int> &y, int datasize)
{
	int i;
	for (i = 0; i < datasize; i++) {
		int t = 2.0 * rand() / double(RAND_MAX) - 1.0;
		x.push_back(t);
		y.push_back(t - 0 > 0.000001 ? 1 : -1);
	}
}

void getNoise(vector<int> &y)
{
	int n = y.size();
	for (int i = 0; i < n; i++) {
		double randnum = rand() / double(RAND_MAX);
		if (randnum < 0.2)
			y[i] *= -1;
	}
}

double calculateError(vector<double> &x, int s, double theta, vector<int> &y)
{
	int err = 0, n = y.size(), h;
	for (int i = 0; i < n; i++) {
		h = DdecisionStump(s, theta, x[i]);
		if (h != y[i])
		{
			err++;
		}
	}
	return err / double(n);
}

double E_in(vector<double> &x, vector<int> &y, int &bestS, double &bestTheta)
{
	int s, theta;
	int n = x.size();
	double minError = 1.0;
	int i;
	for (i = 0; i < n + 1; i++) {
		s = 1;
		if (i == 0)
			theta = x[0] - 1.0;
		else if (i == n)
			theta = x[n - 1] + 1.0; 
		else
			theta = (x[i - 1] + x[i]) / 2.0; 

		double err = calculateError(x, s, theta, y);
		if (err < minError)
		{
			bestTheta = theta;
			bestS = s;
			minError = err;
		}
	} 
	for (i = 0; i < n + 1; i++)
	{
		s = -1;
		if (i == 0)
			theta = x[0] - 1.0;
		else if (i == n)
			theta = x[n - 1] + 1.0;
		else
			theta = (x[i - 1] + x[i]) / 2.0;

		double errorRate = calculateError(x, s, theta, y);
		if (errorRate < minError) {
			bestS = s;
			bestTheta = theta;
			minError = errorRate;
		}
	}
	return minError;
}

double E_out(int bestS, int bestTheta)
{
	return 0.5 + 0.3 * double(bestS) * (double)(fabs(bestTheta) - 1.0);
}

void hw2_17_18()
{
	cout << "\thw2, 17 and 18:" << endl;
	int i;
	int datasize = 20, cycle=5000;
	double totalE_inRate = 0.0;
	double totalE_outRate = 0.0;

	int* seed = new int[cycle];
	int j;
	for (j = 0; j < cycle; j++)
	{
		seed[j] = rand();
	}

	for (i = 0; i < cycle; i++)
	{
		srand(seed[i]);
		vector<double> x;
		vector<int> y;
		getRandData(x, y, datasize);
		getNoise(y);
		sort(x.begin(), x.end());
		int bestS = 1;
		double bestTheta = 0.0;
		double minError = E_in(x, y, bestS, bestTheta);
		// cout << "min E_in is:" << minError << endl;
		totalE_inRate += minError;
		totalE_outRate += E_out(bestS, bestTheta);
	}
	cout << "average E_in is:" << totalE_inRate / cycle << endl;
	cout << "average E_out is:" << totalE_outRate / cycle << endl;
	cout << "==========" << endl;
}
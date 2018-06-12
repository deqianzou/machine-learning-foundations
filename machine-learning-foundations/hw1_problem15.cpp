#include <PLAbase.h>
string trainfile = "hw1_15_train.dat";

class PLA: PLAbase
{
public:
	PLA(double** x, int* y)
	{
		int n = sizeof(x[0]) / sizeof(double);
		for (int i = 0; i < n; i++)
		{
			w[i] = 0.0;
		}
	}
	~PLA()
	{
		delete x;
		delete y;
		delete w;
	}
	void train();
		

private:
	double** x;
	double* w;
	int* y;
};
void PLA::train()
{
	int m = sizeof(x) / sizeof(double), n = sizeof(x[0]) / sizeof(double);
	int sum, h;
	bool halt = false;
	int update_times = 0; // number of updates before halt.
	while (!halt)
	{
		halt = true;
		for (int i = 0; i < m; i++)
		{
			sum = 0;
			/*----- sign(w^T * x) -----*/
			for (int j = 0; j < n; j++)
			{
				sum += w[j] * x[i][j];
			}
			h = sum <= 0 ? -1 : +1;
			/*=========================*/

			if (h != y[i])
			{
				halt = false;
				update_times++;
				cout << "executing the %d update.\n", update_times;
				/*----- fix w -----*/
				for (int j = 0; j < n; j++)
				{
					w[j] += y[i] * x[i][j];
				}
				/*=================*/
			}
		}
	}
}
int main()
{
	DataReader* dr = new DataReader(trainfile);
	double** x = dr->getX(1);
	int* y = dr->getY();
	PLA* trainer = new PLA(x, y);
	trainer->train();
}
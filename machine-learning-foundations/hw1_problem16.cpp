#include <PLAbase.h>
#include<algorithm>

class PLAWithRandomShuffle : PLAbase
{
public:
	PLAWithRandomShuffle(double** x, int m, int* y, int n)
	{
		row = m;
		col = n;
		w = new double[n];
		for (int i = 0; i < col; i++)
		{
			w[i] = 0.0;
		}
		this->x = x;
		this->y = y;
	}

	~PLAWithRandomShuffle()
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
	int row;
	int col;
};

/*randome shuffle train*/
void PLAWithRandomShuffle::train()
{
	const int times = 2000;
	double sum;
	int h;
	bool halt = false;
	int total_updates = 0;
	vector<int> idx(row);
	for (int i = 0; i < row; i++)
	{
		idx[i] = i;
	}
	int update_times;
	for (int t = 0; t < times; t++)
	{
		halt = false;
		update_times = 0;
		for (int j = 0; j < col; j++)
		{
			w[j] = 0;
		}
		random_shuffle(idx.begin(), idx.end());
		while (!halt)
		{
			halt = true;
			for (auto i: idx)
			{
				sum = 0;
				/*----- sign(w^T * x) -----*/
				for (int j = 0; j < col; j++)
				{
					sum += w[j] * x[i][j];
				}
				h = sum <= 0 ? -1 : +1;
				/*=========================*/

				if (h != y[i])
				{
					halt = false;
					update_times++;
					/*----- fix w -----*/
					for (int j = 0; j < col; j++)
					{
						w[j] += y[i] * x[i][j];
					}
					/*=================*/
				}
			}
		}
		cout << "halted after " << update_times << "updates.\n";
		total_updates += update_times;
	}
	cout << "the average number of updates before the algorithm halts is: " << total_updates*1.0 / times << endl;
}
int main()
{
	string trainfile = "f:\\hw1_15_train.dat";
	double x0 = 1.0;

	DataReader* dr = new DataReader(trainfile);
	double** x = dr->getX(x0);
	cout << sizeof(**x) << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << x[0][i] << " ";
	}
	int* y = dr->getY();
	int m = dr->getM(), n = dr->getN();
	PLAWithRandomShuffle* trainer = new PLAWithRandomShuffle(x, m, y, n);
	trainer->train();

	return 0;
}
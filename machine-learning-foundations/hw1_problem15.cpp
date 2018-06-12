#include <PLAbase.h>

class PLA: PLAbase
{
public:
	PLA(double** x, int m, int* y, int n)
	{
		col = m;
		row = n;
		w = new double[n];
		for (int i = 0; i < row; i++)
		{
			w[i] = 0.0;
		}
		this->x = x;
		this->y = y;
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
	int col;
	int row;
};
void PLA::train()
{
	double sum;
	int h;
	bool halt = false;
	int update_times = 0; // number of updates before halt.
	while (!halt)
	{
		halt = true;
		for (int i = 0; i < col; i++)
		{
			sum = 0;
			/*----- sign(w^T * x) -----*/
			for (int j = 0; j < row; j++)
			{
				sum += w[j] * x[i][j];
			}
			h = sum <= 0 ? -1 : +1;
			/*=========================*/

			if (h != y[i])
			{
				halt = false;
				update_times++;
				cout << "executing the "<< update_times<< "update.\n";
				/*----- fix w -----*/
				for (int j = 0; j < row; j++)
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
	string trainfile = "f:\\hw1_15_train.dat";
	double x0 = 1;

	DataReader* dr = new DataReader(trainfile);
	double** x = dr->getX(x0);
	cout << sizeof(**x) << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << x[0][i] << " ";
	}
	int* y = dr->getY();
	int m = dr->getM(), n = dr->getN();
	PLA* trainer = new PLA(x,m, y, n);
	trainer->train();

	return 0;
}
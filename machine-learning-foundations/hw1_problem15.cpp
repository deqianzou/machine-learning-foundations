#include <PLAbase.h>

class PLA: PLAbase
{
public:
	PLA(double** x, int m, int* y, int n)
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
	int row;
	int col;
};

/*naive train*/
void PLA::train()
{
	double sum;
	int h;
	bool halt = false;
	int update_times = 0; // number of updates before halt.
	while (!halt)
	{
		halt = true;
		for (int i = 0; i < row; i++)
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
				cout << "executing the "<< update_times<< "update.\n";
				/*----- fix w -----*/
				for (int j = 0; j < col; j++)
				{
					w[j] += y[i] * x[i][j];
				}
				/*=================*/
			}
		}
	}
}
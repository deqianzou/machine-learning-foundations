#include <PLAbase.h>

AwesomePLA::AwesomePLA(double** x, int m, int* y, int n)
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

AwesomePLA::~AwesomePLA()
{
	delete []x;
	delete []y;
	delete []w;
}

void AwesomePLA::cleanWeights()
{
	for (int j = 0; j < col; j++)
	{
		w[j] = 0;
	}
}

void AwesomePLA::train(double learingRate, bool randomShuffle, int cycle)
{
	if (!randomShuffle && cycle != 1)
	{
		cycle = 1;
		cout << "Random Shuffle is not on, the train will execute only one cycle." << endl;
	}
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
	for (int t = 0; t < cycle; t++)
	{
		halt = false;
		update_times = 0;
		for (int j = 0; j < col; j++)
		{
			w[j] = 0;
		}
		if (randomShuffle)
			random_shuffle(idx.begin(), idx.end());
		while (!halt)
		{
			halt = true;
			for (auto i : idx)
			{
				sum = 0;
				/*----- sign(w^T * x) -----*/
				for (int j = 0; j < col; j++)
				{
					sum += w[j] * x[i][j];
				}
				h = sum - 0.0 <= 0.000001 ? -1 : +1;
				/*=========================*/

				if (h != y[i])
				{
					halt = false;
					update_times++;
					/*----- fix w -----*/
					for (int j = 0; j < col; j++)
					{
						w[j] += learingRate * y[i] * x[i][j];
					}
					/*=================*/
				}
			}
		}
		if (!randomShuffle)
			cout << "halted after " << update_times << "updates.\n";
		total_updates += update_times;
	}
	if (cycle > 1)
	{
		cout << "the average number of updates before the algorithm halts is: " << total_updates * 1.0 / cycle << endl;
	}
}
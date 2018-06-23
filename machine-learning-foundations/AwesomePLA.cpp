#include <PLAbase.h>



AwesomePLA::AwesomePLA(DataReader* dr)
{
	new(this) AwesomePLA(dr->getX(1), dr->getM(), dr->getY(), dr->getN());
}

AwesomePLA::AwesomePLA(vector<vector<double>> x, int m, vector<double> y, int n)
{
	row = m;
	col = n;
	for (int i = 0; i < col; i++)
	{
		w.push_back(0);
	}
	this->x = x;
	this->y = y;
}

AwesomePLA::~AwesomePLA()
{
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
				h = hypothesis(x[i], w, col);
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

int AwesomePLA::hypothesis(vector<double> xn, vector<double> w, int dimension)
{
	assert(xn.size() == dimension);
	assert(w.size() == dimension);
	double sum = 0.0;
	int h;
	for (int j = 0; j < dimension; j++)
	{
		sum += w[j] * xn[j];
	}
	h = sum - 0.0 > 0.000001 ? 1 : -1;
	return h;
}
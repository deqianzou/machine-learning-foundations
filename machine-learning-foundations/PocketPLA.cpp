#include <PLAbase.h>

PocketPLA::PocketPLA(DataReader* dr)
{
	new(this) PocketPLA(dr->getX(), dr->getM(), dr->getY(), dr->getN());
}

PocketPLA::PocketPLA(double** x, int m, int* y, int n)
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

PocketPLA::~PocketPLA()
{
	delete []x;
	delete []y;
	delete []w;
}


void PocketPLA::pocketTrain(int iteration, bool shuffle, bool greedy)
{
	vector<int> idx(row);
	for (int i = 0; i < row; i++)
	{
		idx[i] = i;
	}
	if (shuffle)
	{
		random_shuffle(idx.begin(), idx.end());
	}
	bool halt = false;
	double* bestW = new double[col];
	double minError = row*1.0;
	double curError;
	for (int j = 0; j < col; j++)
	{
		bestW[j] = w[j];
	}
	minError = getAverageError();
	int iter = 0, i = 0;
	double sum = 0, h = 0;
	for (vector<int>::iterator index = idx.begin(); !halt && index != idx.end(); index = index+1==idx.end()? idx.begin(): index+1)
	{
		halt = true;
		sum = 0;
		i = *index;
		for (int j = 0; j < col; j++)
		{
			sum += w[j] * x[i % row][j];
		}
		h = sum - 0.0 > 0.000001 ? 1 : -1;
		if (h != y[i])
		{
			halt = false;
			for (int j = 0; j < col; j++)
			{
				w[j] += y[i] * x[i][j];
			}
			if (greedy)
			{
				curError = getAverageError();
				if (curError < minError)
				{
					minError = curError;
					for (int j = 0; j < col; j++)
					{
						bestW[j] = w[j];
					}
				}
				if (iter + 1 == iteration)
				{
					setWeights(bestW);
					break;
				}
			}
			iter++;
		}
	}
}

void PocketPLA::setWeights(double * weights)
{
	for (int j = 0; j < col; j++)
	{
		w[j] = weights[j];
	}
}

void PocketPLA::cleanWeights()
{
	for (int j = 0; j < col; j++)
	{
		w[j] = 0.0;
	}
}

void PocketPLA::copyWeights(PocketPLA * p)
{
	setWeights(p->getWeights());
}

double PocketPLA::getAverageError()
{
	int e = 0;
	double sum = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sum += w[j] * x[i][j];
		}
		e += y[i] == (sum > 0 ? 1 : -1) ? 1 : 0;
	}
	return e*1.0 / row;
}

double* PocketPLA::getWeights()
{
	return w;
}
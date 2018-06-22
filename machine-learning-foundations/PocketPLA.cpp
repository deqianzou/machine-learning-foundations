#include <PLAbase.h>

PocketPLA::PocketPLA(DataReader* dr)
{
	new(this) PocketPLA(dr->getX(1), dr->getM(), dr->getY(), dr->getN());
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
	double* bestW = new double[col];
	double minError = row*1.0;
	double curError;
	for (int j = 0; j < col; j++)
	{
		bestW[j] = 0.0;
	}
	minError = getAverageError();
	int iter = 0, i = 0, h;
	double sum = 0.0;
	for (vector<int>::iterator index = idx.begin(); index != idx.end(); index = index+1==idx.end()? idx.begin(): index+1)
	{
		sum = 0.0;
		i = *index;
		for (int j = 0; j < col; j++)
		{
			sum += w[j] * x[i][j];
		}
		h = sum - 0.0 > 0.000001 ? 1 : -1;
		if (h != y[i])
		{ 
			iter++;
			for (int j = 0; j < col; j++)
			{
				w[j] += y[i] * x[i][j];
			}
			if (greedy)
			{
				curError = getAverageError();
				if (curError - minError < 0.0)
				{
					minError = curError;
					for (int j = 0; j < col; j++)
					{
						bestW[j] = w[j];
					}
				}
			}
		}
		if (iter == iteration)  break;
		// if (minError < 0.01)  break;
	}
	if (greedy)
	{
		setWeights(bestW);
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
	int h;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sum += w[j] * x[i][j];
		}
		h = sum - 0.0 > 0.000001 ? 1 : -1;
		if (h!=y[i])
		{
			e++;
		}
	}
	return e*1.0 / row;
}

double* PocketPLA::getWeights()
{
	return w;
}
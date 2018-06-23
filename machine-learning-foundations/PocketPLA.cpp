#include <PLAbase.h>

PocketPLA::PocketPLA(DataReader* dr)
{
	new(this) PocketPLA(dr->getX(1), dr->getM(), dr->getY(), dr->getN());
}

PocketPLA::PocketPLA(vector<vector<double>> x, int m, vector<double> y, int n)
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

PocketPLA::~PocketPLA()
{
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
	vector<double> bestW(col, 0);
	double minError = row*1.0;
	double curError;
	minError = getAverageError();
	int iter = 0, i = 0, h;
	for (vector<int>::iterator index = idx.begin(); index != idx.end(); index = index+1==idx.end()? idx.begin(): index+1)
	{
		i = *index;
		h = hypothesis(x[i], w, col);
		if (h != (int)y[i])
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

void PocketPLA::setWeights(vector<double> weights)
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
	int h;
	for (int i = 0; i < row; i++)
	{
		h = hypothesis(x[i], w, col);
		if (h!=y[i])
		{
			e++;
		}
	}
	return e*1.0 / row;
}

vector<double> PocketPLA::getWeights()
{
	return w;
}

int PocketPLA::hypothesis(vector<double> xn, vector<double> w, int dimension)
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
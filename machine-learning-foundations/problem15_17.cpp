#include <PLAbase.h>

class AwesomePLA : PLAbase
{
public:
	AwesomePLA(double** x, int m, int* y, int n)
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

	~AwesomePLA()
	{
		delete x;
		delete y;
		delete w;
	}

	void train(double learingRate, bool randomShuffle, int cycle);


private:
	double** x;
	double* w;
	int* y;
	int row;
	int col;
	
};

void AwesomePLA::train(double learingRate = 1, bool randomShuffle = false, int cycle = 1)
{
	if (!randomShuffle && cycle!=1)
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
		if(randomShuffle)
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
				h = sum <= 0 ? -1 : +1;
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
		if(!randomShuffle)
			cout << "halted after " << update_times << "updates.\n";
		total_updates += update_times;
	}
	if (cycle > 1)
	{
		cout << "the average number of updates before the algorithm halts is: " << total_updates * 1.0 / cycle << endl;
	}
}

int main(int argc, char * argv[])
{
	string trainfile = argv[1];
	double x0 = 1.0;
	DataReader* dr = new DataReader(trainfile);
	double** x = dr->getX(x0);
	int* y = dr->getY();
	int m = dr->getM(), n = dr->getN();
	double learningRate = 1;
	bool randomShuffle = false;
	int cycle = 1;
	AwesomePLA* trainer = new AwesomePLA(x, m, y, n);

	cout << "problem 15: start training..." << endl;
	trainer->train(learningRate, randomShuffle, cycle);
	cout << "problem 15: training complete." << endl;

	randomShuffle = true;
	cycle = 2000;
	cout << "problem 16: start training..." << endl;
	trainer->train(learningRate, randomShuffle, cycle);
	cout << "problem 16: training complete." << endl;

	learningRate = 0.5;
	cout << "problem 17: start training..." << endl;
	trainer->train(learningRate, randomShuffle, cycle);
	cout << "problem 17: training complete." << endl;
	return 0;
}

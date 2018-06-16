#include <PLAbase.h>

void PLAtrain(string trainfile)
{
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
	trainer->cleanWeights();
	cout << "problem 16: start training..." << endl;
	trainer->train(learningRate, randomShuffle, cycle);
	cout << "problem 16: training complete." << endl;

	learningRate = 0.5;
	trainer->cleanWeights();
	cout << "problem 17: start training..." << endl;
	trainer->train(learningRate, randomShuffle, cycle);
	cout << "problem 17: training complete." << endl;
	dr->~DataReader();
	trainer->~AwesomePLA();
}

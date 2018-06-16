#include <PLAbase.h>
void PocketPLAtrain(string trainFile, string testFile)
{
	int iteration = 50;
	int cycle = 2000;
	DataReader* drTrain = new DataReader(trainFile);
	DataReader* drTest = new DataReader(testFile);
	PocketPLA* trainer = new PocketPLA(drTrain);
	PocketPLA* tester = new PocketPLA(drTest);
	double averageError = 0.0;

	cout << "problem 18: start training..." << endl;
	for (int i = 0; i < cycle; i++)
	{
		trainer->cleanWeights();
		trainer->pocketTrain(iteration, true, true);
		tester->copyWeights(trainer);
		averageError += tester->getAverageError();
	}
	cout << "problem 18: average test error is " << averageError / cycle << endl;
	cout << "problem 18: mission complete." << endl;

	cout << "problem 19: start training..." << endl;
	averageError = 0.0;
	for (int i = 0; i < cycle; i++)
	{
		trainer->cleanWeights();
		trainer->pocketTrain(iteration, true, false);
		tester->copyWeights(trainer);
		averageError += tester->getAverageError();
	}
	cout << "problem 19: average test error is " << averageError / cycle << endl;
	cout << "problem 19: mission complete." << endl;

	cout << "problem 20: start training..." << endl;
	averageError = 0.0;
	iteration = 100;
	for (int i = 0; i < cycle; i++)
	{
		trainer->cleanWeights();
		trainer->pocketTrain(iteration, true, true);
		tester->copyWeights(trainer);
		averageError += tester->getAverageError();
	}
	cout << "problem 20: average test error is " << averageError / cycle << endl;
	cout << "problem 20: mission complete." << endl;
	drTrain->~DataReader();
	drTest->~DataReader();
	trainer->~PocketPLA();
	tester->~PocketPLA();
}
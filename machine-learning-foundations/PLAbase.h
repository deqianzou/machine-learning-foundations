#pragma once
#ifndef _PLABASE_H
#define _PLABASE_H

#include<DataReader.h>
#include<algorithm>
// using namespace std;
class PLAbase
{
public:
	PLAbase();
	~PLAbase();
	virtual void train(double learingRate, bool randomShuffle, int cycle);
	virtual void pocketTrain(int iteration);
	virtual void cleanWeights();
private:

};

class AwesomePLA : PLAbase
{
public:
	AwesomePLA(double** x, int m, int* y, int n);

	~AwesomePLA();

	void train(double learingRate, bool randomShuffle, int cycle);
	void cleanWeights();
private:
	double** x;
	double* w;
	int* y;
	int row;
	int col;

};

class PocketPLA : PLAbase
{
public:
	PocketPLA(DataReader* dr);

	PocketPLA(double** x, int m, int* y, int n);

	~PocketPLA();

	void pocketTrain(int iteration, bool shuffle, bool greedy);

	void setWeights(double* weights);

	void cleanWeights();

	void copyWeights(PocketPLA* p);

	double getAverageError();

	double* getWeights();

private:
	double** x;
	double* w;
	int* y;
	int row;
	int col;
};
#endif
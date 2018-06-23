#pragma once
#ifndef _PLABASE_H
#define _PLABASE_H

#include<DataReader.h>
#include<algorithm>
#include <assert.h>

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
	AwesomePLA(DataReader* dr);

	AwesomePLA(vector<vector<double>> x, int m, vector<double> y, int n);

	~AwesomePLA();

	void train(double learingRate, bool randomShuffle, int cycle);

	void cleanWeights();

private:
	vector<vector<double>> x;
	vector<double> w;
	vector<double> y;
	int row;
	int col;
	int hypothesis(vector<double> xn, vector<double> w, int dimension);
};

class PocketPLA : PLAbase
{
public:
	PocketPLA(DataReader* dr);

	PocketPLA(vector<vector<double>> x, int m, vector<double> y, int n);

	~PocketPLA();

	void pocketTrain(int iteration, bool shuffle, bool greedy);

	void setWeights(vector<double> weights);

	void cleanWeights();

	void copyWeights(PocketPLA* p);

	double getAverageError();

	vector<double> getWeights();

private:
	vector<vector<double>> x;
	vector<double> w;
	vector<double> y;
	int row;
	int col;

	int hypothesis(vector<double> xn, vector<double> w, int dimension);
};
#endif
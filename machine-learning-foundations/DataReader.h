#pragma once
#ifndef _DATAREADER_H
#define _DATAREADER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<sstream>
using namespace std;

class DataReader
{
public:
	DataReader(string file);

	~DataReader();

	double** getX(int xzero);

	/*
	*  with default x0=0
	*/
	double** getX();
	
	int* getY();

	int getM();

	int getN();

private:
	std::string filename;
	vector<vector<double>> data;
	std::ifstream in;
	int m;
	int n;
};
#endif
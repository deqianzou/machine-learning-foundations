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

	vector<vector<double>> getX(double xzero);

	/*
	*  with default x0=1
	*/
	vector<vector<double>> getX();
	
	vector<double> getY();

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
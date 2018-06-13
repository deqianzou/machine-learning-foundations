#pragma once
#ifndef _PLABASE_H
#define _PLABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<sstream>
#include<algorithm>
using namespace std;
class PLAbase
{
public:
	PLAbase();
	~PLAbase();
	virtual void train(double learingRate=1, bool randomShuffle=false, int cycle=1) = 0;
private:

};

PLAbase::PLAbase()
{
}

PLAbase::~PLAbase()
{
}

class DataReader
{
public:
	DataReader(string file)
	{
		filename = file;
		in.open(filename);
		if (!in)
		{
			cerr << "error: cannot open file "<<filename<<".\n";
		}

		int i = 0, j = 0;
		string str;
		string val;
		vector<double> line;
		while (getline(in, str))
		{
			j = 0;
			stringstream input(str);
			while (input >> val)
			{
				line.push_back(atof(val.c_str()));
				j++;
			}
			data.push_back(line);
			line.clear();
			i++;
		}
		m = i;
		n = j;
	}

	~DataReader()
	{
		in.close();
		delete &data;
		delete &filename;
		delete &m;
		delete &n;
		delete &in;
	}

	double** getX(int xzero)
	{
		double** x = new double*[m];
		for (int i = 0; i < m; i++)
		{
			x[i] = new double[n];
			x[i][0] = xzero;
			for (int j = 0; j < n - 1; j++)
			{
				x[i][j+1] = data[i][j];
			}
		}

		return x;
	}

	/*
	*  with default x0=0
	*/
	double** getX()
	{
		return getX(0);
	}

	int* getY()
	{
		int* y = new int[m];
		for (int i = 0; i < m; i++)
			y[i] = data[i][n - 1];
		return y;
	}

	int getM() { return m; }

	int getN() { return n; }

private:
	std::string filename;
	vector<vector<double>> data;
	std::ifstream in;
	int m;
	int n;
};
#endif
#pragma once
#ifndef _PLABASE_H
#define _PLABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<sstream>
using namespace std;
class PLAbase
{
public:
	PLAbase();
	~PLAbase();
	virtual void train();
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
			cerr << "error: cannot open file %s.\n", filename;
		}

		int i = 0, j = 0;
		string str;
		string val;
		while (getline(in, str))
		{
			stringstream input(str);
			while (input >> val)
			{
				data[i][j] = atof(val.c_str());
				j++;
			}
			i++;
			j = 0;
		}
		m = i;
		j = j;
	}

	~DataReader()
	{
		in.close();
		delete data;
		delete &filename;
		delete &m;
		delete &n;
	}

	double** getX(int xzero)
	{
		double** x;
		for (int i = 0; i < m; i++)
		{
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
		int* y;
		for (int i = 0; i < m; i++)
			y[i] = data[i][n - 1];
	}

private:
	std::string filename;
	double** data;
	std::ifstream in;
	int m;
	int n;
};
#endif
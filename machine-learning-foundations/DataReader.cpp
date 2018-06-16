#include <DataReader.h>

DataReader::DataReader(string file)
{
	filename = file;
	in.open(filename);
	if (!in)
	{
		cerr << "error: cannot open file " << filename << ".\n";
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

DataReader::~DataReader()
{
	in.close();
	data.~vector();
	in.~ifstream();
	filename.~string();
}

double** DataReader::getX(int xzero)
{
	double** x = new double*[m];
	for (int i = 0; i < m; i++)
	{
		x[i] = new double[n];
		x[i][0] = xzero;
		for (int j = 0; j < n - 1; j++)
		{
			x[i][j + 1] = data[i][j];
		}
	}

	return x;
}

double** DataReader::getX()
{
	return getX(0);
}

int* DataReader::getY()
{
	int* y = new int[m];
	for (int i = 0; i < m; i++)
		y[i] = data[i][n - 1];
	return y;
}

int DataReader::getM() { return m; }

int DataReader::getN() { return n; }
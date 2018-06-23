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
}

vector<vector<double>> DataReader::getX(double xzero)
{
	vector<vector<double>> x;
	for (int i = 0; i < m; i++)
	{
		vector<double> tmp({xzero});
		for (int j = 0; j < n - 1; j++)
		{
			tmp.push_back(data[i][j]);
		}
		x.push_back(tmp);
	}
	return x;
}

vector<vector<double>> DataReader::getX()
{
	return getX(1);
}

vector<double> DataReader::getY()
{
	vector<double> y;
	for (int i = 0; i < m; i++)
		y.push_back(data[i][n - 1]);
	return y;
}

int DataReader::getM() { return m; }

int DataReader::getN() { return n; }
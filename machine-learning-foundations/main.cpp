#include <PLAbase.h>
void PLAtrain(string trainfile);
void PocketPLAtrain(string trainFile, string testFile);
int main()
{
	PLAtrain("f:\\hw1_15_train.dat");
	PocketPLAtrain("f:\\hw1_18_train.dat", "f:\\hw1_18_test.dat");

	return 0;
} 
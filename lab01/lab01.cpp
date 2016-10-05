#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;
int main(int argc, char const *argv[])
{
	int cols, rows;
	cols = rows = 20000;
	vector<int> p_mat(cols*rows);

	for_each(begin(p_mat), end(p_mat),[](auto& el){
			el = rand() % 200 - 100;
	});

	int c_odds = count_if(begin(p_mat), end(p_mat), [&c_odds](auto el){
		return (el % 2 == 0);
	});

	int min = INT_MAX;
	int max = INT_MIN;

	for (int i = 0; i < cols*rows; ++i)
	{
		if(min > p_mat[i])
			min = p_mat[i];
		if(max > p_mat[i])
			max = p_mat[i];
	}

	// int c_filt = 0;
	//
	// for (int i = 0; i < cols*rows; ++i)
	// {
	// 	if(p_mat[i] < 45 || p_mat[i] > -45)
	// 		c_filt++;
	// }
	//
	// delete[] p_mat;

	return 0;
}

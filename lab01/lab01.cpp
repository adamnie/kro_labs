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

	cout << "Odd numbers count: " << c_odds << endl;

	auto result_minmax = minmax_element(begin(p_mat), end(p_mat));

	cout << "Min: " << *result_minmax.first << "\nMax: " << *result_minmax.second << endl;

	int lower_limit, higher_limit;

	lower_limit = -45; higher_limit = 45;

	auto filter = [lower_limit, higher_limit](int value){
		return value < lower_limit || value > higher_limit;
	};

	p_mat.erase(remove_if(begin(p_mat), end(p_mat), filter), end(p_mat));

	int c_filtered = p_mat.size();

	cout << "No. of elements after filtering: " << c_filtered << endl;

	return 0;
}

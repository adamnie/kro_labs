#include <iostream>
using namespace std;

void f(void* p){
	cout << "ptr version\n";
}
// void f(int p){
// 	cout << "a;sldjkfhas;dfha" << endl;
// }

int main(int argc, char const *argv[])
{
	f(0);
	f(false);
	f(NULL);
	f(nullptr);
	return 0;
}

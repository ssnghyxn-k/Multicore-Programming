#include <iostream>
#include <thread>

using namespace std;

int sum;
int main()
{
	for (auto i = 0; i < 50000000; ++i) 
		sum = sum + 2;
	cout << "Sum = " << sum << endl;
}

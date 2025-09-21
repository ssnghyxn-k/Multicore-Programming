#include <iostream>
#include <thread>

using namespace std;

int sum;

void worker()
{
	for(auto i = 0; i < 50000000; ++i) 
		sum = sum + 2;
}

int main()
{
	thread t1(worker);
	thread t2(worker);
	t1.join();
	t2.join();

	cout << "Sum = " << sum << endl;
}
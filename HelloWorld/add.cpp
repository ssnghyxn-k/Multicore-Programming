#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int sum;
mutex myl;

void worker()
{
	for (auto i = 0; i < 25000000; ++i) {
		myl.lock();
		sum += 2;
		myl.unlock();
	}
}

int main()
{
	thread t1(worker);
	thread t2(worker);
	t1.join();
	t2.join();

	cout << "Sum = " << sum << endl;
}
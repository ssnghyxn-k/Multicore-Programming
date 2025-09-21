#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace chrono;

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
	auto start_t = high_resolution_clock::now();
	thread t1(worker);
	thread t2(worker);
	t1.join();
	t2.join();
	auto end_t = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end_t - start_t);

	cout << "Duration = " << duration.count() << " ms" << endl;
	cout << "Sum = " << sum << endl;
}
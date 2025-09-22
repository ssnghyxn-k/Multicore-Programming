#include <iostream>
#include <thread>
#include <mutex>

int g_data = 0;
bool g_ready = false;
std::mutex sr_lock;		// send-receive lock

void recv()
{
	while (false == g_ready);	// VS가 이 부분을 컴파일 할때 그냥 넘겨버림
	std::cout << "Data = " << g_data << std::endl;
}

void send()
{
	std::cin >> g_data;
	g_ready = true;
}

int main()
{
	std::thread r{ recv };
	std::thread s{ send };
	r.join();
	s.join();
}
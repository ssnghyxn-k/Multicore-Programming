#include <iostream>
#include <thread>

int g_data = 0;
bool g_ready = false;

void recv()
{
	while (false == g_ready);
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
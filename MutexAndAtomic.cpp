// MutexAndAtomic.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

int simpleCounter = 0;
int mutexCounter = 0;
std::atomic<int> atomicCounter(0);
std::mutex m;

void SimpleIncrementation() {
	for (int i = 0; i < 100000000; i++) {
		simpleCounter++;
	}
}

void MutexIncrementation() {
	for (int i = 0; i < 100000000; i++) {
		std::lock_guard<std::mutex> lock(m);
		mutexCounter++;
	}
}

void AtomicIncrementation() {
	for (int i = 0; i < 100000000; i++) {
		atomicCounter++;
	}
}

int main()
{
	auto start1 = chrono::high_resolution_clock::now();
	std::thread t1(SimpleIncrementation);
	std::thread t2(SimpleIncrementation);
	t1.join();
	t2.join();
	auto end1 = chrono::high_resolution_clock::now();
	std::cout << "Simple Incrementation result: " << simpleCounter << std::endl;
	double SimpIncTime = chrono::duration_cast<chrono::microseconds>(end1 - start1).count() / 1e6;
	std::cout << "Simple Incrementation time: " << SimpIncTime << std::endl;

	auto start2 = chrono::high_resolution_clock::now();
	std::thread t3(MutexIncrementation);
	std::thread t4(MutexIncrementation);
	t3.join();
	t4.join();
	auto end2 = chrono::high_resolution_clock::now();
	std::cout << "Mutex Incrementation result: " << mutexCounter << std::endl;
	double MutexIncTime = chrono::duration_cast<chrono::microseconds>(end2 - start2).count() / 1e6;
	std::cout << "Mutex Incrementation time: " << MutexIncTime << std::endl;

	auto start3 = chrono::high_resolution_clock::now();
	std::thread t5(AtomicIncrementation);
	std::thread t6(AtomicIncrementation);
	t5.join();
	t6.join();
	auto end3 = chrono::high_resolution_clock::now();
	std::cout << "Atomic Incrementation result: " << atomicCounter << std::endl;
	double AtomicIncTime = chrono::duration_cast<chrono::microseconds>(end3 - start3).count() / 1e6;
	std::cout << "Atomic Incrementation time: " << AtomicIncTime << std::endl;
	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

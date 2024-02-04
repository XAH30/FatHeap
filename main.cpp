#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<chrono>
#include<algorithm>


using namespace std;
using namespace std::chrono;


const int INF = 1e9 + 100;//Максимальное число


#include "Node.cpp"
#include "RootCounterNode.cpp"
#include "FatHeap.cpp"


int main() {
	FatHeap heap;
	auto start_time_insert = high_resolution_clock::now();
	heap.insert(15);
	heap.insert(13);
	heap.insert(5);
	auto end_time_insert = high_resolution_clock::now();
	auto execution_time_insert = duration_cast<nanoseconds>(end_time_insert - start_time_insert);
	cout << "Time insert:" << execution_time_insert.count() << " nanoseconds";

	auto start_time_delete = high_resolution_clock::now();
	heap.deleteMin();
	auto end_time_delete = high_resolution_clock::now();
	auto execution_time_delete = duration_cast<nanoseconds>(end_time_delete - start_time_delete);
	cout << "\nTime delete:" << execution_time_delete.count() << " nanoseconds";
	return 0;
}
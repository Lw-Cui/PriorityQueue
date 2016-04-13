#include "Queue.hpp"
#include "gtest/gtest.h"
#include <array>
#include <iostream>
#include <set>
#include <thread>
using namespace std;
using namespace que;
const int MAX = 100000;

template<typename T>
void insert(PriorityQueue<T>& p, const vector<T> set) {
	for (const auto &d: set)
		p.push(d);
}

TEST(BasicTest, InsertTest) {
	vector<int> dataset;
	for (int i = MAX; i > 0; i--)
		dataset.push_back(i);
	PriorityQueue<int> queue;
	insert(queue, dataset);

	vector<int> res;
	for (const auto &d: queue) res.push_back(d);
	sort(res.begin(), res.end(), [](auto a, auto b) {return a > b;});
	ASSERT_EQ(res, dataset);
}

TEST(BasicTest, delMinTest) {
	vector<int> dataset;
	for (int i = MAX; i > 0; i--)
		dataset.push_back(i);
	PriorityQueue<int> queue;
	insert(queue, dataset);

	vector<int> res;
	while (!queue.empty()) { res.push_back(queue.top()); queue.pop(); }
	sort(res.begin(), res.end(), [](auto a, auto b) {return a > b;});
	ASSERT_EQ(res, dataset);
}

class thread_guard {
public:
	explicit thread_guard(thread& t):mythread(t){}
	~thread_guard() {if (mythread.joinable()) mythread.join();}
	thread_guard(const thread_guard &)=delete;
	thread_guard& operator=(const thread &)=delete;
private:
	std::thread& mythread;
};

TEST(ThreadTest, InsertTest) {
	vector<int> dataset;
	for (int i = MAX; i > 0; i--)
		dataset.push_back(i);
	PriorityQueue<int> queue;
	thread t1(insert<int>, ref(queue), dataset);
	thread t2(insert<int>, ref(queue), dataset);
	t1.join();
	t2.join();
	//thread_guard guard1(t1);
	//thread_guard guard2(t2);

	vector<int> res;
	for (const auto &d: queue) res.push_back(d);
	sort(res.begin(), res.end(), [](auto a, auto b) {return a > b;});
	for (size_t i = 0; i < dataset.size(); i++) {
		ASSERT_EQ(dataset[i], res[i * 2]) << "i = " << i << endl;
		ASSERT_EQ(dataset[i], res[i * 2 + 1]);
	}
}

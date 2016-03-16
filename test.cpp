#include "Queue.h"
#include "gtest/gtest.h"
#include <iostream>
#include <set>
#include <thread>
using namespace std;
using namespace queue;
const int MAX = 100000;
TEST(BasicTest, InsertTest) {
	PriorityQueue<int> queue;
	for (int i = MAX; i > 0; i--)
		queue.insert(i);
	set<int> container;
	for (auto p: queue)
		container.insert(p);
	int cnt = 1;
	for (auto value: container)
		ASSERT_EQ(value, cnt++);
}

TEST(BasicTest, delMinTest) {
	PriorityQueue<int> queue;
	for (int i = MAX; i > 0; i--)
		queue.insert(i);
	for (int i = 1; i <= MAX; i++)
		ASSERT_EQ(queue.delMin(), i);
}

TEST(ThreadTest, InsertTest) {
}

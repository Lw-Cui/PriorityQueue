#include <atomic>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
template<typename T>
class MobileAtomic
{
public:
	MobileAtomic(){}
	MobileAtomic(const T& data): atom(data) {}
	MobileAtomic(const MobileAtomic& mobile): atom(mobile.atom.load()) {}
	inline MobileAtomic& operator=(const MobileAtomic &mobile) {
		atom.store(mobile.atom.load());
		return *this;
	}
	inline operator T() const {
		return atom.load();
	}
private:
	atomic<T> atom;
};

template<typename T>
class PriorityQueue {
public:
	typedef typename vector<MobileAtomic<T>>::const_iterator const_iterator;
	PriorityQueue():array(1) {}
	const_iterator begin() const {return ++array.begin();}
	const_iterator end() const {return array.end();}
	inline void insert(const T& data) {
		array.push_back(data);
		up(array.size() - 1);
	}
	inline T delMin() {
		T data = array[1];
		array[1] = array.back();
		array.pop_back();
		down(1);
		return data;
	}
private:
	void up(size_t index) {
		T data(array[index]);
		// index indicates the current position
		while(index != 1) {
			if (data < array[index / 2])
				array[index] = array[index / 2];
			index /= 2;
		}
		array[index] = data;
	}
	void down(size_t index) {
		T data(array[index]);
		// index means the possible dist
		while (index * 2 < array.size()) {
			index *= 2;
			if (index + 1 < array.size() && array[index + 1] < array[index])
				index++;
			if (array[index] < data)
				array[index / 2] = array[index];
			else
				break;
		}
		if (array[index] >= data)
			array[index / 2] = data;
		else
			array[index] = data;
	}
	vector<MobileAtomic<T>> array;
};

int main() {
	PriorityQueue<int> queue;
	for (int i = 10; i > 0; i--)
		queue.insert(i);
	for (auto p = queue.begin(); p != queue.end(); p++)
		cout << *p << endl;
	cout << endl;
	for (int i = 3; i > 0; i--)
		queue.delMin();
	for (auto p = queue.begin(); p != queue.end(); p++)
		cout << *p << endl;
	return 0;
}

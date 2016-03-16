#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <atomic>
#include <mutex>
#include <algorithm>
#include <vector>
#include <iostream>
namespace queue {
	template<typename T>
	class MobileAtomic
	{
		template<typename T> friend class PriorityQueue;
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
		std::atomic<T> atom;
	};

	template<typename T>
	class PriorityQueue {
	public:
		typedef typename std::vector<MobileAtomic<T>>::const_iterator const_iterator;
		PriorityQueue():array(1) {}
		inline const_iterator begin() const {return ++array.begin();}
		inline const_iterator end() const {return array.end();}
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
		std::vector<MobileAtomic<T>> array;
	};
}

#endif
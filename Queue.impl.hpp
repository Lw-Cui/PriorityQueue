#ifndef _QUEUE_IMPL_H_
#define _QUEUE_IMPL_H_
namespace que {
	template<typename T, typename Con, typename Cmp>
	void PriorityQueue<T, Con, Cmp>::down(size_t index) {
		T data(array[index]);
		// index means the possible dist
		while (index * 2 < array.size()) {
			index *= 2;
			if (index + 1 < array.size() && !compare(array[index + 1], array[index]))
				index++;
			if (!compare(array[index], data))
				array[index / 2] = array[index];
			else
				break;
		}
		if (compare(array[index], data))
			array[index / 2] = data;
		else
			array[index] = data;
	}

	template<typename T, typename Con, typename Cmp>
	void PriorityQueue<T, Con, Cmp>::up(size_t index) {
		T data(array[index]);
		// index indicates the current position
		while(index != 1) {
			if (!compare(data, array[index / 2]))
				array[index] = array[index / 2];
			else
				break;
			index /= 2;
		}
		array[index] = data;
	}
}
#endif
#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <cstdlib>
#include <cstring>
#include <mutex>
#include <condition_variable>

namespace pr {

// MT safe version of the Queue, non blocking.
template <typename T>
class Queue {
	T ** tab;
	const size_t allocsize;
	size_t begin;
	size_t sz;
	bool isBlocking;

	mutable std::mutex m;
	std::condition_variable cv_cons, cv_prod;

	// fonctions private, sans protection mutex
	bool empty() const {
		return sz == 0;
	}
	bool full() const {
		return sz == allocsize;
	}
public:
	Queue(size_t size) :allocsize(size), begin(0), sz(0) {
		tab = new T*[size];
		std::memset(tab, 0, size * sizeof(T*));
	}
	size_t size() const {
		std::unique_lock<std::mutex> lg(m);
		return sz;
	}

	T* pop() {
		std::unique_lock<std::mutex> lg(m);
		while (empty() && isBlocking) {
			cv_cons.wait(lg);
		}
		auto ret = tab[begin];
		tab[begin] = nullptr;
		sz--;
		begin = (begin + 1) % allocsize;
		cv_prod.notify_one();
		return ret;
	}

	bool push(T* elt) {
		std::unique_lock<std::mutex> lg(m);
		while (full() && isBlocking) {
			cv_prod.wait(lg);
		}
		tab[(begin + sz) % allocsize] = elt;
		sz++;
		cv_cons.notify_one();
		return true;
	}
	~Queue() {
		// ?? lock a priori inutile, ne pas detruire si on travaille encore avec
		for (size_t i = 0; i < sz; i++) {
			auto ind = (begin + i) % allocsize;
			delete tab[ind];
		}
		delete[] tab;
	}

	void setBlocking(bool isBlocking){
		std::unique_lock<std::mutex>lg(m);
		this->isBlocking = isBlocking;
		cv_cons.notify_all();
		cv_prod.notify_all();
	}
};

}

#endif /* SRC_QUEUE_H_ */

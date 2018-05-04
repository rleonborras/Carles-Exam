#include "PriorityQueue.h"
#include "UnitTest.h"
#include <vector>
#include <iostream>
#include <cstdlib>

class Event
{
public:

	Event() : id(0) { }
	Event(int evId) : id(evId) { }

	int id; // Event id
};

int main()
{

	// 1 element test
	{
		PriorityQueue<Event> queue;
		queue.enqueue(Event(10), 10);
		const bool ok1 = queue.size() == 1;
		const bool ok2 = queue.front().id == 10;
		TEST("After enqueuing 1 element - the number of elements should be 1", ok1);
		TEST("After enqueuing 1 element - order of the queue", ok2);
	}

	// 2 element test
	{
		PriorityQueue<Event> queue;
		queue.enqueue(Event(10), 20);
		queue.enqueue(Event(9), 30);
		const bool ok1 = queue.size() == 2;
		bool ok2 = true;
		ok2 = ok2 && queue.front().id == 9; queue.dequeue();
		ok2 = ok2 && queue.front().id == 10; queue.dequeue();
		TEST("After enqueuing 2 elements - the number of elements should be 2", ok1);
		TEST("After enqueuing 2 elements - order of the queue", ok2);
	}

	// 17 element test
	{
		std::vector<int> identifiers = { 49, 5, 1, 100, 40, 32, 56, 88, 23, 3, 46, 76, 99, 18, 25, 63, 1000 };
		std::vector<int> sidentifiers = { 1000, 100, 99, 88, 76, 63, 56, 49, 46, 40, 32, 25, 23, 18, 5, 3, 1 };
		PriorityQueue<Event> queue;

		for (auto i = 0; i < identifiers.size(); ++i) {
			const int eventId = identifiers[i];
			const int priority = identifiers[i];
			queue.enqueue(Event(eventId), priority);
		}

		int prev = 9999;
		const bool ok1 = queue.size() == 17;
		bool ok2 = true;
		for (int i = 0; !queue.empty(); ++i)
		{
			const Event curr = queue.front();
			//std::cout << curr.id << std::endl;
			ok2 = ok2 && curr.id == sidentifiers[i];
			prev = curr.id;
			queue.dequeue();
		}

		TEST("After enqueuing 17 elements - the number of elements should be 17", ok1);
		TEST("After enqueuing 17 elements - order of the queue", ok2);
	}

	PRINT_TEST_REPORT();

	system("pause");
	return 0;
}
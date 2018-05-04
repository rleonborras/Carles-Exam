/*----------------- CARLES HOMS PUCHAL --------------------*/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <cassert>

template<class T>
class PriorityQueue
{
public:

	PriorityQueue() :
		_front(nullptr),
		_numElems(0)
	{ }

	~PriorityQueue()
	{
		clear();
	}

	unsigned int size() const
	{
		return _numElems;
	}

	bool empty() const
	{
		return _numElems == 0;
	}

	T &front()
	{
		assert(_numElems > 0 && "Cannot obtain the front of an empty queue");
		return _front->value;
	}

	const T &front() const
	{
		assert(_numElems > 0 && "Cannot obtain the front of an empty queue");
		return _front->value;
	}

	void enqueue(const T &value, int priority)
	{
		if (_numElems == 0)
		{
			_front = new Node;
			_front->value = value;
			_front->next = nullptr;
			_front->priority = priority;
		}
		
		else
		{
			Node* node = new Node;
			node->value = value;
			node->priority = priority;

			if (priority < _front->priority)
			{
				Node* tempPtr = _front;

				while (tempPtr->next != nullptr && priority < tempPtr->next->priority)
					tempPtr = tempPtr->next;

				if (tempPtr->next == nullptr)
				{
					tempPtr->next = node;
					node->next = nullptr;
				}

				else
				{
					node->next = tempPtr->next;
					tempPtr->next = node;
				}
			}

			else
			{
				node->next = _front;
				_front = node;
			}
		}

		_numElems++;
	}

	void dequeue()
	{
		assert(_numElems > 0 && "Cannot dequeue from an empty queue");

		Node *newFront = _front->next;
		delete _front;
		_front = newFront;
		_numElems--;
	}

	void clear()
	{
		while (!empty())
		{
			dequeue();
		}
	}

private:

	struct Node
	{
		T value;
		int priority;
		Node *next;
	};

	Node *_front;
	unsigned int _numElems;
};

#endif // PRIORITY_QUEUE_H

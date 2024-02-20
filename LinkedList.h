#pragma once

#include <memory>

template <typename T> class LinkedListNode
{
public:
	LinkedListNode* next = NULL;
	std::shared_ptr<T> data = NULL;
private:

};

#pragma once

template <typename Type, typename TContainer>
class Queue
{
private:
	TContainer T;

public:
	void Push(const Type& value) { T.PushBack(value); }

	void Pop() { T.PopFront(); }

	Type& Front() { return T.Front(); }

	Type& Back() { return T.Back(); }

	size_t Size() const { return T.Size(); }

	bool IsEmpti() const { return T.Empti(); }

	void Swap(Queue& other) { T.Swap(other); }

	TContainer GetContainer() { return TContainer; }
};
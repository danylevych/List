#pragma once
#include <utility>
#include <initializer_list>

template <typename T>
class List
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node* previous;
	};

	Node* head;
	Node* tail;
	size_t size;

	void Copy(const List& other);

public:
	// --------- Constructers ---------
	List();
	List(List&& other) noexcept;
	List(const List& other);
	List(const std::initializer_list<T>& list);

	// --------- Mhetods ---------
	void PushBack(const T& value);
	void PushFront(const T& value);
	void PopBack();
	void PopFront();
	void Clear();
	bool Empti() const;
	size_t Size() const;
	bool Find(const T& value) const;
	void Swap(List& other) noexcept;
	T& Front();
	const T& Front() const;
	T& Back();
	const T & Back() const;

	// --------- Operators ---------
	List& operator=(const List& other);
	List& operator=(List&& other) noexcept;
	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	// --------- Destructer ---------
	~List();

#pragma region IERATORS

#pragma region INTEFACE IERATOR

private:
	class IIterator
	{
	protected:
		Node* node;
	
	public:
		IIterator()
			: node(nullptr)
		{	}
		IIterator(Node* node)
			: node(node)
		{	}

		virtual ~IIterator() {  }

		bool operator!=(const List<T>::IIterator& other) const { return node != other.node; }
		bool operator==(const List<T>::IIterator& other) const { return !(*this != other); }
		T& operator*() { return node->data; }
		T* operator->() { return &node->data; }

		virtual IIterator& operator++() = 0;
		virtual IIterator& operator--() = 0;

		Node* GetNode() { return node; }
	};
	
#pragma endregion INTEFACE IERATOR

public:
	class Iterator : virtual public IIterator
	{
	public:
		Iterator()
			: IIterator()
		{	}
		Iterator(Node* node)
			: IIterator(node)
		{	}

		virtual Iterator& operator++() override 
		{

			IIterator::node = IIterator::node->next;
			return *this; 
		}
		Iterator operator++(int) 
		{
			Node* temp = IIterator::node;
			IIterator::node = IIterator::node->next;
			return temp; 
		}

		virtual Iterator& operator--() override
		{ 
			IIterator::node = IIterator::node->previous;
			return *this;
		}
		Iterator operator--(int)
		{
			Node* temp = IIterator::node;
			IIterator::node = IIterator::node->previous;
			return temp;
		}

		virtual ~Iterator()	{  }
	};

	class ReverseIterator : virtual public IIterator
	{
	public:
		ReverseIterator()
			: IIterator()
		{	}
		ReverseIterator(Node* node)
			: IIterator(node)
		{	}

		virtual ReverseIterator& operator--() override
		{
			IIterator::node = IIterator::node->next;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			Node* temp = IIterator::node;
			IIterator::node = IIterator::node->next;
			return temp;
		}

		virtual ReverseIterator& operator++() override
		{
			IIterator::node = IIterator::node->previous;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			Node* temp = IIterator::node;
			IIterator::node = IIterator::node->previous;
			return temp;
		}

		virtual ~ReverseIterator() {	}
	};

	/*
	  I don't use constructer delegating in those classes, bacause 
	    I have got access to interface class constructer through 
	                    virtual inheritance.
	*/
	class ConstIterator : virtual public Iterator 
	{
	public:
		ConstIterator()
			: IIterator()
		{	}
		ConstIterator(Node* node)
			: IIterator(node)
		{	}
		ConstIterator(const Iterator& iter)
			: Iterator(iter)
		{	}

		virtual ConstIterator& operator++() override
		{
			Iterator::operator++();
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator temp = *this;
			Iterator::operator++();
			return temp;
		}

		virtual ConstIterator& operator--() override
		{
			Iterator::operator--();
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator temp = *this;
			Iterator::operator--();
			return temp;
		}

		const T&  operator*() {	return IIterator::operator*();	}
		const T* operator->() { return &IIterator::operator->(); }
		
		operator Iterator() = delete;

		virtual ~ConstIterator() {  }
	};

	class ConstReverseIterator : virtual public ReverseIterator
	{
	public:
		ConstReverseIterator()
			: IIterator()
		{	}
		ConstReverseIterator(Node* node)
			: IIterator(node)
		{	}
		ConstReverseIterator(const ReverseIterator& iter)
			: ReverseIterator(iter)
		{	}
		
		virtual ConstReverseIterator& operator--() override
		{
			ReverseIterator::operator--();
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator temp = *this;
			ReverseIterator::operator--();
			return temp;
		}

		virtual ConstReverseIterator& operator++() override
		{
			ReverseIterator::operator++();
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator temp = *this;
			ReverseIterator::operator++();
			return temp;
		}

		const T& operator*() { return IIterator::operator*(); }
		const T* operator->() { return &IIterator::operator->(); }

		operator ReverseIterator() = delete;

		virtual ~ConstReverseIterator() {	}
	};

#pragma region IERATORS MHETODS

	Iterator Begin()
	{
		return Iterator(head);
	}
	Iterator End()
	{
		return Iterator(tail->next);
	}
	
	ConstIterator CBegin()
	{
		return ConstIterator(head);
	}
	ConstIterator CEnd() 
	{
		return ConstIterator(nullptr);
	}

	ReverseIterator RBegin()
	{
		return ReverseIterator(tail);
	}
	ReverseIterator REnd()
	{
		return ReverseIterator(head->previous);
	}

	ConstReverseIterator CRBegin()
	{
		return ConstReverseIterator(tail);
	}
	ConstReverseIterator CREnd()
	{
		return ConstReverseIterator(head->previous);
	}

#pragma endregion IERATORS MHETODS

#pragma endregion IERATORS	
};

template <typename T>
void List<T>::Copy(const List& other)
{
	Node* otherCurrent = other.head;

	while (otherCurrent != nullptr)
	{
		PushBack(otherCurrent->data);
		otherCurrent = otherCurrent->next;
	}
}

// -------------------- Constructers --------------------
template <typename T>
List<T>::List()
	: head(nullptr), tail(nullptr), size(0)
{	}

template <typename T>
List<T>::List(List&& other) noexcept
	: head(other.head), tail(other.tail), size(other.size)
{
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}

template <typename T>
List<T>::List(const List& other)
	: head(nullptr), tail(nullptr), size(0)
{
	Copy(other);
}

template <typename T>
List<T>::List(const std::initializer_list<T>& list)
{
	for (auto& ele : list)
	{
		this->PushBack(ele);
	}
}

// --------------------- Mhetods ---------------------
template <typename T>
void List<T>::PushBack(const T& value)
{
	if (head == nullptr)
	{
		head = new Node{ value, head, tail };
		tail = head;
	}
	else
	{
		tail = tail->next = new Node{ value, nullptr, tail };
	}
	size++;
}

template <typename T>
void List<T>::PushFront(const T& value)
{
	if (head == nullptr)
	{
		head = new Node{ value, head, tail };
		tail = head;
	}
	else
	{
		head = new Node{ value, head, head->previous };
	}
	size++;
}

template <typename T>
void List<T>::PopBack()
{
	if (size > 0)
	{
		Node* temp = tail;
		tail = tail->previous;
		if (size != 1)
		{
			tail->next = nullptr;
		}
		else
		{
			head = tail = nullptr;
		}
		delete temp;
		size--;
	}
}

template <typename T>
void List<T>::PopFront()
{
	if (size > 0)
	{
		Node* temp = head;
		head = head->next;
		if (size != 1)
		{
			head->previous = nullptr;
		}
		else
		{
			head = tail = nullptr;
		}

		delete temp;
		size--;
	}
}

template <typename T>
void List<T>::Clear()
{
	while (size)
	{
		PopFront();
	}
}

template <typename T>
bool List<T>::Empti() const
{
	return size == 0;
}

template <typename T>
size_t List<T>::Size() const
{
	return size;
}

template <typename T>
bool List<T>::Find(const T& value) const
{
	if (head != nullptr)
	{
		Node* tailFind = tail;
		Node* headFind = head;

		do
		{
			if (headFind->data == value || tailFind->data == value)
			{
				return true;
			}
			headFind = headFind->next;
			tailFind = tailFind->previous;

		} while (tailFind != headFind);
	}
	return false;
}

template <typename T>
void List<T>::Swap(List& other) noexcept
{
	List temp = std::move(other);
	other = std::move(*this);
	*this = std::move(temp);
}

template <typename T>
T& List<T>::Front()
{
	return head->data;
}

template <typename T>
typename const T& List<T>::Front() const
{
	return head->data;
}

template <typename T>
T& List<T>::Back()
{
	return tail->data;
}

template <typename T>
const T& List<T>::Back() const
{
	return tail->data;
}

// --------------------- Operators ---------------------
template <typename T>
List<T>& List<T>::operator=(const List& other)
{
	if (this != &other)
	{
		Clear();
		Copy(other);
	}
	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept
{
	if (this != &other)
	{
		Clear();
		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	return *this;
}

template <typename T>
T& List<T>::operator[](size_t index)
{
	if (index == 0)
	{
		return head->data;
	}
	else if (index == size - 1)
	{
		return tail->data;
	}
	else if (index > 0 && index < size - 1)
	{
		if (index > 0 && index <= size / 2)
		{
			Node* headFind = head->next;

			for (size_t i = 1; i < index; i++)
			{
				headFind = headFind->next;
			}
			return headFind->data;
		}
		else
		{
			Node* tailFind = tail->previous;

			for (size_t i = size - 2; i > index; i--)
			{
				tailFind = tailFind->previous;
			}
			return tailFind->data;
		}
	}
	else
	{
		throw std::out_of_range("Incorect index");
	}
}

template <typename T>
const T& List<T>::operator[](size_t index) const
{
	if (index == 0)
	{
		return head->data;
	}
	else if (index == size - 1)
	{
		return tail->data;
	}
	else if (index > 0 && index < size - 1)
	{
		if (index > 0 && index <= size / 2)
		{
			Node* headFind = head->next;

			for (size_t i = 1; i < index; i++)
			{
				headFind = headFind->next;
			}
			return headFind->data;
		}
		else
		{
			Node* tailFind = tail->previous;

			for (size_t i = size - 2; i > index; i--)
			{
				tailFind = tailFind->previous;
			}
			return tailFind->data;
		}
	}
	else
	{
		throw std::out_of_range("Incorect index");
	}
}

// -------------- Destructer --------------
template <typename T>
List<T>::~List()
{
	Clear();
}
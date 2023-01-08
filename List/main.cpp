#include <iostream>
#include "List.h"
#include "Queue.h"

int main()
{

	List<int> myList { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (List<int>::ConstReverseIterator iter = myList.CRBegin(); iter != myList.CREnd(); iter++)
	{
		std::cout << *iter << std::endl;
	}

	return 0;
}
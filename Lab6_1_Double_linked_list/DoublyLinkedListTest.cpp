//#include "DoublyLinkedList.h"
//
//
//int main()
//{
//	std::cout << "starting program\n";
//	//List Object
//	DoublyLinkedList list;
//	//Adding...
//	list.add(new Node(12), 0);
//	list.add(new Node(5), 0);
//	list.add(new Node(66), 0);
//	list.add(new Node(7), 0);
//
//	//Size...
//	std::cout << "size of list: " << list.size() << std::endl;
//
//	//Print...
//	std::cout << "Printing list forward...\n";
//	list.display_forward();
//	std::cout << "Printing list backward...\n";
//	list.display_backward();
//
//	//Remove...
//	std::cout << "Removing Node at index 2...\n";
//	list.remove(2);
//
//	//Replace...
//	std::cout << "Replacing the first node...\n";
//	list.replace(list.nodeAt(0), new Node(77));
//
//	//Printing after removal and replacement...
//	std::cout << "Printing list forward...\n";
//	list.display_forward();
//	std::cout << "Printing list backward...\n";
//	list.display_backward();
//
//	//data by index
//	std::cout << "Data at index 2: " << list[2] << std::endl;
//	//assign data at index
//	std::cout << "Changing data at index 1 to '33'...\n";
//	list[1] = 33;
//	std::cout << "Data at index 1: " << list[1] << std::endl;
//	//comparison by index
//	if (list[1]==33 && list[2]!=5)
//		std::cout << "Comparison is working!\n";
//
//	int input;
//	std::cin >> input;
//	
//	return 0;
//}
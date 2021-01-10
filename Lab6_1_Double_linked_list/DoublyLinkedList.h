#pragma once
#include <cassert>
#include <iostream>

//nodes for DoublyLinkedList
class Node
{
public:
	Node() :next(nullptr), prev(nullptr), data(0) {};
	virtual ~Node(){};
	Node(int data, Node* next=nullptr, Node* prev=nullptr) :next(next), prev(prev), data(data) {};
	Node* getNext();
	Node* getPrev();
	int& getData();
	void setNext(Node* next);
	void setPrev(Node* prev);
	void setData(int data);
private:
	Node* next;
	Node* prev;
	int data;
};

//list of nodes
class DoublyLinkedList
{
public:
	DoublyLinkedList() :head(nullptr), tail(nullptr),nodes(0){};
	~DoublyLinkedList();
	int& operator[](int index);
	bool add(Node* data, int pos);
	bool remove(int pos);
	bool replace(Node* oldNode, Node* newNode);
	int search(Node* data);
	Node* nodeAt(int pos);
	void display_forward();
	void display_backward();
	int size();
	Node* first() { return head; };
	Node* last() { return tail; };
private:
	Node* head;
	Node* tail;
	int nodes;
};


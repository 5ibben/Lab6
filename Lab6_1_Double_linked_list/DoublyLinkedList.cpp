#pragma once
#include "DoublyLinkedList.h"

Node* Node::getNext()
{
    return next;
}

Node* Node::getPrev()
{
    return prev;
}

int& Node::getData()
{
    return data;
}

void Node::setNext(Node* next)
{
    this->next = next;
}

void Node::setPrev(Node* prev)
{
    this->prev = prev;
}

void Node::setData(int data)
{
    this->data = data;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while (0 < nodes)
    {
        remove(0);
    }
}

int& DoublyLinkedList::operator[](int index)
{
    assert(0 <= index && index < nodes);
    return nodeAt(index)->getData();
}

bool DoublyLinkedList::add(Node* data, int pos)
{
    //if within required range
    if (0 <= pos && pos <= nodes && data !=nullptr)
    {
        //squeeze in the new node
        Node* next = nodeAt(pos);
        data->setNext(next);

        //set pointers
        //if first node
        if (pos == 0)
        {
            head = data;
            data->setPrev(nullptr);
            //and not last node
            if (pos != nodes)
                next->setPrev(data);
        }
        //if last node
        if (pos == nodes)
        {
            tail = data;
            //and not first node
            if (pos!=0)
                data->setPrev(nodeAt(pos - 1));
        }
        //if neither first or last
        if (0<pos&&pos<nodes)
        {
            data->setPrev(next->getPrev());
            data->getPrev()->setNext(data);
            next->setPrev(data);
        }
        
        nodes++;
        return true;
    }
    return false;
}

bool DoublyLinkedList::remove(int pos)
{
    if (0 <= pos && pos < nodes)
    {
        Node* node = nodeAt(pos);

        //set pointers
        //if first node
        if (pos == 0)
            head = node->getNext();
        else
            node->getPrev()->setNext(node->getNext());
        //if last node
        if (pos==nodes-1)
            tail = node->getPrev();
        else
            node->getNext()->setPrev(node->getPrev());

        //remove node
        delete node;
        node = nullptr;
        nodes--;
        return true;
    }
    return false;
}

//replace old node with new node
bool DoublyLinkedList::replace(Node* oldNode, Node* newNode)
{
    if (newNode != nullptr)
    {
        int n = search(oldNode);
        if (0<=n)
        {
            remove(n);
            add(newNode, n);
            return true;
        }
    }
    return false;
}

//search for data, if found, return index.
int DoublyLinkedList::search(Node* data)
{
    for (int i = 0; i < nodes; i++)
    {
        if (nodeAt(i) == data)
            return i;
    }
    return -1;
}

//search for node by index
Node* DoublyLinkedList::nodeAt(int pos)
{
    if (0<=pos&&pos<nodes)
    {
        //iterate through nodes
        Node* n = head;
        for (int i = 0; i < pos; i++)
        {
            n = n->getNext();
        }
        return n;
    }
    else
        return nullptr;
}

void DoublyLinkedList::display_forward()
{
    int i=0;
    for (Node* n = head; n!=nullptr; n=n->getNext())
    {
        std::cout << "element " << i << ": " << n->getData() << std::endl;
        i++;
    }
}

void DoublyLinkedList::display_backward()
{
    int i = nodes-1;
    for (Node* n = tail; n != nullptr; n = n->getPrev())
    {
        std::cout << "element " << i << ": " << n->getData() << std::endl;
        i--;
    }
}

int DoublyLinkedList::size()
{
    return nodes;
}

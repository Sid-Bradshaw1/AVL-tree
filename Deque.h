#ifndef DEQUE_H
#define DEQUE_H
#include "dequeinterface.h"
#include <string>
#include <iostream>
#include <ostream>
#include <istream>
#include <sstream>

using namespace std;
template<typename T>

class Deque : public DequeInterface<T>
{
private:
    int capacity;
    int num_items;
    int front_index;
    int rear_index;
    T* the_data;
public:
    Deque(void) :
            capacity(DEFAULT_CAPACITY),
            num_items(0),
            front_index(0),
            rear_index(DEFAULT_CAPACITY - 1),
            the_data (new T[DEFAULT_CAPACITY]) {}
    ~Deque()
    {
        delete[] the_data;
    }


    void push_front(const T& value)
    {
        if (num_items == capacity)
        {
            reallocate();
        }

        if (front_index == 0)
        {
            front_index = capacity - 1;
        }

        else
        {
            front_index--;
        }

        the_data[front_index] = value;
        num_items++;

    }

    void push_back(const T& value)
    {
        if (num_items == capacity)
        {
            reallocate();
        }

        if (rear_index == capacity - 1)
        {
            rear_index = 0;
        }

        else
        {
            rear_index++;
        }

        the_data[rear_index] = value;
        num_items++;

    }


    void pop_front(void) {
        if (num_items == 0)
        {
            cout << "deletion not possible";
        }
        else if (front_index == capacity - 1)
        {
            front_index = 0;
            num_items--;
        }
        else
        {
            front_index++;
            num_items--;
        }
    }

    void pop_back(void)
    {
        if (num_items == 0)
        {
            cout << "deletion not possible";
        }

        else if (rear_index == 0)
        {
            rear_index = capacity - 1;
        }

        else if (num_items == 1)
        {
            front_index = 0;
            rear_index = capacity - 1;
        }
        else
        {
            rear_index--;

        }
        num_items--;
    }


    T& front(void)
    {
        return the_data[front_index];
    }

    T& back(void)
    {
        return the_data[rear_index];
    }

    size_t size() const
    {
        return num_items;
    }

    /*size_t get_capacity() const
    {
        return capacity;
    }*/

    bool empty(void) const
    {
        if (num_items == 0)
            return true;
        else
            return false;

    }

    T& at(size_t index)
    {
        return the_data[index];
    }



    void reallocate()
    {
        int newSize = capacity * 2;
        T* dummyArray = new T[newSize];
        int dummyFront = front_index;

        for (unsigned int i = 0; i < num_items; i++)
        {
            dummyArray[i] = the_data[dummyFront];
            dummyFront = (dummyFront + 1) % capacity;
        }

        front_index = 0;
        rear_index = num_items - 1;
        capacity = newSize;

        swap(the_data, dummyArray);
        delete[] dummyArray;

    }


    string toString(void) const
    {
        int dummyFront = front_index;
        stringstream printer;
        while (dummyFront != rear_index)
        {
            if (dummyFront == capacity -1)
            {
                printer << " " << the_data[dummyFront];
                dummyFront = 0;
            }
            else
            {
                printer << " " << the_data[dummyFront];
                dummyFront++;
            }
        }

        printer << " " << the_data[rear_index];
        return printer.str();
    }

    friend std::ostream& operator<< (std::ostream& os, Deque<T>& deque)
    {
        os << deque.toString();
        return os;
    }
};

#endif //RAILROAD_DEQUE_H

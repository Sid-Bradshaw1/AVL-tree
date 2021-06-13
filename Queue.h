//
// Created by Sid Bradshaw on 3/1/21.
//

#ifndef RAILROAD_QUEUE_H
#define RAILROAD_QUEUE_H
#include "Deque.h"


using namespace std;
template<typename T>
class Queue
{
private:
    Deque<T> deque_;
public:
    Queue() {}
    ~Queue() {}

    void push(T data)
    {
        deque_.push_back(data);
    }

    void pop()
    {
        deque_.pop_front();
    }

    T front()
    {
        return deque_.front();
    }

    size_t size()
    {
        return deque_.size();
    }

    bool empty()
    {
        return deque_.empty();
    }

    string toString()
    {
        return deque_.toString();
    }

    T& at(size_t data)
    {
        return deque_.at(data);
    }


};
#endif //RAILROAD_QUEUE_H

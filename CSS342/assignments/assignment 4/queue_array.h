#include <iostream>

#ifndef _QUEUE_ARRAY_H_
#define _QUEUE_ARRAY_H_

using namespace std;

namespace aqueue
{

    template <typename T>
    class ArrayQueue
    {
    private:
        T *arr;
        int capacity;
        int arsize;

    public:
        ArrayQueue();
        ArrayQueue(const int& c); //doesnt work
        ~ArrayQueue();
        int size() const;
        bool empty() const;
        const T& front() const; 
        void enqueue(const T &e);
        void dequeue(); 
    };
    template <typename T>
    ArrayQueue<T>::ArrayQueue(){
        capacity = 20;
        arr = new T[capacity];
        arsize = 0;
    }
    template <typename T>
    ArrayQueue<T>::ArrayQueue(const int& c)
    {
        capacity = c;
        //int address = &c; //DECLARES AN ADDRESS
        //*address = 5; CHANGES THE VALUE
        arr = new T[capacity];
        cout << "Called this, " << capacity << endl; 
        arsize = 0;
    }
    template <typename T>
    ArrayQueue<T>::~ArrayQueue()
    {
        delete[] arr;
        arr = nullptr;
    }

    template <typename T>
    int ArrayQueue<T>::size() const
    {
        return arsize;
    }

    template <typename T>
    bool ArrayQueue<T>::empty() const
    {
        return arsize == 0;
    }

    template <typename T>
    const T &ArrayQueue<T>::front() const
    {
        if (empty())
        {
            cerr << "Queue empty" << endl;
        } // throw QueueEmpty("front of the queue empty");
        return arr[0];
    }

    template <typename T>
    void ArrayQueue<T>::enqueue(const T &e)
    {   
        cout << arsize << endl;
        if (arsize == capacity)
        {
            cout << "Queue Full" << endl;
            return;
        }
        arr[arsize] = e;
        arsize++;
    }

    template <typename T>
    void ArrayQueue<T>::dequeue()
    {
        if (arsize == 0)
        {
            cout << "Queue empty" << endl;
            return;
        }
        for (int i = 1; i < arsize; i++)
        {
            arr[i - 1] = arr[i];
        }
        arsize--;
    }
} // end of namespace array queue

#endif
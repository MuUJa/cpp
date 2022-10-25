#include <iostream>

using namespace std;
#define SIZE 4

template <typename T> class TQueue
{
    int size = SIZE;
    T* buffer = new T[size];
    int start = -1;
    int end = -1;
    
    bool isFull() const { return (start == (end + 1) % size); }

    public:
    TQueue() = default;
    TQueue(const TQueue & Q)
    {
        size = Q.size;
        start = 0;
        end = Q.counter() - 1;
        buffer = new T[size];
        for (int i = Q.start, j = 0; j <= end; i = (i + 1) % size, j++) 
            buffer[j] = Q.buffer[i];
    }
    ~TQueue() { delete[] buffer; }
    bool isEmpty() const { return (start == -1 && end == -1); }
    
    int counter() const { return (!isEmpty()) * (start <= end) ? (end - start + 1) : (size - (end - start + 1)); }
    T front() const
    {
        if (isEmpty()) exit(1);
        return buffer[start];
    }
    T back() const
    {
        if (isEmpty()) exit(1);
        return buffer[end];
    }
    void reset() { end = -1; start = -1; }
    bool pop()
    {
        if (isEmpty()) return false;
        if (start == end) reset();
        else start = (start + 1) % size; 
        return true;
    }
    void push(T elem)
    {
        if (isEmpty()) start = end = 0;
        else if (isFull())
        {
            T* tmp = new T[size * 2];
            for (int i = 0, j = start; i < size; i++, j = (j + 1) % size)
                tmp[i] = buffer[j];
            delete[] buffer;
            buffer = tmp;
            start = 0; end = size;
            size *= 2;
        }
        else 
            end = (end + 1) % size;
        buffer[end] = elem;
    }

    TQueue operator=(const TQueue & Q)
    {
        if (size < Q.size)
        {
            size = Q.size;
            buffer = new T[size];
        }
        start = 0;
        end = Q.counter() - 1;
        for (int i = Q.start, j = 0; j <= end; i = (i + 1) % size, j++) 
            buffer[j] = Q.buffer[i];
        return *this;
    }
    template<typename T1>
    friend ostream & operator<< (ostream &, TQueue<T1>);
};

template<typename T>
ostream & operator<< (ostream & o, TQueue<T> Q)
{
    if (Q.isEmpty()) cout << "Queue is empty";
        else
        {
            for (int i = Q.start; i != Q.end; i = (i + 1) % Q.size)
                o << Q.buffer[i] << " -> ";
            o << Q.buffer[Q.end];
        }
        o << '\n';
    return o;
}

int main()
{

}
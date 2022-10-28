#include <iostream>

using namespace std;
#define SIZE 4

template <typename T> class TDeque
{
    int size = SIZE;
    T* buffer = new T[size];
    int start = -1;
    int end = -1;
    
    bool isFull() const { return (start == (end + 1) % size); }

    public:
    TDeque() = default;
    TDeque(const TDeque & Q)
    {
        size = Q.size;
        start = 0;
        end = Q.counter() - 1;
        buffer = new T[size];
        for (int i = Q.start, j = 0; j <= end; i = (i + 1) % size, j++) 
            buffer[j] = Q.buffer[i];
    }
    ~TDeque() { delete[] buffer; }
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
    bool pop_front()
    {
        if (isEmpty()) return false;
        if (start == end) reset();
        else start = (start + 1) % size; 
        return true;
    }
    bool pop_back()
    {
        if (isEmpty()) return false;
        if (start == end) reset();
        else end = (size + end - 1) % size; 
        return true;
    }
    void push_front(T elem)
    {
        if (isEmpty()) start = end = 0;
        else if (isFull())
        {
            T* tmp = new T[size * 2];
            for (int i = 0, j = start; i < size; i++, j = (j + 1) % size)
                tmp[i + 1] = buffer[j];
            delete[] buffer;
            buffer = tmp;
            start = 0; end = size;
            size *= 2;
        }
        else 
            start = (size + start - 1) % size;
        buffer[start] = elem;
    }
    void push_back(T elem)
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

    TDeque operator=(const TDeque & Q)
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
    friend ostream & operator<< (ostream &, TDeque<T1>);
};

template<typename T>
ostream & operator<< (ostream & o, TDeque<T> Q)
{
    if (Q.isEmpty()) cout << "Deque is empty";
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
    TDeque<int> dq;
    for (int i = 0; i < 5; i++)
    {
        dq.push_front(i*2);
        dq.push_back(i*2 + 1);
    }
    cout << dq;
    cout << dq.counter() << "\n";
    cout << dq.back() << " " << dq.front() << "\n";
    dq.pop_back();
    cout << dq;
    dq.pop_front();
    cout << dq;
}

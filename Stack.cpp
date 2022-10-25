#include <iostream>
using namespace std;

template <typename T> 
class Stack {
    int _top = -1;
    int _size = 2;
    T* buffer = new int[2];

    bool full() const {
        return (_top == _size - 1);
    }

public:
    Stack() = default;
    Stack(const Stack& st) : _top(st._top), _size(st._size),
        buffer(new int[_size])
    {
        for (int i = 0; i <= _top; i++)
            buffer[i] = st.buffer[i];
    }
    Stack& operator= (const Stack& st) {
        if (this != &st) {


        }
        return *this;
    }

    bool empty() const {
        return (_top == -1);
    }

    bool pop() {
        if (empty()) return false;
        _top--;
        return true;
    }
    int size() const {
        return _top + 1;
    }
    T top() const {
        if (empty()) exit(1);
        return buffer[_top];
    }

    bool push(T element) {
        if (full()) {
            int* new_buffer = new T[_size * 2];
            if (!new_buffer) return false;
            _size *= 2;
            for (int i = 0; i <= _top; i++)
                new_buffer[i] = buffer[i];
            delete[] buffer;
            buffer = new_buffer;
        }
        buffer[++_top] = element;
        return true;
    }
};

int main()
{

}

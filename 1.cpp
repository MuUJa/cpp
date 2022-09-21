#include <iostream>

using namespace std;

class String
{
    char * buffer = NULL;
    unsigned int size = 0;

    public:

    String () = default;
    String (const String & s)
    {
        size = s.size;
        buffer = new char[size + 1];
        for (int i = 0; i <= size; i++)
            *(buffer + i) = *(s.buffer + i);
    }
    String (const char * str)
    {
        if (str)
        {
            while (*(str + size++) != 0){}
            buffer = new char[size--];
            for (int i = 0; i < size; i++)
                *(buffer + i) = *(str + i);
            *(buffer + size) = 0;
        }
    }

    char & operator[] (const int & ind)
    {
        return *(buffer + ind);
    }
    const char & operator[] (const int & ind) const 
    {
        return *(buffer + ind);
    }

    ~String()
    {
        delete [] buffer;
    }
    String & operator= (const String & s)
    {
        size = s.size;
        buffer = new char[size + 1];
        for (int i = 0; i <= size; i++)
            *(buffer + i) = *(s.buffer + i);
    }
    
    friend ostream & operator<< (ostream &, const String &);
    friend const String operator+ (const String &, const String &);
    friend const String operator* (const String &, const int &);
    friend const String & operator+= (const String &, const String &);
};

ostream & operator<< (ostream &os, const String & s)
{
    for (int i = 0; i < s.size; i++)
        cout << *(s.buffer + i);
    return os;
}

const String operator+ (const String & l, const String & s)
    {
        String tmp;
        tmp.size = l.size + s.size;
        tmp.buffer = new char [tmp.size + 1];
        for (int i = 0; i < l.size; i++)
            *(tmp.buffer + i) = *(l.buffer + i);
        for (int i = 0; i < s.size; i++)
            *(tmp.buffer + l.size + i) = *(s.buffer + i);
        *(tmp.buffer + tmp.size) = 0;
        return tmp;
    }

String & operator+= (String & s, const String & a)
{
    s = s + a;
    return s;
}

const String operator* (const String & s, const int & n)
    {
        String tmp;
        tmp.size = s.size * n;
        tmp.buffer = new char [tmp.size + 1];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < s.size; j++)
                *(tmp.buffer + s.size * i + j) = *(s.buffer + j);
        return tmp;
    }

int main()
{
    String s = "Hello";
    cout << s + " world" << endl;
    cout << String("_") * 20;
}

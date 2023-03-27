#include <iostream>

using namespace std;

class bit {
	int bitSize;
	int memSize;
	char* p;

	char mask(const int index) const {
		int memId = index / 8;
		int memOffset = index - memId * 8;
		return (1 << memOffset);
	}

public:
	bit(int size) {
		bitSize = size;
		memSize = (bitSize + 7) / 8;
		p = new char[memSize]{0};
		//memset(p, 0, memSize);
	}
	int size() const { return bitSize; }
	void set(const int index) {
		int memId = index / 8;
		p[memId] |= mask(index);
	}
	void clear(const int index) {
		int memId = index / 8;
		p[memId] &= ~(mask(index));
	}
	int get(const int index) const {
		int memId = index / 8;
		return (p[memId] & mask(index)) != 0;
	}
	bit operator|(const bit & x) const {
		bit res(bitSize);
		for (int i = 0; i < memSize; i++)
			res.p[i] = this->p[i] | x.p[i];
		return res;
	}
	bit operator&(const bit & x) const {
		bit res(bitSize);
		for (int i = 0; i < memSize; i++)
			res.p[i] = this->p[i] & x.p[i];
		return res;
	}
	bit operator~(void) const {
		bit res(bitSize);
		for (int i = 0; i < memSize; i++)
			res.p[i] = ~(this->p[i]);
		return res;
	}
};

ostream& operator<< (ostream& o, bit x) {
	for (int i = 0; i < x.size(); i++) {
		o << x.get(i);
	}
	return o;
}

class BitSet {
	int maxSize;
	bit bitField;

public:

	BitSet(int size) : maxSize(size), bitField(bit(size)) { }
	BitSet(bit b) : maxSize(b.size()), bitField(b) { }

	int size() const { return maxSize; }
	bool contains(int elem) { return bitField.get(elem); }
	void insert(int elem) { bitField.set(elem); }
	void erase(int elem) { bitField.clear(elem); }

	BitSet operator+ (BitSet & x) const { return BitSet(this->bitField | x.bitField); }
	BitSet operator* (BitSet & x) const { return BitSet(this->bitField & x.bitField); }
	BitSet operator- (BitSet & x) const { return BitSet(this->bitField & (~x.bitField)); }
};

ostream& operator<< (ostream& o, BitSet x) {
	for (int i = 0; i < x.size(); i++)
		if (x.contains(i)) o << i << " ";
	return o;
}

int main()
{
	BitSet a(6), b(6);
	a.insert(3);
	a.insert(1);
	b.insert(2);
	b.insert(3);
	cout << a << "\n";
	cout << b << "\n";
	cout << a + b << "\n";
	cout << a - b << "\n";
	cout << a * b << "\n";
}

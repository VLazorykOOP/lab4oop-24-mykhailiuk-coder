#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
using namespace std;

class VectorUInt {
private:
    int size;
    unsigned int* data;
    int codeError;
    static int objectCount;

public:
    VectorUInt() : size(1), codeError(0) {
        data = new (nothrow) unsigned int[1];
        if (!data) codeError = 1;
        else data[0] = 0;
        objectCount++;
    }

    VectorUInt(int n) : size(n), codeError(0) {
        if (n < 0) {
            codeError = 3;
            data = nullptr;
            return;
        }
        data = new (nothrow) unsigned int[n] {};
        if (!data) codeError = 1;
        objectCount++;
    }

    VectorUInt(int n, unsigned int value) : size(n), codeError(0) {
        if (n < 0) {
            codeError = 3;
            data = nullptr;
            return;
        }
        data = new (nothrow) unsigned int[n];
        if (!data) codeError = 1;
        else fill(data, data + n, value);
        objectCount++;
    }

    VectorUInt(const VectorUInt& other) : size(other.size), codeError(other.codeError) {
        data = new (nothrow) unsigned int[size];
        if (!data) codeError = 1;
        else copy(other.data, other.data + size, data);
        objectCount++;
    }

    VectorUInt& operator=(const VectorUInt& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        codeError = other.codeError;
        data = new (nothrow) unsigned int[size];
        if (!data) codeError = 1;
        else copy(other.data, other.data + size, data);
        return *this;
    }

    ~VectorUInt() {
        delete[] data;
        objectCount--;
    }

    void setElement(size_t index, unsigned int value = 0) {
        if (index >= size) {
            codeError = 2;
            return;
        }
        data[index] = value;
    }

    unsigned int getElement(size_t index) const {
        if (index >= size) return 0;
        return data[index];
    }

    void print() const {
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << endl;
    }

    VectorUInt operator+(const VectorUInt& other) const {
        if (size != other.size) throw invalid_argument("Error: different vector sizes");
        VectorUInt result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] + other.data[i];
        return result;
    }

    VectorUInt operator-(const VectorUInt& other) const {
        if (size != other.size) throw invalid_argument("Error: different vector sizes");
        VectorUInt result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] - other.data[i];
        return result;
    }

    VectorUInt operator*(unsigned int scalar) const {
        VectorUInt result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] * scalar;
        return result;
    }

    VectorUInt operator/(unsigned int scalar) const {
        VectorUInt result(size);
        if (scalar == 0) {
            result.codeError = 2;
            return result;
        }
        for (int i = 0; i < size; i++) result.data[i] = data[i] / scalar;
        return result;
    }

    VectorUInt operator%(unsigned int scalar) const {
        VectorUInt result(size);
        if (scalar == 0) {
            result.codeError = 2;
            return result;
        }
        for (int i = 0; i < size; i++) result.data[i] = data[i] % scalar;
        return result;
    }

    VectorUInt operator|(const VectorUInt& other) const {
        int minSize = std::min(size, other.size);
        VectorUInt result(minSize);
        for (int i = 0; i < minSize; i++) result.data[i] = data[i] | other.data[i];
        return result;
    }

    VectorUInt operator^(const VectorUInt& other) const {
        int minSize = std::min(size, other.size);
        VectorUInt result(minSize);
        for (int i = 0; i < minSize; i++) result.data[i] = data[i] ^ other.data[i];
        return result;
    }

    VectorUInt operator&(const VectorUInt& other) const {
        int minSize = std::min(size, other.size);
        VectorUInt result(minSize);
        for (int i = 0; i < minSize; i++) result.data[i] = data[i] & other.data[i];
        return result;
    }

    VectorUInt& operator+=(const VectorUInt& other) {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) data[i] += other.data[i];
        return *this;
    }

    VectorUInt& operator-=(const VectorUInt& other) {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) data[i] -= other.data[i];
        return *this;
    }

    VectorUInt& operator*=(unsigned int scalar) {
        for (int i = 0; i < size; i++) data[i] *= scalar;
        return *this;
    }

    VectorUInt& operator/=(unsigned int scalar) {
        if (scalar == 0) {
            codeError = 2;
            return *this;
        }
        for (int i = 0; i < size; i++) data[i] /= scalar;
        return *this;
    }

    VectorUInt& operator%=(unsigned int scalar) {
        if (scalar == 0) {
            codeError = 2;
            return *this;
        }
        for (int i = 0; i < size; i++) data[i] %= scalar;
        return *this;
    }

    VectorUInt& operator|=(const VectorUInt& other) {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) data[i] |= other.data[i];
        return *this;
    }

    VectorUInt& operator^=(const VectorUInt& other) {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) data[i] ^= other.data[i];
        return *this;
    }

    VectorUInt& operator&=(const VectorUInt& other) {
        int minSize = std::min(size, other.size);
        for (int i = 0; i < minSize; i++) data[i] &= other.data[i];
        return *this;
    }

    VectorUInt& operator++() {
        for (int i = 0; i < size; i++) data[i]++;
        return *this;
    }

    VectorUInt operator++(int) {
        VectorUInt temp(*this);
        ++(*this);
        return temp;
    }

    VectorUInt& operator--() {
        for (int i = 0; i < size; i++) data[i]--;
        return *this;
    }

    VectorUInt operator--(int) {
        VectorUInt temp(*this);
        --(*this);
        return temp;
    }

    VectorUInt operator~() const {
        VectorUInt result(size);
        for (int i = 0; i < size; i++) result.data[i] = ~data[i];
        return result;
    }

    VectorUInt operator-() const {
        VectorUInt result(size);
        for (int i = 0; i < size; i++) result.data[i] = static_cast<unsigned int>(-static_cast<int>(data[i]));
        return result;
    }

    bool operator==(const VectorUInt& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) if (data[i] != other.data[i]) return false;
        return true;
    }

    bool operator!=(const VectorUInt& other) const {
        return !(*this == other);
    }

    bool operator<(const VectorUInt& other) const {
        return size < other.size;
    }

    bool operator>(const VectorUInt& other) const {
        return size > other.size;
    }

    bool operator<=(const VectorUInt& other) const {
        return !(*this > other);
    }

    bool operator>=(const VectorUInt& other) const {
        return !(*this < other);
    }

    unsigned int& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 2;
            return data[size - 1];
        }
        return data[index];
    }

    void operator()() const {
        cout << "Vector size: " << size << endl;
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << endl;
    }

    int getState() const { return codeError; }
    static int getObjectCount() { return objectCount; }

    friend ostream& operator<<(ostream& out, const VectorUInt& v) {
        for (int i = 0; i < v.size; i++) out << v.data[i] << " ";
        return out;
    }

    friend istream& operator>>(istream& in, VectorUInt& v) {
        for (int i = 0; i < v.size; i++) in >> v.data[i];
        return in;
    }

    void* operator new(size_t size) {
        void* p = malloc(size);
        if (!p) throw bad_alloc();
        return p;
    }

    void operator delete(void* p) {
        free(p);
    }
};

int VectorUInt::objectCount = 0;

int main() {
    //Завдання 1
    cout << "Task_2\n\n";
    VectorUInt v1;
    VectorUInt v2(5);
    VectorUInt v3(5, 10);
    VectorUInt v4 = v3;

    cout << "Vector v1: "; v1.print();
    cout << "Vector v2: "; v2.print();
    cout << "Vector v3: "; v3.print();
    cout << "Vector v4 (copy v3): "; v4.print();

    v2.setElement(2, 20);
    cout << "New v2: "; v2.print();

    VectorUInt v5 = v3 + v2;
    cout << "v3 + v2: "; v5.print();

    VectorUInt v6 = v3 * 2;
    cout << "v3 * 2: "; v6.print();

    cout << "Number of objects: " << VectorUInt::getObjectCount() << endl;
	cout << "Error state: " << v1.getState() << endl;

    return 0;
}

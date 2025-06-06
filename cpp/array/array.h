#ifndef ARRAY_H
#define ARRAY_H
// #define ARRAY_SIZE 100

class Array{
    private:
    int *pArr_;
    int size_;
    
public:
    static int getDefaultArraySize();        // 전역함수

    static const int ARRAY_SIZE;
    Array(const int *pArr, int size);
    explicit Array(int size = ARRAY_SIZE);
    Array(const Array& rhs);
    Array& operator = (const Array& rhs);
    bool operator == (const Array& rhs) const;
    ~Array();

    int size() const;

    int& operator[](int index);

    const int& operator[](int index) const;

    
    // Array()    {}
    // Array(const Array& ) {}
    // ~Array()
    // Array& operator=(const Array& ){}   // +=, -=, *=, /= (O) // %=, &=. |=, ^=  (X)
    // Array *operator&(){return this;}
    // const Array *operator&() const{return this;}
};


#endif
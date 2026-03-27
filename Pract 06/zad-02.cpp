#include <iostream>
#include <functional>

template <typename T>
class Pipeline {
public:
    Pipeline();
    Pipeline(const Pipeline&);
    Pipeline& operator=(const Pipeline&);
    ~Pipeline();

    Pipeline& pipe(std::function<T(T)> f);
    int getSize() const;
    void clear();

    T operator()(T val) const;
    Pipeline operator+(const Pipeline& other) const;
    Pipeline& operator+=(const Pipeline& other);

    template <typename R>
    R reduce(std::function<R(R, T)> f, R init) const;

private:
    std::function<T(T)>* funcs;
    int size;
    int capacity;

    void free();
    void copyFrom(const Pipeline& other);
    void resize();
};

template <typename T>
Pipeline<T>::Pipeline() : funcs(nullptr), size(0), capacity(0) {}

template <typename T>
Pipeline<T>::Pipeline(const Pipeline& other) { copyFrom(other); }

template <typename T>
Pipeline<T>& Pipeline<T>::operator=(const Pipeline& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
Pipeline<T>::~Pipeline() { free(); }

template <typename T>
Pipeline<T>& Pipeline<T>::pipe(std::function<T(T)> f) {
    if (size == capacity) resize();
    funcs[size++] = f;
    return *this;
}

template <typename T>
int Pipeline<T>::getSize() const { return size; }

template <typename T>
void Pipeline<T>::clear() { size = 0; }

template <typename T>
T Pipeline<T>::operator()(T val) const {
    for (int i = 0; i < size; i++)
        val = funcs[i](val);
    return val;
}

template <typename T>
Pipeline<T> Pipeline<T>::operator+(const Pipeline& other) const {
    Pipeline res = *this;
    res += other;
    return res;
}

template <typename T>
Pipeline<T>& Pipeline<T>::operator+=(const Pipeline& other) {
    for (int i = 0; i < other.size; i++)
        pipe(other.funcs[i]);
    return *this;
}

template <typename T>
template <typename R>
R Pipeline<T>::reduce(std::function<R(R, T)> f, R init) const {
    T intermediate = init;
    R acc = init;
    for (int i = 0; i < size; i++) {
        intermediate = funcs[i](intermediate);
        acc = f(acc, intermediate);
    }
    return acc;
}

template <typename T>
void Pipeline<T>::free() {
    delete[] funcs;
    funcs = nullptr;
    size = capacity = 0;
}

template <typename T>
void Pipeline<T>::copyFrom(const Pipeline& other) {
    size = other.size;
    capacity = other.capacity;
    funcs = new std::function<T(T)>[capacity];
    for (int i = 0; i < size; i++)
        funcs[i] = other.funcs[i];
}

template <typename T>
void Pipeline<T>::resize() {
    int newcapacity = capacity == 0 ? 2 : capacity * 2;
    std::function<T(T)>* newFuncs = new std::function<T(T)>[newcapacity];
    for (int i = 0; i < size; i++)
        newFuncs[i] = funcs[i];
    delete[] funcs;
    funcs = newFuncs;
    capacity = newcapacity;
}

int main() {
    Pipeline<int> p;
    p.pipe([](int x){ return x + 1; })
     .pipe([](int x){ return x * 3; });

    std::cout << p(4) << "\n";      // (4+1)*3 = 15
    std::cout << p.getSize() << "\n";  // 2

    // operator+= и operator+
    Pipeline<int> p2;
    p2.pipe([](int x){ return x - 2; });

    Pipeline<int> p3 = p + p2;
    std::cout << p3(4) << "\n";     // ((4+1)*3)-2 = 13
    std::cout << p3.getSize() << "\n"; // 3

    // reduce: init=4, step1: 4->5 acc=4+5=9, step2: 5->15 acc=9+15=24
    int result = p.reduce<int>([](int acc, int x){ return acc + x; }, 4);
    std::cout << result << "\n";    // 24
}
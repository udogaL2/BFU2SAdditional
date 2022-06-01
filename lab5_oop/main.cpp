#include <iostream>

template <typename T>
class Base{
public:
    explicit Base(int j){
        i = new T[j];
    }
    ~Base(){
        std::cout << "dest\n";
        delete i;
    }

private:
    T* i;
};

int main() {
    auto* f =new Base<int>(100);
    auto* g =new Base<char>(100);

    delete f;
//    f = reinterpret_cast<Base<int> *>(g);
    delete g;

    return 0;
}

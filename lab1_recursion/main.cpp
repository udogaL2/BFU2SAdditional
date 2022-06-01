#include <iostream>

int sumDig(int num) {
    if (num < 10)
        return num;
    else {
        return num % 10 + sumDig(num / 10);
    }
}

int main() {
    int num;
//    while (true) {
        std::cin >> num;
        std::cout << sumDig(num) << '\n';
//    }
    return 0;
}

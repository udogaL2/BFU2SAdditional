#include <iostream>

// O(n^2) - худшее
// O(n*log^2n) - лучшее

void sortShell(int n, int *mas) {
    int k = n / 2;
    while (k > 0) {
        for (int i = 0; i < n - k; i++) {
            int j = i;
            while (j >= 0 and mas[j] > mas[j + k]) {
                int temp = mas[j];
                mas[j] = mas[j + k];
                mas[j+k] = temp;
                j--;
            }
        }
        k /= 2;
    }
}

int main() {
    int m[10] = {1000, -3, 4, 3, 34, 5, -2, 3, 12,-1};
    sortShell(10, m);
    for(auto n : m){
        std::cout << n << ' ';
    }
    return 0;
}

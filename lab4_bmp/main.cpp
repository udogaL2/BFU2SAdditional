#include "inc/BMP.h"
#include <iostream>
#include <cmath>

using std::acos;
using std::asin;

int main() {
    try {
        mt::images::BMP test_bmp;
        test_bmp.Open("../out2.bmp");
        test_bmp.Code({255, 255, 255});
        test_bmp.Save("../out2.bmp");
        test_bmp.Uncode({255, 255, 255});
        test_bmp.Save("../out3.bmp");
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

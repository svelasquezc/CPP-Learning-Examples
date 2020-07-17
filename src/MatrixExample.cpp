#include <iostream>
#include "MyMatrix.hpp"

int main(){
    using Matrixd = MyMatrix<double>;

    Matrixd mat(5,5,1);

    mat[4][4] = static_cast<double>(5);
    mat[0][0] = static_cast<double>(5);

    std::cout << mat[0][0] << std::endl;
}

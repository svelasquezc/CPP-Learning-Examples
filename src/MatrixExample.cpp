#include <iostream>
#include "MyMatrix.hpp"

int main(){
    using Matrixd = MyMatrix<double>;

    Matrixd mat(5,5,1);

    mat[4][4] = 10;
    mat[0][0] = static_cast<double>(5);

    std::cout << "Frobenius Norm: static_cast<double>(mat) = " << static_cast<double>(mat) << std::endl;
    std::cout << "int cast: static_cast<int>(mat) = " << static_cast<int>(mat) << std::endl;
    
    //std::cout << mat[0][0] << std::endl;
    
    
}

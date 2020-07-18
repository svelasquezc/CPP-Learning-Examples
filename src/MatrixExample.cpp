#include <iostream>
#include "MyMatrix.hpp"

#define DEBUG 0

#if DEBUG

template<typename TD> class TypeDescriptor;

#endif

int main(){
    using Matrixd = MyMatrix<double>;
    using Matrixf = MyMatrix<float>;

    Matrixd mat(5,5,1);

    Matrixf mat2(5,5,10);
    
    mat[4][4] = 10;
    mat[0][0] = static_cast<double>(5);

    std::cout << "Frobenius Norm: static_cast<double>(mat) = " << static_cast<double>(mat) << std::endl;
    std::cout << "int cast: static_cast<int>(mat) = " << static_cast<int>(mat) << std::endl;

    //auto mat3(mat + mat2);
    
#if DEBUG
    TypeDescriptor<decltype(mat3)> td();
#endif
    //std::cout << mat[0][0] << std::endl;
    
    
}

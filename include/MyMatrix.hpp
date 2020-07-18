#ifndef MYMATRIX_HPP
#define MYMATRIX_HPP

#include <vector>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <exception>
/*
  Here I am going to present the following examples:

  - Member functions
  - Operator overload (operator+, operator[])
  - cast operator (operator "int")
  - Templates
  - For_each with lambdas
  - keyword auto
  - noexcept
  - Copy Elision (RVO)
*/
    
template<typename Precision>
class MyMatrix{

    static_assert(std::is_arithmetic_v<Precision>, "Precision type is not an arithmetic type");

    using Mat_t = std::vector<Precision>;
    using Precision_t = Precision;
    
private:
    
    std::vector<Precision> _elements;
    std::size_t _rows;
    std::size_t _cols;
    
    class ProxyAccessor{
        
    private:
        MyMatrix& _my_mat;
        std::size_t _row_index;
        
    public:

        explicit ProxyAccessor(MyMatrix& my_mat, std::size_t row_index) : _my_mat(my_mat), _row_index(row_index) {}
        
        Precision_t& operator[](std::size_t col_index){
            return _my_mat._elements[_row_index*_my_mat._rows + col_index];
        }
    };

    template<typename SPrecision> friend class MyMatrix;
    
public:
    
    //Special Members - in C++
    //Default Constructor

    // Explicitly deleted -- since C++11
    MyMatrix() = delete;
    
    MyMatrix(std::size_t rows, std::size_t cols) : _rows(rows), _cols(cols){
        _elements = Mat_t(_rows*_cols, static_cast<Precision>(0));
    }


    // Disabling constructor for non-convertible types, enable_if since C++11
    // Templates at least since C++98
    template<typename SPrecision,
             typename =
             std::enable_if<std::is_convertible_v<SPrecision, Precision>, SPrecision>
             >
    MyMatrix(std::size_t rows, std::size_t cols, SPrecision val) : _rows(rows), _cols(cols){
        _elements = Mat_t(_rows*_cols, static_cast<Precision>(val));
    }
    
    //Copy constructor -- at least C++98
    template<typename SPrecision,
             typename =
             std::enable_if<std::is_convertible_v<SPrecision, Precision>, SPrecision>
             >
    MyMatrix(const MyMatrix<SPrecision>& matrix) noexcept{
        _rows = matrix._rows;
        _cols = matrix._cols;

        _elements = Mat_t(_rows*_cols);

        for(std::size_t i=0; i<_rows; ++i){
            for(std::size_t j=0; j<_cols; ++j){
                _elements[i][j] = static_cast<Precision>(matrix[i][j]);
            };
        };
        
    }

    //Move constructor - since C++11
    MyMatrix(MyMatrix&& matrix) noexcept : _rows(std::move_if_noexcept(matrix._rows)),
                                           _cols(std::move_if_noexcept(matrix._cols)),
                                           _elements(std::move_if_noexcept(matrix._elements)){}

    // Explicit default -- since C++11
    ~MyMatrix() = default;

    //Operator [] - at least C++98
    ProxyAccessor operator[](std::size_t index_i) {
        //Here a RVO - Copy Elision must ocurr
        return ProxyAccessor(*this, index_i);
    };


    //auto as return type since C++14, helper variables since C++17
    template<typename SPrecision,
             typename = 
             std::enable_if<std::is_convertible_v<SPrecision, Precision>, Precision>
             >
    auto operator+(MyMatrix<SPrecision>& mat) const{
        
        using ResultType = decltype(std::declval<SPrecision>()+std::declval<Precision>());
        
        if(_rows == mat._rows && _cols == mat._cols){
            MyMatrix<ResultType> result(_rows, _cols);
            std::transform(_elements.begin(), _elements.end(),
                           mat._elements.begin(), result._elements.begin(),
                           std::plus<ResultType>());
            return result;
        }else{
            throw std::runtime_error("rows and cols in sum matrixes do not match");
        }
    }
    
    // Cast operator to Precision -- explicit cast since C++11
    explicit operator Precision(){
        // Frobenius Norm of a Matrix
        // https://mathworld.wolfram.com/FrobeniusNorm.html
        //
        Precision fnorm=static_cast<Precision>(0);
        std::for_each(_elements.begin(), _elements.end(),
                      [&](auto value){fnorm+=std::pow(value,2);});
        return std::sqrt(fnorm);
    }
    
    // Cast operator to int -- explicit cast since C++11
    explicit operator int(){
        return static_cast<int>(static_cast<Precision>(*this));
    }
};

#endif /* MYMATRIX_HPP */

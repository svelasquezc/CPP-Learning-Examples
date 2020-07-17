#ifndef MYMATRIX_HPP
#define MYMATRIX_HPP

#include <vector>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
/*
  Here I am going to present the following examples:

  - Member functions
  - Operator definition (operator+)
  - cast operator (operator "int")
  - Templates
  - For_each with lambdas
  - keyword auto
  - noexcept
 */


template<typename Precision>
class MyMatrix{

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
    
    
public:
    
    //Special Members
    //Default Constructor

    MyMatrix() = delete;
    
    MyMatrix(std::size_t rows, std::size_t cols) : _rows(rows), _cols(cols){
        _elements = Mat_t(_rows*_cols, static_cast<Precision>(0));
    }


    // Disabling constructor for non-convertible types
    template<typename ValuePrecision,
             typename =
             std::enable_if<std::is_convertible_v<ValuePrecision, Precision>, ValuePrecision>
             >
    MyMatrix(std::size_t rows, std::size_t cols, ValuePrecision val) : _rows(rows), _cols(cols){
        _elements = Mat_t(_rows*_cols, static_cast<Precision>(val));
    }
    
    //Copy constructor
    MyMatrix(const MyMatrix& matrix) noexcept{
        _rows = matrix._rows;
        _cols = matrix._cols;

        _elements = Mat_t(_rows*_cols);

        for(std::size_t i=0; i<_rows; ++i){
            for(std::size_t j=0; j<_cols; ++j){
                _elements[i][j] = matrix[i][j];
            };
        };
        
    }

    //Move constructor
    MyMatrix(MyMatrix&& matrix) noexcept : _rows(std::move_if_noexcept(matrix._rows)),
                                  _cols(std::move_if_noexcept(matrix._cols)),
                                  _elements(std::move_if_noexcept(matrix._elements)){}


    ~MyMatrix() = default;

    //Operator []
    ProxyAccessor operator[](std::size_t index_i) {
        return ProxyAccessor(*this, index_i);
    };

    template<typename SPrecision,
             typename =
             std::enable_if<std::is_convertible_v<SPrecision, Precision>, Precision>
             >
    auto operator+(MyMatrix<SPrecision>& mat){
        
    }
    
    // Cast operator to Precision
    explicit operator Precision(){
        // Frobenius Norm of a Matrix
        // https://mathworld.wolfram.com/FrobeniusNorm.html
        //
        Precision fnorm=static_cast<Precision>(0);
        std::for_each(_elements.begin(), _elements.end(),
                      [&](auto value){fnorm+=std::pow(value,2);});
        return std::sqrt(fnorm);
    }
    
    // Cast operator to int
    explicit operator int(){
        return static_cast<int>(static_cast<Precision>(*this));
    }
};

#endif /* MYMATRIX_HPP */

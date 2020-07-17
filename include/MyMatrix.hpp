#ifndef MYMATRIX_HPP
#define MYMATRIX_HPP

#include <vector>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <numeric>
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

    using Row_t = std::vector<std::vector<Precision>>;
    using Col_t = std::vector<Precision>;
    using Precision_t = Precision;
    
private:
    
    std::vector<std::vector<Precision>> _elements;
    std::size_t _rows;
    std::size_t _cols;
    
public:
    
    //Special Members
    //Default Constructor

    MyMatrix() = delete;
    
    MyMatrix(std::size_t rows, std::size_t cols) : _rows(rows), _cols(cols){
        _elements = Row_t(rows, Col_t(cols, static_cast<Precision>(0)));
    }


    // Disabling constructor for non-convertible types
    template<typename ValuePrecision,
             typename =
             std::enable_if<std::is_convertible_v<ValuePrecision, Precision>, ValuePrecision>
             >
    MyMatrix(std::size_t rows, std::size_t cols, ValuePrecision val) : _rows(rows), _cols(cols){
        _elements = Row_t(rows, Col_t(cols, static_cast<Precision>(val)));
    }
    
    //Copy constructor
    MyMatrix(const MyMatrix& matrix) noexcept{
        _rows = matrix._rows;
        _cols = matrix._cols;

        _elements = Row_t(_rows, Col_t(_cols));

        for(std::size_t i=0; i<_rows; ++i){
            for(std::size_t j=0; j<_cols; ++j){
                _elements[i][j] = matrix[i,j];
            };
        };
        
    }

    //Move constructor
    MyMatrix(MyMatrix&& matrix) : _rows(std::move_if_noexcept(matrix._rows)),
                                  _cols(std::move_if_noexcept(matrix._rows)),
                                  _elements(std::move_if_noexcept(matrix._elements)){}


    ~MyMatrix() = default;

    //Operator []
    Col_t& operator[](std::size_t index_i) {
        return _elements[index_i];
    };
    
    // Cast operator to Precision
    operator Precision(){
        // Frobenius Norm of a Matrix
        // https://mathworld.wolfram.com/FrobeniusNorm.html
        //
        Precision fnorm=static_cast<Precision>(0);
        std::for_each(_elements.begin(), _elements.end(),
                      [&](auto col){fnorm+=std::accumulate(col.begin(), col.end(), 0);});
        return fnorm;
    }
    
    // Cast operator to int
    operator int(){
        return static_cast<int>(static_cast<Precision>(*this));
    }
};

#endif /* MYMATRIX_HPP */

#include "PImplExample.hpp"

#include <iostream>

struct pImplExample::Impl{

    std::string _message;

    Impl() = delete;
    
    Impl(std::string message) : _message(message) {};

    Impl(const Impl&) = default;
    
    Impl(Impl&&) = default;

    void print() const{
        
        std::cout << "This is a message printed using pImpl " <<  _message << std::endl;
    }
    
};

pImplExample::pImplExample(std::string message) : _pImpl(new Impl(message)){}

pImplExample::pImplExample(const pImplExample& other) : _pImpl(new Impl(*other._pImpl)){}

pImplExample& pImplExample::operator=(pImplExample rhs){
    std::swap(_pImpl, rhs._pImpl);
    return *this;
}

pImplExample::pImplExample(pImplExample&&) = default;

pImplExample& pImplExample::operator=(pImplExample&&) = default;

void pImplExample::print() const{
    _pImpl->print();
}

pImplExample::~pImplExample() = default;

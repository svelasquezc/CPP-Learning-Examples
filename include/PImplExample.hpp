#ifndef PIMP_EXAMPLE
#define PIMP_EXAMPLE

#include <memory>
#include <string>

/*
  
  Pointer to implementation example,
  In this header the interface is declared  


 */

class pImplExample{
private:
    struct Impl;
    // For pImplExaple to be copy constructible pointer to Implentation must be shared_ptr.
    std::unique_ptr<Impl> _pImpl;
    
public:
    
    pImplExample(std::string message);


    pImplExample(const pImplExample& other);
    pImplExample& operator=(pImplExample rhs);

    pImplExample(pImplExample&&);
    pImplExample& operator=(pImplExample&&);
    
    void print() const;

    ~pImplExample();
    
    //Interface Methods
    
};

#endif /* PIMP_EXAMPLE */

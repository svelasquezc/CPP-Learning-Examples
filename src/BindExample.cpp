#include <functional>
#include <iostream>

#define FUNCERROR 0

/*

  In this example, I show how std::bind can be use to construct a callable object
  with a class method (static member).

 */


class StaticMethodExample{

public:

    static void methodExample(const char* name);
};

void operacion(std::function<void()> func){
    func();
}

int main(){
    
#if FUNCERROR
    //this command does not compile (type does not match)
    operacion(StaticMethodExample::methodExample);
    //invalid use of void expression
    operacion(StaticMethodExample::methodExample("Steven"));
#else
    operacion(std::bind(StaticMethodExample::methodExample, "Steven"));
#endif
}

void StaticMethodExample::methodExample(const char* name){
    std::cout << "methodExample() being called with name: "<< name <<"\n";
}

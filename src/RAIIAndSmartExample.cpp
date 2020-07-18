#include <memory>
#include <iostream>


class RAIIExample{

    std::string _name;

    static std::size_t count_created;
    
public:

    

    //Default Constructor
    RAIIExample(std::string name) : _name(name) {
        ++count_created;
        std::cout << "New RAIIExample("<< name << ") Object\n";
        std::cout << "There are "<< count_created << " RAIIExamples\n\n";
    };

    const std::string& name() const{
        return _name;
    }

    ~RAIIExample(){
        --count_created;
        std::cout << "RAIIExample(" <<_name<<") Deleted\n";
        std::cout << "There are "<< count_created << " RAIIExamples\n\n";
    };
};

std::size_t RAIIExample::count_created = 0;
    
int main(){


    //Smart Pointers -- Well Stablished in C++11
    std::weak_ptr<RAIIExample> observer; 
    
    {
        //Type Deduction -- C++11
        auto shared_RAII1 = std::make_shared<RAIIExample>("First");

        observer = shared_RAII1;

        //Resource Adquisition Is Initialization (RAII)
        //Destructors are called at the end of the scope
        {
            auto shared_RAII2 = shared_RAII1;

            std::cout << shared_RAII2->name() << " with " << shared_RAII1.use_count() << " shared pointers\n";
        
            RAIIExample second("Second");
        
        }

        std::cout << shared_RAII1->name() << " now has " << shared_RAII1.use_count() << " shared pointers\n";
    }

    if(observer.expired()) std::cout << "weak_ptr pointing to a deleted object\n";
                               
}

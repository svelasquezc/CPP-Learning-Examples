#include <memory>
#include <string>
#include <vector>
#include <iostream>

//Scoped enum -- C++11
enum class Element{TREE, ROCK};

//Abstract class 
class AbstractElement{
protected:
    std::string _name;
public:
    virtual ~AbstractElement() = default;
    //Virtual pure method
    virtual void describe() = 0;
};

class Tree : public AbstractElement {
    std::size_t _number_of_leafs;
    std::string _specie;
public:

    Tree(std::size_t number_of_leafs, std::string specie) : _number_of_leafs(number_of_leafs),
                                                            _specie(specie){
        using namespace std::string_literals;
        _name = "Tree"s;
    }
    //Rule of five
    Tree(const Tree&) = default;

    Tree(Tree&&) = default;

    Tree& operator=(Tree&) = default;

    Tree& operator=(Tree&&) = default;
    
    ~Tree() = default;
    
    // Override keyword C++11
    void describe() override{
        std::cout << _name << " of the species " << _specie << " with " << _number_of_leafs << " leafs.\n";
    };
};

class Rock : public AbstractElement {
    std::vector<std::string> _minerals;
public:


    // Variadic Template -- C++11
    template<typename ...Minerals>
    Rock(Minerals... mins){
        using namespace std::string_literals;
        _name="Rock"s;
        //Initializer list for vector assignment
        _minerals = {mins...};
    }
    //Rule of five
    Rock(const Rock&) = default;

    Rock(Rock&&) = default;

    Rock& operator=(Rock&) = default;

    Rock& operator=(Rock&&) = default;
    
    ~Rock() = default;

    // Override keyword C++11
    void describe() override{
        std::cout << _name << " with minerals: ";
        for(const auto& mineral : _minerals){
            std::cout << mineral << " ";
        }
        std::cout << "\n";
    };
};


int main(){

    using namespace std::string_literals;
    
    Element obj = Element::TREE;

    //Unique ptr -- C++11
    std::unique_ptr<AbstractElement> uptr;
    
    //Switch with scoped Enum
    switch(obj){

    case Element::TREE:
        uptr = std::make_unique<Tree>(10000,"oak"s);
        break;
    case Element::ROCK:
        uptr = std::make_unique<Rock>("Calcite"s, "Quartz"s, "Amphibole"s, "Feldspar"s);
        break;
    }

    // Late calling to derived or overriden method
    uptr->describe();
}

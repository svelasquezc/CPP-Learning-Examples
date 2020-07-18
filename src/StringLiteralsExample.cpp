#include <string>
#include <iostream>
#include <typeinfo>

int main(){

    using namespace std::string_literals;
    
    auto sentence = "I am a sentence with null \0\0 characters"s;
    auto Lsentence = L"I am a sentence with null \0\0 characters";
    auto u8sentence = u8"I am a sentence with null \0\0 characters";
    auto u16sentence = u"I am a sentence with null \0\0 characters";
    auto u32sentence = U"I am a sentence with null \0\0 characters";

    

    //std::cout << "sentence with Type: " << typeid(sentence).name() << " containing " << sentence << std::endl;
    //std::cout << "Lsentence with Type: " << typeid(Lsentence).name() << " containing " << std::wstring(Lsentence) << std::endl;
    //std::cout << "u8sentence with Type: " << typeid(u8sentence).name() << " containing " << u8sentence << std::endl;
    //std::cout << "u16sentence with Type: " << typeid(u16sentence).name() << " containing " << std::u16string(u16sentence) << std::endl;
    //std::cout << "u32sentence with Type: " << typeid(u32sentence).name() << " containing " << std::u32string(u32sentence) << std::endl;  
}

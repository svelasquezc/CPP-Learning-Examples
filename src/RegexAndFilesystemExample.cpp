#include <filesystem>
#include <regex>
#include <exception>
#include <iostream>
#include <chrono>
#include <cstdint>
#include <cmath>
/*
  
  This example finds a file by using r

*/

namespace fs = std::filesystem;


//From: https://en.cppreference.com/w/cpp/filesystem/directory_entry/file_size
struct HumanReadable { std::uintmax_t size {}; };
 
template <typename Os> Os& operator<< (Os& os, HumanReadable hr)
{
    int i{};
    double mantissa = hr.size;
    for (; mantissa >= 1024.; ++i) {
        mantissa /= 1024.;
    }
    mantissa = std::ceil(mantissa * 10.) / 10.;
    os << mantissa << "BKMGTPE"[i];
    return i == 0 ? os : os << "B (" << hr.size << ')';
}
//////////////////////////////////////////////////////////////////////////////////

int main(const int argc, const char* argv[]){
    if(argc <= 1){
        throw std::runtime_error("No input file given");
    }else{

        auto root = fs::current_path().root_path();
        auto file_to_find = std::string(argv[1]);
        
        std::regex self_regex(file_to_find,
                              std::regex_constants::ECMAScript | std::regex_constants::icase);
         
        std::cout << "Root directory: " << root << "\nFile to find name: " << file_to_find << std::endl;

        //TODO: Try to solve for root
        //There is probably a bug because permission denied directories are still being accessed
        //https://github.com/boostorg/filesystem/issues/112

        //Using solution here, still trying to access non permitted directories
        //https://stackoverflow.com/questions/58309449/c-how-to-use-stdfilesystemdirectory-options
        
        const fs::directory_options options = (
                                               std::filesystem::directory_options::skip_permission_denied
                                               );
        
        for(const auto& p :
                fs::recursive_directory_iterator(root, options)){
            try{
                if(!p.is_directory()){
                    auto name = std::string(p.path().filename());
                
                    if(std::regex_search(name, self_regex)){

                        std::cout << "file name: " << name << std::endl;
                        std::cout << "file size: " << HumanReadable{p.file_size()} << std::endl;
                        std::cout << "file path: " << p.path() << std::endl ;
                    
                        //From: https://stackoverflow.com/questions/56788745/how-to-convert-stdfilesystemfile-time-type-to-a-string-using-gcc-9
                    
                        auto lwtime = p.last_write_time();
                    
                        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>
                            (lwtime - decltype(lwtime)::clock::now() + std::chrono::system_clock::now());

                        std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
                    
                        std::cout << "file last modified: " <<
                            std::asctime(std::localtime(&cftime)) << std::endl;
                    

                    }
                }
            }catch(std::filesystem::filesystem_error &fse){
                //We are going to ignore this...
                //std::cout << "Caught fatal exception: "
                //          << std::endl
                //          << fse.what()
                //          << std::endl;
            }
        }
    }
}

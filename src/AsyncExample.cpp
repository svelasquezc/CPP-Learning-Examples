#include <future>
#include <mutex>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>

std::mutex mutex;

template <typename RandomIt>
RandomIt parallel_linear_search(RandomIt begin, RandomIt end, const typename RandomIt::value_type& value, int& thread_count){
    
    auto size = end - begin;
    
    if(size < 1000) return std::find(begin, end, value);
    
    RandomIt middle = begin + size/2;
    
    {
        std::lock_guard<std::mutex> lk(mutex);
        ++thread_count;
        std::cout << "Creating thread (" << thread_count << ") with async\n";
    }
    
    auto handle = std::async(std::launch::async,
                             [&](){
                                 return parallel_linear_search<RandomIt>(middle, end, value, thread_count);
                             });
    RandomIt pos = parallel_linear_search(begin, middle, value, thread_count);
    
    auto pos2 = handle.get();
    
    if(pos2 != end)
        return pos2;
    if(pos != middle)
        return pos;
    return end;
}



template <typename RandomIt>
int parallel_linear_search(RandomIt begin, RandomIt end, const typename RandomIt::value_type& value){
    int thread_count = 0;
    RandomIt pos = parallel_linear_search(begin, end, value, thread_count);
    if(pos == end) return -1;
    return static_cast<int>(std::distance(begin, pos));
}


int main(int argc, char* argv[]){

    
    
    if(argc > 2){
        auto data = std::string(argv[1]);
        std::stringstream reader(data);
        std::vector<int> vec(50000, 1);
        
        std::size_t index = 0;
        int value = 0;
        reader >> index;
        data = std::string(argv[2]);
        reader = std::stringstream(data);
        reader >> value;

        std::cout << "Reading index: " << index <<" and value: " << value << "\n";

        vec[index] = value;

        int found_pos = parallel_linear_search(vec.begin(), vec.end(), value);

        if(found_pos == -1){
            std::cout << "Value was not found.\n";
        }else{
            std::cout << "Value: " << vec[found_pos] << " was found in position: " << found_pos << ".\n";
        }
        
    }
    
    
    std::string message("Working with async");

    
    
    auto result = std::async(std::launch::deferred, [message = std::ref(message)](){
                                                     std::lock_guard<std::mutex> lock(mutex);
                                                     //TypeDescriptor<decltype(message)> td;
                                                     std::cout << message.get() << std::endl;
                                                 });
    result.wait();
}

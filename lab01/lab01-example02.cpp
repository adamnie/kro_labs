#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

template <typename T>
void send_item(T item) {
      std::cout << item << std::endl;
}

std::map<std::string, int> get_map(void){
    return {
        { "there", 4 },
        { "are",   3 },
        { "four",  5 },
        { "words", 6 },
    };
}

int main(int argc, char const *argv[]) {
      std::vector<int> arr = {12, 33, 42, 67};
      if (auto it = find(std::begin(arr), std::end(arr), 33); it != arr.end()) { send_item(*it); }
      for(auto& [k,v]: get_map()) std::cout << "key=" << k << ", value=" << v << std::endl;
      return 0;
}

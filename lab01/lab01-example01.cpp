#include <algorithm>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

template <typename T>
concept bool Integral = std::is_integral_v<T>;
template <typename T>
concept bool SignedIntegral = Integral<T> && std::is_signed_v<T>;
template <SignedIntegral T>
void send_item(T item) {
  	std::cout << item << std::endl;
}
template <typename Filt, typename Arr>
void send_measures(Arr &&arr, Filt filt) {
  	arr.erase(std::remove_if(std::begin(arr), std::end(arr), filt), std::end(arr));
  	std::sort(std::begin(arr), std::end(arr));
  	std::for_each(std::begin(arr), std::end(arr), send_item<typename Arr::value_type>);
}

int main(int argc, char const *argv[]) {
  	std::vector<unsigned int> arr = {12, 33, 42, 67};
  	send_measures(std::move(arr), [](auto i) { return i <= 23; });
  	return 0;
}





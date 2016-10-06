#include <algorithm>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>
#include <random>

template <typename T>
concept bool Integral = std::is_integral<T>::value;
template <typename T>
concept bool SignedIntegral = Integral<T> && std::is_signed<T>::value;
template <SignedIntegral T>
void send_item(T item) {
  	std::cout << item << std::endl;
}
template <typename Filt, typename Arr>
void send_measures(Arr &&arr, Filt filt) {

  	// arr.erase(std::remove_if(std::begin(arr), std::end(arr), filt), std::end(arr));
  	std::sort(std::begin(arr), std::end(arr));
    /*
      Chyba nie o to chodziło, bo jak się poda za typ vectora unsigned, to program dalej się wysypuje,
      ale szczerze mówiąc nie rozumiem jak ma to działać przy użyciu filtra i z zachowaniem template
      na funkcji send_item.
    */
    if(std::all_of(std::begin(arr), std::end(arr), filt)){
  	   std::for_each(std::begin(arr), std::end(arr), send_item<typename Arr::value_type>);
    }
}

auto RandomlySeededMersenneTwister () {
    // Magic number 624: The number of unsigned ints the MT uses as state
    std::vector<unsigned int> random_data(624);
    std::random_device source;
    std::generate(begin(random_data), end(random_data), [&](){return source();});
    std::seed_seq seeds(begin(random_data), end(random_data));
    std::mt19937 seededEngine (seeds);
    return seededEngine;
}

int main(int argc, char const *argv[]) {
  	std::vector<int> arr(10000);

    auto rng = RandomlySeededMersenneTwister();

    for_each(begin(arr), end(arr), [&rng](auto& el){
      el = rng();
    });


  	send_measures(std::move(arr), [](auto i) { return SignedIntegral<decltype(i)>; });
  	return 0;
}

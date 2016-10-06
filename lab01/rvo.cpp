#include <iostream>
#include <vector>

std::vector<int> testNRVO(int value, size_t size, const std::vector<int> **localVec)
{
   std::vector<int> vec(size, value);

   *localVec = &vec;

   /* Do something here.. */

   return vec;
}

int main()
{
   const std::vector<int> *localVec = nullptr;

   std::cout << &localVec << std::endl;
   std::cout << localVec << std::endl;
  //  std::cout << *localVec << endl;

   std::vector<int> vec = testNRVO(123123, 100000000, &localVec);

   std::cout << &localVec << std::endl;
   std::cout << localVec << std::endl;

   if (&vec == localVec)
      std::cout << "NRVO was applied" << std::endl;
   else
      std::cout << "NRVO was not applied" << std::endl;
}

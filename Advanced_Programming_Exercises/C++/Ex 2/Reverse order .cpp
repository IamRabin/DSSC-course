/**
 * Write a program that reads from stdin the length of an array and then store in
 * it the numbers given from stdin. The program should then prints the numbers
 * in reverse order. Remember to properly free the used memory. You should divide
 * the problem in two parts:
 *  1. Write one template function that allocates on the heap one array of a
 *  given size, initialize its elements and returns the pointer to the first element.

 2.Write a template function that prints the elements of an array in the reverse
  order.Test with integers and doubles.
 */

 #include<iostream>
 #include"reverse_order.hpp"


 template <typename T>
 T* myarray(int size)
 {
     T * array{new T[size]};
     for(int i{0}; i < size; ++i)
     {
         std::cout << "Enter your numbers " << i + 1 << " of the array:" << std::endl;
         std::cin >> array[i];
     }

     return array;
 }

 template <typename T>
 void myarrayInReverse(T* array, int size)
 {
     for(int i{size - 1}; i >= 0; --i)
     {
         std::cout << "array[" << i << "] = " << array[i] << std::endl;
     }
     delete[] array;
 }

 int main()
 {
   int size;
   std::cout << " insert  size of your array:" << std::endl;
   std::cin >> size;
   int * intptr = myarray<int>(size);
   myarrayInReverse(intptr, size);
   double * doubleptr = myarray<double>(size);
   myarrayInReverse(doubleptr, size);
   return 0;
 }

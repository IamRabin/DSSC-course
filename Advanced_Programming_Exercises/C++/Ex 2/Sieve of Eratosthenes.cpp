/**
 *Implement the Sieve of Eratosthenes algorithm. Write a code that prints on screen
 * the first prime numbers up to N included, where N is read from stdin.
 *The first prime number that should be printed is 2.
 */

#include <iostream>
#include <cmath>


int main()
{

    std::cout << "insert your number: ";
    std::cin >> container;

    int container{0};3

    bool * primeptr{new bool[container]};
    std::fill(primeptr + 1, primeptr + container, true); // exclude 1

    for (int i{2}; i <= std::sqrt(container); i++)
    {
        if (primeptr[i - 1]) //only prime numbers
        {
            for (int j{i * i}; j <= container; j+=i)
            {
                primeptr[j - 1] = false; // multiples of i cannot be prime numbers
            }
        }
    }

    for (int i{1}; i <= container; i++)
    {
        if (primeptr[i - 1])
            std::cout << i << std::endl;
    }

    return 0;
}

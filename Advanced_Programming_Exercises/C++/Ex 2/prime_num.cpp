/**
Populate an array named primes containing the first prime numbers up to 100.
Consider 2 as the first prime (i.e. primes[0] == 2).
you are free to choose the design and the implementation.
please comment and motivate your choices
(e.g., allocate one big array or every time I find a new prime number
I increase the size of the previous primes array, etc.)
 */

const int SIZE = 100; //prime number up to 100.


int main()
{
    //  SIZE / 2 is the array size .

    int * primeptr{new int[SIZE / 2]};
    int count{0};

    for (int  i{2}; i < SIZE; ++i)
    {
        bool  prime{true};
        for (int  j{2}; j < i; ++j)
        {
            if (i % j == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (prime)
        {
            primeptr[count++] = i;
        }
    }

    return 0;
}

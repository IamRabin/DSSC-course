/**
 * Store the numbers contained in file temperatures.txt into an std::vector<double>
 * and compute:the mean the median
Hints:
use push_back()
you can increment a variable using += operator
you can sort the elements of a vector v as follows
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>


/**
    container  takes in filename and returns std::vector containing
    filenames.
*/
const std::vector<double> container(std::string filename)
{
    double value = 0.0;
    std::ifstream file(filename);
    std::string line;
    std::vector<double> num_holder;

    while (file >> value)
    {
        num_holder.push_back(value);
    }

    return num_holder;
}

/**
    Computes the mean for a vector of num_holder

*/
const double mean(std::vector<double> num_holder)
{
    double total = 0.0;

    for (double val : num_holder)
    {
        total += val;
    }

    return total / num_holder.size();
}

/**
    Computes the median for a vector of num_holder

*/
const double median(std::vector<double> num_holder)
{
    std::sort(num_holder.begin(), num_holder.end());
    int size = num_holder.size();
    double median;
    if (size % 2 == 0 )
    {
        median = (num_holder[size / 2] + num_holder[(size / 2) - 1]) / 2.0;
    }
    else
    {
        median = num_holder[size / 2];
    }
    return median;
}



int main()
{
    std::vector<double> temp = container("temperatures.txt");
    std::cout << "Mean: " << mean(temp) << std::endl;
    std::cout << "Median: " << median(temp) << std::endl;
    return 0;
}

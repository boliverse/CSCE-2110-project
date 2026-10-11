#include "Sorting.h"

namespace
{
    bool comesBefore(const std::pair<int, std::string>& a,
                     const std::pair<int, std::string>& b)
    {
        if (a.first != b.first)
        {
            return a.first > b.first; 
        }

        return a.second < b.second;   
    }

    
    void mergeRanges(
        std::vector<std::pair<int, std::string>>& values,
        std::vector<std::pair<int, std::string>>& temporary,
        std::size_t left,
        std::size_t middle,
        std::size_t right)
    {
        std::size_t i = left;
        std::size_t j = middle;
        std::size_t output = left;

        while (i < middle && j < right)
        {
            if (comesBefore(values[j], values[i]))
            {
                temporary[output++] = values[j++];
            }
            else
            {
                temporary[output++] = values[i++];
            }
        }

        while (i < middle)
        {
            temporary[output++] = values[i++];
        }

        while (j < right)
        {
            temporary[output++] = values[j++];
        }

        for (std::size_t index = left; index < right; ++index)
        {
            values[index] = temporary[index];
        }
    }

    
    void mergeSort(
        std::vector<std::pair<int, std::string>>& values,
        std::vector<std::pair<int, std::string>>& temporary,
        std::size_t left,
        std::size_t right)
    {
        if (right - left < 2)
        {
            return;
        }

        const std::size_t middle = left + (right - left) / 2;

        mergeSort(values, temporary, left, middle);
        mergeSort(values, temporary, middle, right);
        mergeRanges(values, temporary, left, middle, right);
    }
}

namespace Sorting
{
    void sortResourceCounts(
        std::vector<std::pair<int, std::string>>& counts)
    {
        if (counts.size() < 2)
        {
            return;
        }

        std::vector<std::pair<int, std::string>> temporary(counts.size());
        mergeSort(counts, temporary, 0, counts.size());
    }
}

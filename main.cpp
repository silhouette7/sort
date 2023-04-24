#include <vector>
#include <iostream>
#include <algorithm>

#include "sort.h"

void sortVec(std::vector<int> &vec, deric_sort::sortAlgorithm_e algorithm_) {
    std::shared_ptr<deric_sort::sortAlgorithmFactory> pFactory(new deric_sort::sortAlgorithmFactory());
    std::shared_ptr<deric_sort::sortAlgorithm> pSort = pFactory->getSortAlgorithm(algorithm_);
    if(pSort) {
        std::shared_ptr<deric_sort::sortContext> pContext(new deric_sort::sortContext(pSort));
        pContext->sort(vec);
    }
    else {
        std::cout << "ERRL pSort is null" << std::endl;
    }

}

int main(int argc, char* argv[])
{
    if(argc < 1) {
        std::cout << "ERR: not number input" << std::endl;
    }
    else {
        std::vector<int> vec;
        std::for_each(&argv[1], argv + argc, [&vec](char* c){(vec.push_back(std::stoi(c)));});

        std::cout << "original vec: " << std::endl;
        std::for_each(vec.begin(), vec.end(), [](int a){std::cout << a << " ";});
        std::cout << std::endl;

        sortVec(vec, deric_sort::SORT_ALGORITHM_QUICK);
        std::cout << "sort result: " << std::endl;
        std::for_each(vec.begin(), vec.end(), [](int a){std::cout << a << " ";});
        std::cout << std::endl;
    }

    return 0;
}
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

#include "sort.h"

namespace deric_sort
{
    sortContext::sortContext(std::shared_ptr<sortAlgorithm> algorithm) :
        m_algorithm(algorithm) {
    }

    void sortContext::sort(std::vector<int> &vec) {
        if(m_algorithm) {
            m_algorithm->sort(vec);
        }
    }

    sortAlgorithmFactory::sortAlgorithmFactory() {
    }

    std::shared_ptr<sortAlgorithm> sortAlgorithmFactory::getSortAlgorithm(sortAlgorithm_e sortAlgorithmType) {
        switch(sortAlgorithmType) {
            case SORT_ALGORITHM_BUBBLE:
                return std::shared_ptr<sortAlgorithm>(new bubbleSortAlgorithm());
            case SORT_ALGORITHM_INSERT:
                return std::shared_ptr<sortAlgorithm>(new insertionSortAlgorithm());
            case SORT_ALGORITHM_SHELL:
                return std::shared_ptr<sortAlgorithm>(new shellSortAlgorithm());
            case SORT_ALGORITHM_HEAP:
                return std::shared_ptr<sortAlgorithm>(new heapSortAlgorithm());
            case SORT_ALGORITHM_MERGE:
                return std::shared_ptr<sortAlgorithm>(new mergeSortAlgorithm());
            case SORT_ALGORITHM_QUICK:
                return std::shared_ptr<sortAlgorithm>(new quickSortAlgorithm());
            default:
                std::cout << "unknowed type" << std::endl;
                return nullptr;
        }
    }

    void bubbleSortAlgorithm::sort(std::vector<int> &vec) {
        int i, j;
        bool isChanged = false;
        for(i = vec.size() - 1; i > 0; --i) {
            isChanged = false;
            for(j = 0; j < i; ++j) {
                if(vec[j] > vec[j + 1]) {
                    isChanged = true;
                    std::swap(vec[j], vec[j + 1]);
                }
            }
            if(!isChanged) {
                break;
            }
        }
    }

    void insertionSortAlgorithm::sort(std::vector<int> &vec) {
        int tmp, i, j;
        for(i = 0; i < vec.size(); ++i) {
            tmp = vec[i];
            for(j = i; j > 0 && tmp < vec[j - 1]; --j) {
                vec[j] = vec[j - 1];
            }
            vec[j] = tmp;
        }
    }

    void shellSortAlgorithm::sort(std::vector<int> &vec) {
        int gap, tmp, i, j;
        for(gap = vec.size() / 2; gap > 0; gap /= 2) {
            for(i = gap; i < vec.size(); ++i) {
                tmp = vec[i];
                for(j = i; j >= gap && tmp < vec[j - gap]; j -= gap) {
                    vec[j] = vec[j - gap];
                }
                vec[j] = tmp;
            }
        }
    }

    void heapSortAlgorithm::sort(std::vector<int> &vec) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        int i;
        for(int num : vec) {
            pq.push(num);
        }
        i = 0;
        while(!pq.empty()) {
            vec[i++] = pq.top();
            pq.pop();
        }
    }

    void mergeSortAlgorithm::sort(std::vector<int> &vec) {
        std::vector<int> _bufVec(vec.size());
        int targetLen = 2;
        int i = 0;
        for(targetLen = 2; targetLen / 2 < vec.size(); targetLen *= 2) {
            for(i = 0; i + targetLen - 1  < vec.size(); i += targetLen) {
                merge(vec, i, i + targetLen / 2, i + targetLen - 1, _bufVec);
            }
            if(i + targetLen / 2 < vec.size()) {
                merge(vec, i, i + targetLen / 2, vec.size() - 1, _bufVec);
            }
        }
    }

    void mergeSortAlgorithm::merge(std::vector<int> &in_vec, int leftBegin, int rightBegin, int end, std::vector<int> &buffer_vec) {
        int i = leftBegin, j = rightBegin, index = leftBegin;
        while(i < rightBegin && j <= end) {
            if(in_vec[i] <= in_vec[j]) {
                buffer_vec[index++] = in_vec[i];
                ++i;
            }
            else {
                buffer_vec[index++] = in_vec[j];
                ++j;
            }
        }
        for(; i < rightBegin; ++i) {
            buffer_vec[index++] = in_vec[i];
        }
        for(; j <= end; ++j) {
            buffer_vec[index++] = in_vec[j];
        }

        for(i = leftBegin; i <= end; ++i) {
            in_vec[i] = buffer_vec[i];
        }
    }

    void quickSortAlgorithm::sort(std::vector<int> &vec) {
        quickSort(vec, 0, vec.size()-1);
    }

    int quickSortAlgorithm::findPivotBymedian3(std::vector<int> &vec, int left, int right) {
        if(left == right) {
            return vec[left];
        }

        int mid = left + (right - left) / 2;
        if(vec[left] > vec[right]) {
            std::swap(vec[left], vec[right]);
        }
        if(vec[left] > vec[mid]) {
            std::swap(vec[left], vec[mid]);
        }
        if(vec[mid] > vec[right]) {
            std::swap(vec[mid], vec[right]);
        }
        std::swap(vec[mid], vec[right - 1]);

        return vec[right - 1];
    }

    void quickSortAlgorithm::quickSort(std::vector<int> &vec, int left, int right) {
        if(left >= right) {
            return;
        }
        int pivot = findPivotBymedian3(vec, left, right);
        int i = left, j = right - 1;
        while(i < j) {
            while(vec[++i] < pivot) {}
            while(vec[--j] > pivot) {}
            if(i < j) {
                std::swap(vec[i], vec[j]);
            }
        }
        std::swap(vec[i], vec[right-1]);

        quickSort(vec, left, i - 1);
        quickSort(vec, i + 1, right);
    }
}
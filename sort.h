#include <vector>
#include <memory>

namespace deric_sort
{

typedef enum{
    SORT_ALGORITHM_BUBBLE,
    SORT_ALGORITHM_INSERT,
    SORT_ALGORITHM_SHELL,
    SORT_ALGORITHM_HEAP,
    SORT_ALGORITHM_MERGE,
    SORT_ALGORITHM_QUICK
}sortAlgorithm_e;

class sortAlgorithm
{
public:
    virtual void sort(std::vector<int> &vec) = 0;
};

class bubbleSortAlgorithm : public sortAlgorithm
{
public:
    virtual void sort(std::vector<int> &vec);
};

class insertionSortAlgorithm : public sortAlgorithm
{
public:
    virtual void sort(std::vector<int> &vec);
};

class shellSortAlgorithm : public sortAlgorithm
{
public:
    virtual void sort(std::vector<int> &vec);
};

class heapSortAlgorithm : public sortAlgorithm
{
public:
    virtual void sort(std::vector<int> &vec);
};

class mergeSortAlgorithm : public sortAlgorithm
{
public:
    virtual void sort(std::vector<int> &vec);
private:
    void merge(std::vector<int> &in_vec, int leftBegin, int rightBegin, int end,std::vector<int> &buffer_vec);
};

class quickSortAlgorithm : public sortAlgorithm
{
public:
    virtual void sort(std::vector<int> &vec);
private:
    int findPivotBymedian3(std::vector<int> &vec, int left, int right);
    void quickSort(std::vector<int> &vec, int left, int right);
};

class sortContext
{
public:
    sortContext(std::shared_ptr<sortAlgorithm> algorithm);
    void sort(std::vector<int> &vec);

private:
    std::shared_ptr<sortAlgorithm> m_algorithm;
};

class sortAlgorithmFactory
{
public:
    sortAlgorithmFactory();
    std::shared_ptr<sortAlgorithm> getSortAlgorithm(sortAlgorithm_e sortAlgorithmType);
};

}
#include "Heap.h"
#include "qSortKthCut.h"

#define HEAP_TYPE 1
#define KTHM_TYPE 0

template <typename T>
class TTopElements {
private:
    Heap < T > heap;
    qSortKthCut < T > cut;
    int type;
public:
    TTopElements(size_t topSize, int _type = KTHM_TYPE);
    void Add(const T & elem);
    ostream& GetCurrentTop();
}

TTopElements::TTOpElements(int topSize, int _type): type(_type) {
    if (type == HEAP_TYPE) heap(topSize);
    if (type == KTHM_TYPE) qSortKthCut(topSize);
}

void TTopElements::Add(const T & elem) {
    if (type == HEAP_TYPE) heap.addPoint(elem);
    if (type == KTHM_TYPE) qSortKthCut.addPoint(elem);
}

ostream& TTopElements::GetCurrentTop(ostream &out) {
    if (type == HEAP_TYPE) out << heap.out();
    if (type == KTHM_TYPE) out << qSortKthCut.out();
}

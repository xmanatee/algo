#ifndef _SEGMENTTREE_H_
#define _SEGMENTTERE_H_

#include <vector>
#include <ostream>

template <typename T>
class SegmentTree {
public:
    int size;
    int real_size;
    std::vector<T> data;
    SegmentTree(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        real_size = 2 * size - 1;
        data.resize(real_size);
    }

    void update(int id) {
        data[id] = data[2 * id + 1] + data[2 * id + 2];
    }

    bool isLeaf(int id) {
        return id >= size - 1;
    }

    int iToId(int i) {
        return i + size - 1;
    }

    void add(int i, T x) {
        int id = iToId(i);
        data[id] += x;
        while (id != 0) {
            id = (id - 1) / 2;
            update(id);
        }
    }

    int getSth(T x) {
        int id = 0;
//        cerr << "in " << id << endl;
        while (!isLeaf(id)) {
            int lId = 2 * id + 1;
            if (data[lId] >= x) {
                id = lId;
            } else {
                x -= data[lId];
                id = lId + 1;
            }
//            cerr << "in " << id << endl;
        }
        return id - size + 1;
    }
};

template<typename T>
std::ostream& operator << (std::ostream& out, SegmentTree<T> tree) {
    int levelSize = 2;
    out << "SegTree(n=" << tree.size << ") :" << std::endl;
    for (int i = 0; i < tree.real_size; ++i) {
        out << tree.data[i] << " ";
        if (i == levelSize - 2) {
            out << std::endl;
            levelSize *= 2;
        }
    }
}


#endif // _SEGMENTTREE_H_
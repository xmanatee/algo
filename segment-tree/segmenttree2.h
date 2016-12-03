template <typename T>
class SegmentTree {
public:
    size_t size;
    size_t real_size;
    std::vector<T> data;
    explicit SegmentTree(size_t init_size) {
        size = 1;
        while (size < init_size) {
            size *= 2;
        }
        real_size = 2 * size - 1;
        data.resize(real_size);
    }

    void update(size_t id) {
        data[id] = data[2 * id + 1] + data[2 * id + 2];
    }

    bool isLeaf(size_t id) {
        return id >= size - 1;
    }

    size_t inToId(size_t in) {
        return in + static_cast<int>(size) - 1;
    }

    size_t idToIn(size_t id) {
        return id - static_cast<int>(size) + 1;
    }

    void add(size_t in, T sum) {
        size_t id = inToId(in);
        data[id] += sum;
        while (id != 0) {
            id = (id - 1) / 2;
            update(id);
        }
    }

    size_t getSth(T sum) {
        size_t id = 0;
        while (!isLeaf(id)) {
            size_t lId = 2 * id + 1;
            if (data[lId] >= sum) {
                id = lId;
            } else {
                sum -= data[lId];
                id = lId + 1;
            }
        }
        return idToIn(id);
    }

    T getRoot() {
        return data[0];
    }
};

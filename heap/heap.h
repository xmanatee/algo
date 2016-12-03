template<class T>
class Heap {
 public:
    void put(const T& item) {
        data.push_back(item);
        int id = data.size() - 1;
        while (heapify(id)) {
            id = up(id);
        }
    }

    T popMin() {
        assert(!data.empty());
        T answer = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            pull(0);
        }
        return answer;
    }

    bool empty() {
        return data.empty();
    }

 private:    
    std::vector<T> data;

    int up(int id) {
        return (id - 1) / 2;
    }

    int downL(int id) {
        return 2 * id + 1;
    }

    int downR(int id) {
        return 2 * id + 1;
    }

    bool heapify(int id) {
        if (data[id] > data[up(id)]) {
            std::swap(data[id], data[up(id)]);
            return true;
        }
        return false;
    }

    void pull(int id) {
        if (downL(id) >= data.size()) {
            return;
        }
        if (downR(id) >= data.size()) {
            if (data[downL(id)] < data[id]) {
                std::swap(data[id], data[downL(id)]);
            }
            return;
        }
        if (data[id] < std::min(data[downL(id)], data[downR(id)])) {
            return;
        }
        int childId = downR(id);
        if (data[downL(id)] < data[downR(id)]) {
            childId = downL(id);
        }
        std::swap(data[id], data[childId]);
        pull(childId);
    }
};

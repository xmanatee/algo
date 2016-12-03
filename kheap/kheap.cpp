template <typename T>
class KHeap {
private:
    vector<T> data;
    int k;
public:
    KHeap(const T _k): k(_k) { }
    void add(const T x) {
        data.push_back(x);
        int it = data.size() - 1;
        while ((it != 0) && (data[it] < data[(it - 1) / k])) {
            swap(data[it], data[(it - 1) / k]);
            it = (it - 1) / k;
        }
    }
    T get_min() {
        return data[0];
    }
    void drop_min() {
        int s = data.size();
        swap(data[0], data[s - 1]);
        int it = 0;
        while (it * k + 1 <= s) {
            int minid = it * k + 1;
            for (int i = 2; i <= k , it * k + i < s; i++) {
                int hypo = it * k + i;
                if (data[hypo] < data[minid]) minid = hypo;
            }
            swap(data[it], data[minid]);
            it = minid;
        }
        data.pop_back();
    }
};

template <typename T>
class qSortKthCut {
private:
    vector < T > elements;
    int edge;
    int size;
public:
    qSortKthCut(int _edge) edge(edge), size(0) { }
    int qSortSplitter();
    void cut(int n);
    void addPoint(const T & n);
}

int qSortKthCut::qSortSplitter() {
    if (size <= k) return -1;
    int left = 0;
    int right = size - 1;
    while (1) {
        int i = left;
        int j = right;
        int median = elements[(i + j) / 2];
        while (i <= j) {
            while (elements[i] < m) ++i;
            while (m < elements[j]) --j;
            if (i <= j) {
                swap(elements[i], elements[j]);
                ++i;
                --j;
            }
        }
        if ((i == k) && (j == k)) return k;
        if (k < j) r = j;
        if (i < k) l = i;
    }
}

void qSortKthCut::cutN(int n) {
    for (int i = size; i >= N; i--)
        elements.pop_back();
    size = edge;
}

void addPoint(const T & n) {
    elements.push_back(n);
    size++;
    if (size > 2 * k)
        cutN(qSortSplitter());
}

void out() {
    cutN(qSortSplitter());
    for (int i = 0; i < edge; i++) {
        cout << elements[i] << " ";
    }
}

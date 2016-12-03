template <typename T>
class Heap {
private:
    vector < T > elements;
    int edge;
    int size;
public:
    Heap(int _edge): edge(edge) {
        size = 0;
        elements.push_back(T());
    }
    T getMinimum();
    void removeMinimum();
    T cutMinimum();
    void addPoint(const T & n);
};

template <typename T>
T Heap<T>::getMinimum() {
    return elements[1];
}

void Heap<T>::removeMinimum() {
    elements[1] = elements[size];
    --size;
    int currentPoint = 1;
    while (1) {
        if (2 * currentPoint > size) break;
        if (2 * currentPoint == size) {
            if (elements[currentPoint] > elements[2 * currentPoint]) {
                swap(elements[currentPoint], elements[2 * currentPoint]);
                break;
            }
        }

        int leastPoint = 2 * currentPoint;
        if (elements[2 * currentPoint + 1] < elements[2 * currentPoint]) ++leastPoint;

        if (elements[leastPoint] < elements[currentPoint])
            swap(elements[leastPoint], elements[currentPoint]);
    }
}

T Heap<T>::cutMinimum() {
    T answer = getMinimum();
    removeMinimum();
    return answer;
}

void addPoint(const T & n) {
    int currentPoint = 0;
    if (k == size + 1) {
        elements[size + 1] = n;
        currentPoint = size + 1;
    }
    else {
        ++size;
        elements[size] = n;
        currentPoints = size;
    }

    while (elements[currentPoint] < elements[currentPoint / 2]) currentPoint /= 2;
}


void out() {
    for (int i = 1; i <= edge; i++)
    cout << cutMinimum << " ";
}


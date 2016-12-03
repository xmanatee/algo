class segment {
public:
    int beg;
    int len;
    bool type;
    segment(){}
    segment(int b, int l) : beg(b), len(l){}
};

inline int get_min_run(int n) {
    int r = 0;
    while (n >= 64) {
        n >>= 1;
        r |= n &1;
    }
    return n + r;
}

void insertion_sort(vector <int> &arr, int left, int right, bool grows) {
    if (grows) {
        for (int i = left + 1; i < right; ++i) {
            int j = i;
            while ((j > left) && (arr[j - 1] > arr[j])) {
                swap(arr[j], arr[j - 1]);
                --j;
            }
        }
    }
    else {
        for (int i = left + 1; i < right; ++i) {
            int j = i;
            while ((j > left) && (arr[j - 1] < arr[j])) {
                swap(arr[j], arr[j - 1]);
                --j;
            }
        }
        reverse(arr.begin() + left, arr.begin() + right);
    }
}

void split(vector <int> & arr, vector <segment> segs, int min_run) {
    int last = 0;

    while (last < arr.size()) {
        segment current_seg(last, min(min_run, (int)arr.size() - last));
        bool grows = (arr[last] <= arr[last + 1]);
        int run = 2;
        while ((current_seg.beg + run < arr.size()) && !((grows) ^ (arr[current_seg.beg + run - 1] <= arr[current_seg.beg + run])))
            ++run;
        if (run <= min_run)
            run = min(min_run, (int)arr.size() - last);

        current_seg.len = run;
        last = last + run;
        current_seg.len = run;
        current_seg.type = grows;
        segs.push_back(current_seg);
    }
}

void timsort(vector<int> &mas) {
    int n = mas.size();
    int min_run = get_min_run(n);
    int beg = 0;
    vector <segment> seg;
    seg.reserve((n - 1) / min_run + 1);
    split(mas, seg, min_run);

    for (int i = 0; i < seg.size(); ++i) {
        insertion_sort(mas, seg[i].beg, seg[i].beg + seg[i].len, seg[i].type);
    }

    segment z = seg[0];
    segment y = seg[1];
    segment x;
    int segid = 2;
    while (segid < seg.size()) {
        x = seg[segid];
        if ((x.len > y.len + z.len) && (y.len > z.len)) {
            inplace_merge(mas.begin() + y.beg, mas.begin() + x.beg, mas.begin() + x.beg + x.len);
            x.beg = y.beg;
            x.len = x.len + y.len - 1;
            y = z;
        }
        else {
            if (x.len < y.len) {
                inplace_merge(mas.begin() + y.beg, mas.begin() + x.beg, mas.begin() + x.beg + x.len);
                x.beg = y.beg;
                x.len = x.len + y.len - 1;
                y = z;
            }
            else {
                inplace_merge(mas.begin() + z.beg, mas.begin() + y.beg, mas.begin() + y.beg + y.len);
                y.beg = z.beg;
                y.len = y.len + z.len - 1;
            }
        }
        ++segid;
    }
    inplace_merge(mas.begin() + y.beg, mas.begin() + x.beg, mas.begin() + x.beg + x.len);
}

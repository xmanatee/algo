#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

class SubString {
public:
    int l, r;
    string *s;
    SubString(string &_s, int _l, int _r): l(_l), r(_r), s(&_s) {}

    int length() {
        return r - l;
    }

    char operator [] (unsigned int id) {
        return s->at(l + id);
    }
};

int compareSubStrings(SubString *a, SubString *b) {
    int m = std::min(a->length(), b->length());
    for (int i = 0; i < m; ++i) {
        if ((*a)[i] > (*b)[i]) {
            return 1;
        } else if ((*a)[i] < (*b)[i]) {
            return -1;
        }
    }
    return a->length() - b->length();
}


bool lessSubString(SubString *a, SubString *b) {
    return compareSubStrings(a, b) < 0;
}

int main() {
    string s;
    cin >> s;
    s += '$';
    int n = s.length();

    vector<SubString*> vs(n);
    for (int i = 0; i < n; ++i) {
        vs[i] = new SubString(s, i, n);
    }
    //cerr << compareSubStrings(vs[0], vs[1]);

    sort(vs.begin(), vs.end(), lessSubString);
    //qsort(vs.data(), n, sizeof(SubString), compareSubStrings);

    vector<int> z;
    z.push_back(vs.size());
    for (int i = 1; i < vs.size(); ++i) {
        z.push_back(vs[i]->l);
    }

    for (int i = 1; i < vs.size(); ++i) {
        cout << vs[i]->l << "\t";
    }
    cout << "\n";
}
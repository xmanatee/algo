#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <ctime>

using namespace std;

class SubVector {
public:
    int l, r;
    vector<int> *s;
    SubVector(vector<int> &_s, int _l, int _r): l(_l), r(_r), s(&_s) {}

    int length() {
        return r - l;
    }

    int operator [] (unsigned int id) {
        return s->at(l + id);
    }
};

int compare(SubVector *a, SubVector *b, vector<bool> &t) {
    int m = std::min(a->length(), b->length());
    for (int i = 0; i <= m; ++i) {
        if ((*a)[i] > (*b)[i]) {
            return 1;
        } else if ((*a)[i] < (*b)[i]) {
            return -1;
        } else if (t[a->l + i] && !t[b->l + i]) {
            return 1;
        } else if (!t[a->l + i] && t[b->l + i]) {
            return -1;
        }
    }
    return a->length() - b->length();
}

ostream& operator << (ostream &out, SubVector *s) {
    out << "(";
    for (int i = s->l; i < s->r; ++i) {
        out << static_cast<char>('a' + s->s->at(i));
    }
    out << ")";
    return out;
}

namespace SuffixStructures {
    unsigned int DEFAULT_SIGMA = 256;

    class SuffixArray {
    private:
        vector<int> lTypeIter;
        vector<int> sTypeIter;
    public:
        SuffixArray(int sigma);
        void build(vector<int> &s, int sigma, vector<int> &sa);
        void initSIters(vector<int> &sTypeTails);
        void initLIters(vector<int> &lTypeHeads);
        void classify(vector<int> &s, vector<bool> &t);
        void findLMS(vector<int> &s, vector<bool> &t, vector<SubVector *> &p1, vector<int> &whichLMS);
        void induceSA(vector<int> &s, vector<bool> &t, vector<int> &sa1, vector<SubVector *> &p1, vector<int> &lTypeHeads, vector<int> &sTypeTails, vector<int> &sa);
        void induceLMSSort(vector<int> &s, vector<bool> &t, vector<SubVector *> &p1, vector<int> &lTypeHeads, vector<int> &sTypeTails, vector<int> &sa);
    };

    SuffixArray::SuffixArray(int sigma = DEFAULT_SIGMA) {
        lTypeIter.resize(sigma);
        sTypeIter.resize(sigma);
    }

    void SuffixArray::initSIters(vector<int> &sTypeTails) {
        sTypeIter.resize(sTypeTails.size());
        for (int i = 0; i < sTypeTails.size(); ++i) {
            sTypeIter[i] = sTypeTails[i];
        }
    }

    void SuffixArray::initLIters(vector<int> &lTypeHeads) {
        lTypeIter.resize(lTypeHeads.size());
        for (int i = 0; i < lTypeHeads.size(); ++i) {
            lTypeIter[i] = lTypeHeads[i];
        }
    }

    void SuffixArray::classify(vector<int> &s, vector<bool> &t) {
        int n = s.size();
        t[n - 1] = true;
        for (int i = n - 2; i >= 0; --i) {
            if ((s[i] < s[i + 1]) || ((s[i] == s[i + 1]) && (t[i + 1]))) {
                t[i] = true;
            }
        }
    }

    void SuffixArray::findLMS(vector<int> &s, vector<bool> &t, vector<SubVector *> &p1, vector<int> &mapToLMS) {
        int prev = 1;
        while (!t[prev] || t[prev - 1]) ++prev;
        for (int i = prev + 1; i < s.size(); ++i) {
            if (t[i] && !t[i - 1]) {
                p1.push_back(new SubVector(s, prev, i));
                prev = i;
            }
        }
        p1.push_back(new SubVector(s, s.size() - 1, s.size() - 1));

        for (int i = 0; i < p1.size(); ++i) {
            mapToLMS[p1[i]->l] = i;
        }
    }

    void initTailsAndHeads(vector<int> &s, int sigma, vector<int> &lTypeHeads, vector<int> &sTypeTails) {
        vector<int> charCount(sigma);
        for (int i = 0; i < s.size(); ++i) {
            ++charCount[s[i]];
        }

        sTypeTails[0] = charCount[0] - 1;
        lTypeHeads[0] = 0;
        for (int i = 1; i < sigma; ++i) {
            lTypeHeads[i] = sTypeTails[i - 1] + 1;
            sTypeTails[i] = lTypeHeads[i] + charCount[i] - 1;
        }
    }

    void SuffixArray::induceSA(vector<int> &s,
                               vector<bool> &t,
                               vector<int> &sa1,
                               vector<SubVector *> &p1,
                               vector<int> &lTypeHeads,
                               vector<int> &sTypeTails,
                               vector<int> &sa) {
        int n = (int) s.size();
        initSIters(sTypeTails);

        for (int i = sa1.size() - 1; i >= 0; --i) {
            int start = p1[sa1[i]]->l;
            int c = s[start];
            sa[sTypeIter[c]--] = start;
        }

        initLIters(lTypeHeads);

        for (int i = 0; i < n; ++i) {
            if ((sa[i] > 0) && (!t[sa[i] - 1])) {
                int c = s[sa[i] - 1];
                sa[lTypeHeads[c]++] = sa[i] - 1;
            }
        }

        initSIters(sTypeTails);

        for (int i = n - 1; i >= 0; --i) {
            if ((sa[i] > 0) && (t[sa[i] - 1])) {
                int c = s[sa[i] - 1];
                sa[sTypeTails[c]--] = sa[i] - 1;
            }
        }
    }

    void SuffixArray::induceLMSSort(vector<int> &s,
                                    vector<bool> &t,
                                    vector<SubVector *> &p1,
                                    vector<int> &lTypeHeads,
                                    vector<int> &sTypeTails,
                                    vector<int> &sa) {

        int n = s.size();
        initSIters(sTypeTails);
        for (int i = 0; i < p1.size(); ++i) {
            int start = p1[i]->l;
            int c = s[start];
            sa[sTypeIter[c]--] = start;
        }

        initLIters(lTypeHeads);
        for (int i = 0; i < n; ++i) {
            if ((sa[i] > 0) && (!t[sa[i] - 1])) {
                int c = s[sa[i] - 1];
                sa[lTypeIter[c]++] = sa[i] - 1;
            }
        }

        initSIters(sTypeTails);
        for (int i = n - 1; i >= 0; --i) {
            if ((sa[i] > 0) && (t[sa[i] - 1])) {
                int c = s[sa[i] - 1];
                sa[sTypeIter[c]--] = sa[i] - 1;
            }
        }
    }

    void SuffixArray::build(vector<int> &s, int sigma, vector<int> &sa) {
        s.push_back(0);
        int n = s.size();
        sa.assign(n, -1);

        // determining the type
        vector<bool> t(n); // is S-type
        classify(s, t);

        // finding LMS - chars
        vector<SubVector *> p1;
        vector<int> mapToLMS(n, -1);
        findLMS(s, t, p1, mapToLMS);

        // induced sort all the LMS-substrings using P1 and B
        vector<int> lTypeHeads(sigma);
        vector<int> sTypeTails(sigma);
        initTailsAndHeads(s, sigma, lTypeHeads, sTypeTails);
        induceLMSSort(s, t, p1, lTypeHeads, sTypeTails, sa);

        vector<int> p1Sort;
        for (int i = 0; i < n; ++i) {
            if (mapToLMS[sa[i]] > -1) {
                p1Sort.push_back(mapToLMS[sa[i]]);
            }
        }

        int numBuckets = 0;
        vector<int> toBucketMap(p1.size());
        toBucketMap[p1Sort[0]] = numBuckets++;

        for (int i = 1; i < p1Sort.size(); ++i) {
            if (compare(p1[p1Sort[i - 1]], p1[p1Sort[i]], t) != 0) {
                ++numBuckets;
            }
            toBucketMap[p1Sort[i]] = numBuckets - 1;
        }

        sa.assign(n, -1);

        vector<int> sa1(p1.size());
        if (numBuckets == p1.size()) { // Each character in S1 is unique
            // Directly compute SA1 from S1
            for (int i = 0; i < p1.size(); ++i) {
                sa1[toBucketMap[i]] = i;
            }
        } else {
            // RECURSEVELY SORT (S1) -> SA1
            // Name each LMS-substring in S by its bucket index to get a new shortened string S1
            vector<int> s1;
            for (int i = 0; i < p1.size(); ++i) {
                s1.push_back(1 + toBucketMap[i]);
            }
            build(s1, numBuckets + 1, sa1);
        }

        //Induce SA from SA1

        induceSA(s, t, sa1, p1, lTypeHeads, sTypeTails, sa);

        for (int i = 1; i < sa.size(); ++i) {
            sa[i - 1] = sa[i];
        }
        sa.pop_back();
        s.pop_back();
    }

    void lcpFromSuffArray(vector<int> &s, vector<int> &sa, vector<int> &lcp) {
        int len = s.size();
        lcp.resize(len);
        vector<int> pos(len);

        for (int i = 0; i < len; ++i) {
            pos[sa[i]] = i;
        }

        int k = 0;
        for (int i = 0; i < len; ++i) {
            if (k > 0) {
                --k;
            }
            if (pos[i] == len - 1) {
                lcp[len - 1] = -1;
                k = 0;
            } else {
                int j = sa[pos[i] + 1];
                while (max(i + k, j + k) < len && s[i + k] == s[j + k]) {
                    ++k;
                }
                lcp[pos[i]] = k;
            }
        }
    }
};


class Word2Vec {
private:
    vector<int> charCount;
    vector<int> map;
    const unsigned long DEFAULT_SIGMA = 256;
public:
    unsigned int build(string &s, vector<int> &vec) {
        charCount.assign(DEFAULT_SIGMA, 0);
        map.assign(DEFAULT_SIGMA, 0);
        for (int i = 0; i < s.length(); ++i) {
            ++charCount[s[i]];
        }
        unsigned int numChars = 0;
        for (int i = 0; i < DEFAULT_SIGMA; ++i) {
            if (charCount[i] != 0) {
                map[i] = ++numChars;
            }
        }

        vec.clear();
        for (int i = 0; i < s.length(); ++i) {
            vec.push_back(map[s[i]]);
        }
        return numChars;
    }
};


#ifdef SPEED_TEST

string getRandomString(int n) {
    srand(13);
    string s = "";

    for (int i = 0; i < n; ++i) {
        s += char('a' + rand() % 26);
    }

    return s;
}

int main() {
    int n;
    cin >> n;
    string s = getRandomString(n);

    Word2Vec wv;
    SuffixStructures::SuffixArray suffArrayBuilder(256);

    cerr << "Word2Vec : " << clock() * 1.0 / CLOCKS_PER_SEC << "\n";
    vector<int> vecstr;
    int sigma = wv.build(s, vecstr) + 1;

    cerr << "SauffArr : " << clock() * 1.0 / CLOCKS_PER_SEC << "\n";
    vector<int> sa;
    suffArrayBuilder.build(vecstr, sigma, sa);

    cerr << "Outputtt : " << clock() * 1.0 / CLOCKS_PER_SEC << "\n";
    for (int i = 0; i < sa.size(); ++i) {
        cout << sa[i] << "\t";
    }
    cout << "\n";
    return 0;
}

#else

int segmentMin(int i, int j, vector <int> &lcp) {
    int ans = 1e9;
    for (int k = i; k < j; ++k) {
        ans = min(ans, lcp[k]);
    }
    return ans;
}

void timusAdvanced(string &str, int &k) {
    Word2Vec wv;
    vector<int> vecstr;
    int sigma = wv.build(str, vecstr) + 1;
    int len = vecstr.size();
    for (int i = 0; i < len; ++i) {
        vecstr.push_back(vecstr[i]);
    }
    vector<int> sa;
    vector<int> lcp;
    SuffixStructures::SuffixArray saBuilder(sigma);
    saBuilder.build(vecstr, sigma, sa);

    sa.push_back(0);
    for (int i = sa.size() - 1; i > 0; --i) {
        sa[i] = sa[i - 1];
    }
    sa[0] = sa.size() - 1;

    vector<int> saRev(sa.size());
    for (int i = 0; i < sa.size(); ++i) {
        saRev[sa[i]] = i;
    }

    vecstr.push_back(0);
    SuffixStructures::lcpFromSuffArray(vecstr, sa, lcp);

    for (int i = 0; i < len; ++i) {
        vector<pair<int, int>> ans;
        vector<int> s;
        for (int j = 0; j < k; j++) {
            ans.push_back(make_pair(saRev[i + j], j));
            s.push_back(vecstr[i + j]);
        }
        s.push_back(0);
        ans.push_back(make_pair(0, k));

        sort(ans.begin(), ans.end());

        int sum_lcp = 0;
        int cur_lcp = 0;
        int cur = 0;
        for (int j = 1; j < ans.size(); ++j) {
            int l = min(k - ans[j].second, k - ans[cur].second);
            cur_lcp = segmentMin(ans[cur].first, ans[j].first, lcp);
            sum_lcp += min(l, cur_lcp);
            if ((cur_lcp < k - ans[j].second) || (k - ans[j].second >= k - ans[cur].second)) {
                cur = j;
            }
        }
        cout << (k + 1) * k / 2 - sum_lcp << " ";
    }
    cout << "\n";
}

void timusStupid(string &str, int k) {
    int n = str.size();
    str = str + str;

    Word2Vec wv;
    vector<int> vecstr;

    int sk = k * (k + 1) / 2;

    SuffixStructures::SuffixArray suffArrayBuilder(k);
    for (int i = 0; i < n; ++i) {

        string sub = str.substr(i, k);
        int sigma = wv.build(sub, vecstr) + 1;

        vector<int> sa;
        suffArrayBuilder.build(vecstr, sigma, sa);

        vector<int> lcp;
        SuffixStructures::lcpFromSuffArray(vecstr, sa, lcp);

        int sum = 0;
        for (int j = 0; j < lcp.size(); ++j) sum += lcp[j];
        cout << sk - 1 - sum << " ";
    }
    cout << "\n";
}


int main() {
    int k;
    string s;
    cin >> k;
    cin >> s;

    timusAdvanced(s, k);
    return 0;
}

#endif
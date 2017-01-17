
#include"nvector.h"

using namespace numerica;
using namespace std;

ostream &tools::operator<<(ostream &out, const NVector &v) {
    for (size_t i = 0; i < v.size(); i++)
        out << v[i] << " ";
    out << endl;
    return out;
}

bool tools::operator==(const NVector &a, const NVector &b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i]) return false;
    return true;
}

bool tools::operator!=(const NVector &a, const NVector &b) {
    if (a.size() != b.size()) return true;
    valarray<bool> res = a != b;
    auto val = true;
    for (auto &e : res) {
        val &= e;
    }
    return val;
}

NVector tools::operator*(const NVector &lhs, int rhs) {

    NVector res = lhs;

    for (auto &item:res) {
        res *= rhs;
    }
    return res;
}
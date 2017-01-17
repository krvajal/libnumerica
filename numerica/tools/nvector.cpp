
#include"nvector.h"

using namespace numerica;
using namespace std;

ostream &tools::operator<<(ostream &out, const NVector &v) {
    for (size_t i = 0; i < v.size(); i++)
        out << v[i] << " ";
    out << endl;
    return out;
}


bool equals(const tools::NVector &a, const tools::NVector &b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i]) return false;
    return true;

}

bool tools::operator==(const NVector &a, const NVector &b) {

    return equals(a, b);
}


bool tools::operator!=(const NVector &a, const NVector &b) {


    return !equals(a, b);
}

tools::NVector tools::operator*(const NVector &lhs, int rhs) {

    NVector res = lhs;

    for (auto &item:res) {
        item *= rhs;
    }
    return res;
}
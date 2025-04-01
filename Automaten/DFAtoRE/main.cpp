#include <iostream>
#include "DFA.h"
using namespace std;

int main() {
    DFA dfa("../DFA1.json");
    dfa.toRE().print();
    return 0;
}

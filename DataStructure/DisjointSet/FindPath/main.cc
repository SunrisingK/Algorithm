#include <iostream>
#include "../DisjointSet.h"
using namespace std;


int main(int argc, char const* argv[]) {
    int n, m;
    cin >> n >> m;
    DisjointSet st(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        st.merge(a, b);
    }
    int source, destination;
    cin >> source >> destination;
    cout << st.isInSame(source, destination);
    return 0;
}
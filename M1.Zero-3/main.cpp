#include <iostream>
#include <map>
#include <cmath>

using std::cout,std::cin, std::map;

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int n;
    cin >> n;
    int buf,a,b;
    map <int,int> m;
    for(int i=0; i<n; ++i)
    {
        cin >> a >> b;
        auto ita = m.find(a);
        if (ita == m.end())
            m[a] = a;
        auto itb = m.find(b);
        if (itb == m.end())
            m[b] = b;
        buf = m[a];
        m[a] = m[b];
        m[b] = buf;
        cout << abs(m[a] - m[b])<<"\n";
    }
    return 0;
}

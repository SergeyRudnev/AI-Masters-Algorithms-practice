#include <iostream>

using namespace std;
void Merge(int *a, const int &start, const int &end, const int &length, const int &middle)
{
    size_t ind1 = start;
    size_t ind2 = middle + 1;
    int *buf = new int[length];
    for(size_t i = 0; i < length; ++i)
    {
        if (ind1 <= middle && ind2 <= end)
        {
            if (a[ind2] > a[ind1])
            {
                buf[i] = a[ind1];
                ++ind1;
            }
            else
            {
                buf[i] = a[ind2];
                ++ind2;
            }
        }
        else if (ind1 <= middle)
        {
            buf[i] = a[ind1];
            ++ind1;
        }
        else if (ind2 <= end)
        {
            buf[i] = a[ind2];
            ++ind2;
        }
    }

    for(size_t i = 0; i < length; ++i)
    {
        a[start + i] = buf[i];
    }
    delete[]buf;
}
void MergeSort(int *a, const int &start, const int &end, const int &length)
{
    if (start == end)
        return;
    int mid = (start + end) / 2;
    MergeSort(a, start, mid, mid - start + 1 );
    MergeSort(a, mid + 1, end, end - mid);
    Merge(a, start, end, length, mid);
}

int main ()
{
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int t;
    cin >> t;
    for(size_t i = 0; i < t; ++i)
    {
        int n;
        cin >> n;
        int *v = new int[n];
        for(size_t i = 0; i < n; ++i)
            cin >> v[i];
        MergeSort(v,0,n-1,n);
        for(size_t i = 0; i < n; ++i)
            cout << v[i] << " ";
        cout << "\n";
        delete[]v;
    }
    return 0;
}



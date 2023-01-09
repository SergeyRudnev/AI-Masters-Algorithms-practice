#include<iostream>
#include<set>
#include<map>
#include<string>
using namespace std;

template<typename F, typename S, typename T>
class Triad {
public:
    F first;
    S second;
    T third;

    Triad()
    = default;

    Triad(const F &f, const S &s, const T &t):
            first(f),
            second(s),
            third(t)
    {}
    Triad<F, S, T>& operator=(const  Triad<F, S, T>& triad)
    {
        first = triad.first;
        second = triad.second;
        third = triad.third;
    }
};

template<typename F, typename S, typename T>
Triad<F, S, T> MakeTriad(const F &first, const S &second, const T &third) {
    return Triad<F, S, T>(first, second, third);
}

struct Comparator{
    bool operator( )(const Triad<int, string, int> & x, const Triad<int, string, int> &y  ) const {
        if (x.first < y.first) return true;
        if (x.first > y.first) return false;
        return x.third > y.third;
    }
};


class MaxPrQueue{
    set<Triad<int,string,int>, Comparator> time_queue; // int -> priority, string -> key, int -> timestamp
    map<string, set<Triad<int,string,int> >::iterator > find;
public:
    MaxPrQueue()= default;;
    void insert(Triad<int,string,int> vkt);
    void insert(int v, string k, int timestamp){ insert(MakeTriad(v ,k, timestamp)); };
    Triad<int,string,int> extract_max();
    void set_priority(Triad<int,string,int> vkt);
    void set_priority(int v, string k, int timestamp){ set_priority(MakeTriad(v, k, timestamp)); };
    class ExceptionAddTheSameKey{};
    bool is_in_Queue(Triad<int, string, int> vkt);
    bool is_in_Queue(int v, string k, int timestamp){ return is_in_Queue(MakeTriad(v, k, timestamp)); };
    void set_max_priority(Triad<int, string, int> vkt);
    void set_max_priority(int v, string k, int timestamp){ set_max_priority(MakeTriad(v, k, timestamp)); };
    void print();
};

void MaxPrQueue::insert(Triad<int,string,int> vkt){
    if(find.find(vkt.second) == find.end())
        find[vkt.second] = time_queue.insert(vkt).first;
    else{throw ExceptionAddTheSameKey();}
}

Triad<int,string,int> MaxPrQueue::extract_max(){
    auto it = time_queue.end();
    --it;
    find.erase(it->second);
    Triad<int, string, int> x = *it;
    time_queue.erase(it);
    return x;
}

void MaxPrQueue::set_priority(Triad<int,string,int> vkt){
    time_queue.erase(find[vkt.second]);
    find.erase(vkt.second);
    insert(vkt);
}

bool MaxPrQueue::is_in_Queue(Triad<int, string, int> vkt){
    if(find.find(vkt.second) == find.end())
        return true;
    else{return false;}
}


void MaxPrQueue::set_max_priority(Triad<int, string, int> vkt){
    for (auto x : time_queue)
    {
        if (vkt.second == x.second)
        {
            if (vkt.first > x.first)
            {
                set_priority(vkt);
                break;
            }

        }
    }
}

void MaxPrQueue::print(){
    for (auto t : time_queue)
    {
        cout << t.first << " "<< t.second<<" "<<t.third<<"\n";
    }
}


int main ()
{
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int M, N;
    cin >> M >> N;
    int value;
    string name;
    MaxPrQueue q;
    for (int i = 0; i < N; ++i) {
        cin >> name;
        cin >> value;
        if (q.is_in_Queue(value, name, i))
            q.insert(value, name, i);

        else
            q.set_max_priority(value, name, i);
    }

    //q.print();
    for (int j = 0; j < M; ++j)
    {
        auto res = q.extract_max();
        cout <<res.second <<"\n";
    }

    return 0;
}
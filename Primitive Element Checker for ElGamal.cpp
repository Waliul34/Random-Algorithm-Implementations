#include <bits/stdc++.h>
using namespace std;

long long int pow_big(long long int a, long long int b, long long int n)
{
    if(b == 0)
        return 1;
    if(b % 2 == 0)
    {
        long long int result;
        result = pow_big(a, b / 2, n);
        return ((result % n) * (result % n)) % n;
    }
    else
        return ((a % n) * (pow_big(a, b - 1, n) % n)) % n;
}

int main()
{
    long long int i, j, a, b, c, d, n, p, q, m, e, x;
    vector<long long int>prims;

    //p = 7, a = 3 <-- primitive
    //p = 7, a = 2 <-- not primitive
    //p = 13, a = 2 <-- primitive
    //p = 13, a = 3 <-- not primitive
    //p = 125243, a = 5, 6, 101 <-- primitive
    //p = 125243, a = 2, 3, 7 <-- not primitive

    p = 997;
//    a = 101;
    for(j = 1; j < p; j++)
    {
        map<long long int, long long int> dist;
        vector<long long int> pows;
        bool prim = true;
        for(i = 0; i < p - 1; i++)
        {
            a = j;
            x = pow_big(a, i, p);
            if(dist[x])
                prim = false;
            dist[x]++;
            pows.push_back(x);
        }

        if(prim)
        {
            cout<<a<<" is a primitive element of "<<p<<endl<<endl;
            prims.push_back(a);
        }
        else
            cout<<a<<" is NOT a primitive element of "<<p<<endl<<endl;
//        //    sort(vec.begin(), vec.end());
//        for(auto it : pows)
//            cout<<it<<" ";
//        cout<<endl<<endl;

//        if(!prim)
//        {
//            cout<<"The recurring elements: ";
//            for(auto it: dist)
//            {
//                if(it.second > 1)
//                    cout<<it.first<<" ";
//            }
//            cout<<endl<<endl;
//        }
    }
    cout<<endl<<endl<<endl;
    cout<<"Total primitive element of "<<p<<": "<<prims.size()<<endl<<endl;
    cout<<"They are: ";
    for(it : prims)
        cout<<it<<" ";

}

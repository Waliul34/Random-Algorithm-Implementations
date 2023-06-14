//Author: Waliul Islam Sumon (1807034)
//public key for encryption, private key for decryption
//private key(x), public key(g, y, p) where g is primitive

#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
using namespace std;
#define lli long long int

lli gcd(lli a, lli b)
{
    if(b > a)
        swap(a, b);
    lli c = a % b;
    if(c == 0)
        return b;
    return gcd(b, c);
}

lli pow_big(lli a, lli b, lli n)
{
    if(b == 0)
        return 1;
    if(b % 2 == 0)
    {
        lli result;
        result = pow_big(a, b / 2, n);
        return ((result % n) * (result % n)) % n;
    }
    else
    {
        lli result;
        result = ((a % n) * (pow_big(a, b - 1, n) % n)) % n;
        return result;
    }
}

struct triplet
{
    lli x, y, gcd;
};

triplet extendedEuclid(lli a, lli b)
{
    if(b == 0)
    {
        triplet ans;
        ans.x = 1;
        ans.gcd = a;
        ans.y = 0;
        return ans;
    }

    triplet smallAns = extendedEuclid(b, a % b);
    triplet ans;
    ans.x = smallAns.y;
    ans.gcd = smallAns.gcd;
    ans.y = smallAns.x - (a/b)*smallAns.y;
    return ans;
}

lli modInv(lli a, lli n)
{
    triplet temp = extendedEuclid(a, n);
    //11 mod 7 = 4 <--- 7 * 1 + 4 = 11
    //-11 mod 7 = 3 <--- -7 * 2 + 3 = -11
    //but (-11 % 7) gives -4 in C++, so, the below is done to get the right remainder
    lli ans = (temp.x % n + n) % n;
//    cout<<"The GCD: "<<temp.gcd<<endl;
//    cout<<"The x: "<<temp.x<<endl;
//    cout<<"The y: "<<temp.y<<endl;
    return ans;
}

bool isPrimitive(lli p, lli a)
{
    long long int i, b, c, d, n, q, m, e, x;
    map<int, int> dist;
    bool prim = true;

    //p = 7, a = 3 <-- primitive
    //p = 7, a = 2 <-- not primitive
    //p = 13, a = 2, 7 <-- primitive
    //p = 13, a = 3 <-- not primitive
    //p = 125243, a = 5, 6, 101, 1010 <-- primitive
    //p = 125243, a = 2, 3, 7 <-- not primitive


    for(i = 0; i < p - 1; i++)
    {
        x = pow_big(a, i, p);
        if(dist[x])
            prim = false;
        dist[x]++;
    }

    return prim;

}

lli chooseR(lli p, lli t)
{
    lli lb, ub, i, x;
    lb = 2;
    ub = p-1;
    srand(time(0)+t);
    x = (rand() % (ub - lb + 1)) + lb;
    while(gcd(x, ub) != 1)
        x = (rand() % (ub - lb + 1)) + lb;
    return x;
}

int main()
{
    lli a, n2, cyp1, cyp2, cyp1_, cyp2_, cyp1_f, cyp2_f, dec, x, p, q, msg, e, g, lembda, mu(0), r, y, y1, y2, x1, x2, c1, c2, r2, m1, m2;
    bool prim;

    p = 125243;
    g = 1010;

    //x = chooseX(p);
    x = 3;
    r = chooseR(p, 0);
    y = pow_big(g, x, p);

    //cout<<isPrimitive(p, g)<<endl;



    printf("Public Key (g, y, p): (%lld, %lld, %lld)\n", g, y, p);
    printf("Private Key (x): (%lld)\n", x);
    printf("Random Integer (r): (%lld)\n\n", r);


    m1 = 34;
    m2 = 27;
    cout<<"The message 1: "<<m1<<endl<<endl;
    cout<<"The message 2: "<<m2<<endl<<endl;
    cout<<"The multiplied value m1 * m2: "<<m1*m2<<endl<<endl;


    cyp1 = pow_big(g, r, p);
    cyp2 = (m1 * pow_big(y, r, p)) % p;
    cout<<"The encrypted message1 (cyp1, cyp2): ("<<cyp1<<", "<<cyp2<<")"<<endl<<endl;

    cyp1_ = pow_big(g, r, p);
    cyp2_ = (m2 * pow_big(y, r, p)) % p;
    cout<<"The encrypted message2 (cyp1_, cyp2_): ("<<cyp1_<<", "<<cyp2_<<")"<<endl<<endl;

    cyp1_f = (cyp1 * cyp1_) % p;
    cyp2_f = (cyp2 * cyp2_) % p;
    cout<<"The multiplied value (cyp1_f, cyp2_f): ("<<cyp1_f<<", "<<cyp2_f<<")"<<endl<<endl;

    e = pow_big(cyp1_f, x, p);
    dec = (cyp2_f * modInv(e, p)) % p;        //dec = cyp2 / (cyp1 ^ x)
    cout<<"The decrypted message: "<<dec<<endl;

    return 0;
}

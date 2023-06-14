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
    lli a, n2, cyp1, cyp2, dec, x, p, q, msg, e, g, lembda, mu(0), r, y, y1, y2, x1, x2, c1, c2, r2;
    bool prim;

    p = 2000639;
    g = 1011;

    //x = chooseX(p);
    x = 3;
    r = chooseR(p, 0);
    y = pow_big(g, x, p);

    //cout<<isPrimitive(p, g)<<endl;



    printf("Public Key (g, y, p): (%lld, %lld, %lld)\n", g, y, p);
    printf("Private Key (x): (%lld)\n", x);
    printf("Random Integer (r): (%lld)\n\n", r);


    msg = 1807034;
    cout<<"The message: "<<msg<<endl<<endl;


    printf("Standard Encryption & Decryption\n-----------------------------------\n");
    cyp1 = pow_big(g, r, p);
    //cyp2 = (msg * pow_big(y, r, p));       //previous         //doing (cyp2 % p) doesn't yield correct message
    cyp2 = (msg * pow_big(y, r, p)) % p;
    cout<<"The encrypted message (cyp1, cyp2): ("<<cyp1<<", "<<cyp2<<")"<<endl;

    //e = pow_big(cyp1, x, p);              //previous
    //dec = cyp2 / e;                       //previous
    e = pow_big(cyp1, p - 1 - x, p);        //new
    dec = (cyp2 * e) % p;                   //new
    //alternative::
    e = pow_big(cyp1, x, p);
    dec = (cyp2 * modInv(e, p)) % p;        //dec = cyp2 / (cyp1 ^ x)
    cout<<"The decrypted message: "<<dec<<endl;

    cout<<"\n\nDigital Signature\n-------------------"<<endl;
    cout<<"Message: "<<msg<<endl;

    y1 = pow_big(g, r, p);
    y2 = (((msg - x * y1) % (p - 1)) * modInv(r, p-1)) % (p - 1);
    if(y2 < 0)
        y2 += (p - 1);
    cout<<"(y1, y2) = ("<<y1<<", "<<y2<<")"<<endl;

    x1 = (pow_big(y1, y2, p) * pow_big(y, y1, p)) % p;
    cout<<"L.H.S. = "<<x1<<endl;

    x2 = pow_big(g, msg, p);
    cout<<"R.H.S. = "<<x2<<endl;

    if(x1 == x2)
        cout<<"\nVERIFIED!!"<<endl;
    else
        cout<<"\nNOT VERIFIED!!"<<endl;


    cout<<"\n\nRe-randomization\n-------------------"<<endl;


    r2 = chooseR(p, 69696);
    printf("Random Integer (r2): (%lld)\n", r2);
    //c1 = (pow_big(g, r, p) * pow_big(g, r2, p)) % p;          //previous
    //c2 = (pow_big(y, r, p) * pow_big(y, r2, p)) % p;          //previous
    //c2 = (msg * c2);                                          //previous   //doing (c2 % p) doesn't yield correct message
    c1 = (cyp1 * pow_big(g, r2, p)) % p;                        //new
    c2 = (cyp2 * pow_big(y, r2, p)) % p;                        //new
    cout<<"(c1, c2) = ("<<c1<<", "<<c2<<")\n"<<endl;

    //x1 = pow_big(c1, x, p);                                   //previous
    //x2 = c2 / x1;                                             //previous
    x1 = pow_big(c1, p - 1 - x, p);                                     //new
    x2 = (c2 * x1) % p;                                               //new
    //also can do:
    //x1 = pow_big(c1, x, p);
    //x2 = (c2 * modInv(x1, p)) % p;
    cout<<"The decrypted message: "<<x2<<endl<<endl;

}

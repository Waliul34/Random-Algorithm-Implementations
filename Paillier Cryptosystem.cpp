//public key for encryption, private key for decryption

//p = 32416190071, q = 64832380147
//if p cannot divide (q - 1), then the gcd will be 1.

#include <bits/stdc++.h>
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

lli lcm(lli a, lli b)
{
    return (a / gcd(a, b)) * b;
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

lli multiplicativeModuloInverse(lli a, lli n)
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

lli L(lli x, lli n)
{
    return (x - 1) / n;
}

lli chooseG(lli n)
{
    lli n2, i, j, k, x, g;
    n2 = n * n;
//    for(i = 2; i < n; i++)
//    {
//        if(gcd(i, n) == 1)
//        {
//            g = pow_big(i, n, n2);
//            if(gcd(g, n2) == 1 && g != 0)
//                return g;
//        }
//    }
//    return -1;
    for(i = 2; i < n; i++)
        if(gcd(i, n2) == 1)
            return i;
}

lli chooseMu(lli g, lli lembda, lli n)
{
    lli x, b, c, d, mu, n2;
    n2 = n * n;
    x = pow_big(g, lembda, n2);
    b = L(x, n);
    mu = multiplicativeModuloInverse(b, n);
    return mu;
}

lli chooseR(lli n)
{
    lli lb, ub, i, x;
    lb = 15;
    ub = 155;
    srand(time(0));
    x = (rand() % (ub - lb + 1)) + lb;
    while(gcd(x, n) != 1)
        x = x = (rand() % (ub - lb + 1)) + lb;
    return x;
}

int main()
{
    lli i, x1, x2, a, b, n2, cyp, dec, x, p, q, msg, e, n, phi_n, g(0), lembda, mu(0), r;


    p = 101;
    q = 103;
    n = p * q;
    phi_n = (p - 1) * (q - 1);
    lembda = lcm((p - 1), (q - 1));
    n2 = n * n;

    g = chooseG(n);
    //  g = n + 1;
    mu = chooseMu(g, lembda, n);

    printf("Public Key (n, g): (%lld, %lld)\n", n, g);
    printf("Private Key (lambda, mu): (%lld, %lld)\n", lembda, mu);

    r = chooseR(n);

    msg = 1111;
    cout<<"The message: "<<msg<<endl;
    x1 = pow_big(g, msg, n2);
    x2 = pow_big(r, n, n2);
    cyp = (x1 * x2) % n2;
    cout<<"The encrypted message: "<<cyp<<endl;
    x1 = L(pow_big(cyp, lembda, n2), n);
    dec = ((x1 % n) * (mu % n)) % n;
    cout<<"The decrypted message: "<<dec<<endl;


}

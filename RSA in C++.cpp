//In normal RSA, public key for encryption, private key for decryption
//For RSA Digital Signature, Encryption with Private Key, Decryption with Public Key
//public key = e
//private key = d


#include <bits/stdc++.h>
using namespace std;

long long int gcd(long long int a, long long int b)
{
    if(b > a)
        swap(a, b);
    long long int c = a % b;
    if(c == 0)
        return b;
    return gcd(b, c);
}

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


struct triplet
{
    long long int x, y, gcd;
};

triplet extendedEuclid(long long int a, long long int b)
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

long long int multiplicativeModuloInverse(long long int a, long long int n)
{
    triplet temp = extendedEuclid(a, n);
    //11 mod 7 = 4 <--- 7 * 1 + 4 = 11
    //-11 mod 7 = 3 <--- -7 * 2 + 3 = -11
    //but (-11 % 7) gives -4 in C++, so, the below is done to get the right remainder
    long long int ans = (temp.x % n + n) % n;
    return ans;
}

int main()
{
    long long int i, a, b, c, d, n, p, q, m, e, phi_n, x;
//    a = 12, b = 16;
//    cout<<gcd(b, a)<<endl;

    p = 7907;
    q = 7919;

    n = p * q;
    phi_n = (p - 1) * (q - 1);

    e = 2;
    while(e < phi_n)
    {
        if(gcd(e, phi_n) == 1)
            break;
        e++;
    }


//    //one way of finding d
//    d = 1;
//    for(i = 0; i < n; i++)
//    {
//        x = 1 + i * phi_n;
//        if(x % e == 0)
//        {
//            d = x / e;
//            break;
//        }
//    }


//    //another way of finding d, using modular multiplicative inverse, naive approach
//    d = 1;
//    for(i = 1; i < phi_n; i++)
//    {
//        if(((e % phi_n) * (i % phi_n)) % phi_n == 1)
//        {
//            d = i;
//            break;
//        }
//    }


    //The most efficient way of finding d, using Extended Euclidean algorithms
    d = multiplicativeModuloInverse(e, phi_n);
    cout<<"The e: "<<e<<endl;
    cout<<"The phi_n: "<<phi_n<<endl;
    cout<<"The d: "<<d<<endl<<endl;




    m = 1807034;
    cout<<"The message: "<<m<<endl<<endl;
    a = pow_big(m, e, n);
    cout<<"The encrypted message: "<<a<<endl<<endl;
    b = pow_big(a, d, n);
    cout<<"The decrypted message: "<<b<<endl<<endl;

}

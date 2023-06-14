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


int main()
{
    long long int i, a, b, c, d, n, p, q, m, e, phi_n, x, d1, d2;
//    a = 12, b = 16;
//    cout<<gcd(b, a)<<endl;

    p = 997;
    q = 1009;

    n = p * q;
    phi_n = (p - 1) * (q - 1);

    e = 2;
    while(e < phi_n)
    {
        if(gcd(e, phi_n) == 1)
            break;
        e++;
    }


    d = 1;
    for(i = 0; i < n; i++)
    {
        x = 1 + i * phi_n;
        if(x % e == 0)
        {
            d = x / e;
            break;
        }
    }


    cout<<"The e: "<<e<<endl;
    cout<<"The phi_n: "<<phi_n<<endl;
    cout<<"The d: "<<d<<endl<<endl;




    m = 7034;
    cout<<"The message: "<<m<<endl<<endl;
    a = pow_big(m, e, n);
    cout<<"The encrypted message: "<<a<<endl<<endl;
//    b = pow_big(a, d, n);
//    cout<<"The decrypted message: "<<b<<endl<<endl;

    //Decryption key finding
    x = 1;
    bool notFound = true;
    while(notFound)
    {
        d1 = pow_big(a, x, n);
        if(d1 == m)
            break;
        x++;
    }
    cout<<"The found key, d: "<<x<<endl<<endl;
    d1 = pow_big(a, x, n);
    cout<<"The decrypted message: "<<d1<<endl<<endl;

}

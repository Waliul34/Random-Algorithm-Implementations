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
    long long int i, a, b, c, d, n, p, q, m1, m2, e, phi_n, x, e1, e2, m_e;
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


    //one way of finding d
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




    m1 = 34;
    m2 = 27;
    cout<<"The message 1: "<<m1<<endl<<endl;
    cout<<"The message 2: "<<m2<<endl<<endl;
    cout<<"The multiplied value m1 * m2: "<<m1*m2<<endl<<endl;
    e1 = pow_big(m1, e, n);
    cout<<"The encrypted message 1: "<<e1<<endl<<endl;
    e2 = pow_big(m2, e, n);
    cout<<"The encrypted message 2: "<<e1<<endl<<endl;
    m_e = e1 * e2;
    cout<<"The multiplied value e1 * e2: "<<e1*e2<<endl<<endl;
    b = pow_big(m_e, d, n);
    cout<<"The decrypted message: "<<b<<endl<<endl;

}

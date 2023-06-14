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
    long long int i, a, b, c, d, n, p, q, m1, m2, e, phi_n, x, e1, e2, m_e, msg, d_e;
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
    cout<<"The n: "<<n<<endl;
    cout<<"The d: "<<d<<endl<<endl;



    msg = 1807034;
    hash<string>hash_fn;
    size_t msg_hash = hash_fn(to_string(msg)) % n;

    cout<<"The message: "<<msg<<endl<<endl;
    cout<<"The hash message: "<<msg_hash<<endl<<endl;

    m_e = pow_big(msg_hash, d, n);
    cout<<"The encrypted hash: "<<m_e<<endl<<endl;

    cout<<"In receiver side:\n-----------------"<<endl<<endl;

    size_t rcv_hash = hash_fn(to_string(msg)) % n;
    cout<<"The calculated hash of message: "<<rcv_hash<<endl<<endl;

    d_e = pow_big(m_e, e, n);
    cout<<"The decrypted hash: "<<d_e<<endl<<endl;

    if(d_e == rcv_hash)
        cout<<"VERIFIED!!!"<<endl;
    else
        cout<<"Verification failed!!!"<<endl;
    return 0;

}

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int i, j, k, m, n, x, y;
    string msg, cyp_text, dec_text, key;
    char temp;

    msg = "ATTACKKBRO";
    key = "MONEYMONEY";
    cout<<"The message: "<<msg<<endl<<endl;

    cyp_text = "";
    n = msg.size();
    for(i = 0; i < n; i++)
    {
        x = msg[i] - 'A';
        y = key[i] - 'A';
        k = x ^ y;
//        if(k >= 26)
//            k = k - 26;
        temp = 'A' + k;
        cyp_text += temp;

    }

    cout<<"The cipher text: "<<cyp_text<<endl<<endl;

    dec_text = "";
    n = cyp_text.size();
    for(i = 0; i < n; i++)
    {
        x = cyp_text[i] - 'A';
        y = key[i] - 'A';
        k = x ^ y;
//        if(k >= 26)
//            k = k - 26;
        temp = 'A' + k;
        dec_text += temp;

    }

    cout<<"The decrypted text: "<<dec_text<<endl<<endl;

}

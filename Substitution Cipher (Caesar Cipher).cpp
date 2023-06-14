#include <bits/stdc++.h>
using namespace std;

int main()
{
    int i, j, k, m, n, key;
    string msg, cyp_text, dec_text;
    char temp;

    msg = "I am a HUMAN ZXY!";
    cout<<"The message: "<<msg<<endl<<endl;
    key = 4;

    cyp_text = "";
    n = msg.size();
    for(i = 0; i < n; i++)
    {
        if(msg[i] >= 'a' && msg[i] <= 'z')
        {
            k = msg[i] - 'a' + key;
            k = k % 26;
            temp = 'a' + k;
            cyp_text += temp;
        }
        else if(msg[i] >= 'A' && msg[i] <= 'Z')
        {
            k = msg[i] - 'A' + key;
            k = k % 26;
            temp = 'A' + k;
            cyp_text += temp;
        }
        else
            cyp_text += msg[i];
    }

    cout<<"The cipher text: "<<cyp_text<<endl<<endl;

    dec_text = "";
    n = cyp_text.size();
    for(i = 0; i < n; i++)
    {
        if(cyp_text[i] >= 'a' && cyp_text[i] <= 'z')
        {
            k = cyp_text[i] - 'a' - key;
            if(k < 0)
                k += 26;
            temp = 'a' + k;
            dec_text += temp;
        }
        else if(cyp_text[i] >= 'A' && cyp_text[i] <= 'Z')
        {
            k = cyp_text[i] - 'A' - key;
            if(k < 0)
                k += 26;
            temp = 'A' + k;
            dec_text += temp;
        }
        else
            dec_text += cyp_text[i];
    }

    cout<<"The decrypted text: "<<dec_text<<endl<<endl;

}

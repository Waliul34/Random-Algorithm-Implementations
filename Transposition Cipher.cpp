//In this version, I start encryption and decryption from backward and change the alphabets in reverse letter case

#include<bits/stdc++.h>
using namespace std;

int main() {

    int i, j, k, m, n, a, b, c, col_no, row_no, key_size, block_size;
    string message, str_key, key, temp, cipher_text, decrypted_text;

    message = "I am Waliul. I study CSE(KUET). My roll is 1807034.";
    str_key = "Engineer";

    ////Key generation
    map<int, int> my_map;
    map<int, int> cnt;
    temp = str_key;
    sort(temp.begin(), temp.end());
    key_size = temp.size();

    j = 1;
    for(i = 0; i < key_size; i++)
    {
        cnt[temp[i]] += 1;
        if(my_map[temp[i]] == 0)
            my_map[temp[i]] = j;
        j++;
    }

    map<int, int> key_cnt;
    key = "";
    for(x: str_key)
    {
        key += to_string(my_map[x] + key_cnt[x]);
        key_cnt[x]++;
    }

    //cout<<key<<endl;

    cout<<"The message: "<<message<<endl<<endl;
    cout<<"The key: "<<str_key<<endl;
    cout<<"The ordered key: "<<key<<endl;

    ////Encryption
    col_no = key_size;
    n = message.size();
    row_no = ceil(n * 1.0 / col_no) + 1;
    //cout<<row_no<<endl;

    char enc_mat[row_no][col_no];
    for(i = 0; i < key_size; i++)
        enc_mat[0][i] = key[i];

    k = 0;
    for(i = 1; i < row_no; i++)
        for(j = 0; j < col_no; j++)
        {
            if(k < n)
                enc_mat[i][j] = message[k++];
            else
                enc_mat[i][j] = '*';
        }

    cout<<endl<<"The encryption matrix: "<<endl;
    for(i = 0; i < row_no; i++)
    {
        for(j = 0; j < col_no; j++)
            cout<<enc_mat[i][j]<<" ";
        cout<<endl;
    }

    //Generating cipher in reverse
    k = key_size;
    a = 0;
    cipher_text = "";
    for(i = 0; i < col_no; i++)
    {
        for(j = 0; j < col_no; j++)
            if(enc_mat[0][j] == to_string(k)[0])
                a = j;

        for(j = 1; j < row_no; j++)
        {
            if(enc_mat[j][a] >= 'A' && enc_mat[j][a] <= 'Z')
                cipher_text += tolower(enc_mat[j][a]);
            else if(enc_mat[j][a] >= 'a' && enc_mat[j][a] <= 'z')
                cipher_text += toupper(enc_mat[j][a]);
            else
                cipher_text += enc_mat[j][a];
        }

        k--;
    }

    cout<<endl;
    cout<<"The cipher text: "<<cipher_text<<endl<<endl;


    ////Decryption
    col_no = key_size;
    block_size = cipher_text.size() / key_size;
    row_no = block_size + 1;
    char dec_mat[row_no][col_no];

    for(i = 0; i < key_size; i++)
        dec_mat[0][i] = key[i];

    k = key_size;
    a = 0;
    b = 0;
    for(i = 0; i < col_no; i++)
    {
        for(j = 0; j < col_no; j++)
            if(dec_mat[0][j] == to_string(k)[0])
                a = j;

        for(j = 1; j < row_no; j++)
            dec_mat[j][a] = cipher_text[b++];

        k--;
    }

    cout<<endl<<"The decryption matrix: "<<endl;
    for(i = 0; i < row_no; i++)
    {
        for(j = 0; j < col_no; j++)
            cout<<dec_mat[i][j]<<" ";
        cout<<endl;
    }

    //Generating decrypted text
    decrypted_text = "";
    for(i = 1; i < row_no; i++)
    {
        for(j = 0; j < col_no; j++)
        {
            if(dec_mat[i][j] >= 'A' && dec_mat[i][j] <= 'Z')
                decrypted_text += tolower(dec_mat[i][j]);
            else if(dec_mat[i][j] >= 'a' && dec_mat[i][j] <= 'z')
                decrypted_text += toupper(dec_mat[i][j]);
            else if(dec_mat[i][j] == '*')
                continue;
            else
                decrypted_text += dec_mat[i][j];
        }
    }

    cout<<endl<<"The decrypted text: "<<decrypted_text<<endl<<endl;

    if(message == decrypted_text)
        cout<<"Transposition Cipher SUCCESSFUL!!!\n";
    else
        cout<<"Transposition Cipher FAILED!!!\n";

    return 0;
}


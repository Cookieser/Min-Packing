

#include <iostream>
#include <gmp.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

/*a decimal number will be transformed to the binary one with the fix length*/
string toBinary(long long n, int length) {
    string r;
    char c = '0';
    while (n != 0) {
        r += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    }
    reverse(r.begin(), r.end());
    if (r.length() < length) {
        r.insert(0, length - r.length(), c);
    }
    return r;
}

/*trans  010101(string)-->gmp_num*/
void trans(string s, mpz_t result) {

    mpz_t base, b;
    mpz_init(base);
    mpz_init(b);
    mpz_set_si(base, 2);

    mpz_init(result);
    unsigned long int exponent;
    unsigned long int midvalue;
    long long res = 0;
    for (int i = 0; i < s.length(); i++) {
        midvalue = s[i] - 48;
        exponent = s.length() - 1 - i;
        mpz_pow_ui(b, base, exponent);
        mpz_mul_ui(b, b, midvalue);
        mpz_add(result, b, result);

    }
    gmp_printf("%Zd", result);
    printf("\n");
    mpz_clear(base);
    mpz_clear(b);

}


/*trans  010101(string)-->little num*/
long long translittle(string s) {
    long long res = 0;
    for (int i = 0; i < s.length(); i++) {
        printf("%d", s[i] - 48);


        res = res + (s[i] - 48) * pow(2, s.length() - 1 - i);


    }
    printf("--------The value  by decimal  %lld\n", res);
    return res;

}

/*encoding these data and generate a gmp_num*/
int testEncoding(int value[], int n, int block, int num, mpz_t result) {

    mpz_init(result);

    int valuemax = pow(2, n) - 1;
    string m;
    char c = '0';
    for (int i = 0; i < num; i++) {
        if (value[i] > valuemax) {
            printf("Too large！");
            return 0;
        }

        string q = toBinary(value[i], n);
        q.insert(0, block, c);
        cout << "Adding value expressed by binary:" << q << endl;
        m = m + q;

    }

    cout << "The value packed:" << m << endl;
    printf("%s", "so, the packing value is ");
    trans(m, result);
    printf("\n");
    return 0;
}


/*

Decoding a big big number which has been transformed to plaintext after the homomorphic operations

*/
int *testDecoding(mpz_t w, int n, int block, int num) {


    int length = (n + block) * num;
    char *str = new char[100];
    string b;
    char c = '0';

    mpz_get_str(str, 2, w);
    b = str;

    if (b.length() < length) {
        b.insert(0, length - b.length(), c);
    }
    cout << "The packing result can use binary to express: " << b << endl;


    int *value = new int[num];
    string val;
    for (int i = 0; i < num; i++) {
        int a = block - 1 + (n + block) * i;
        int c = 1 + n;
        val = b.substr(a, c);
        value[i] = translittle(val);

    }
    return value;

}


int main() {


    int block = 2;

    int n = 8;


    /*
    Reading data:
    
    
    Read a series of data in data.txt
    
    */

    int a;

    int val[100];


    FILE *fp1 = fopen("data.txt", "r");

    char c = ' ';

    if (fp1 == NULL) {
        puts("CAN NOT OPEN THE TXT！");
        return 0;
    }

    int m;

    int num = 0;

    fseek(fp1, 0, 2);

    m = ftell(fp1);

    rewind(fp1);

    while (ftell(fp1) != m - 1) {
        fscanf(fp1, "%d", &a);

        val[num] = a;

        //printf("%d\n",val[num]);

        num++;


    }


    fclose(fp1);

    /*
    
    Start to encoding : 
    
    
    
    try to packing all values into one coded number
    
    
    */
    mpz_t result;

    mpz_init(result);

    testEncoding(val, n, block, num, result);


    /*
    
    Start to decoding : 
    
    
    
    Start to decoding and write the output into the output.txt
    
    
    
    */

    int *res;

    res = testDecoding(result, n, block, num);

    FILE *fp2 = fopen("output.txt", "w");

    char blockflag = ' ';

    for (int i = 0; i < num; i++) {
        int value = *(res + i);

        fprintf(fp2, "%d", value);
        fputc(blockflag, fp2);

    }
    fclose(fp2);
}
    
    
	
    





#include <iostream>
#include <gmp.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;


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


int main(int argc, char *argv[]) {


    int block = atoi(argv[4]);

    int n = atoi(argv[5]);

    int num = atoi(argv[3]);

    mpz_t result;

    mpz_init(result);


    FILE *fp1 = fopen(argv[1], "r");

    mpz_inp_str(result, fp1, 16);

    fclose(fp1);

    /*
    
    Start to decoding : 
    
    
    
    Start to decoding and write the output into the output.txt
    
    
    
    */

    int *res;

    res = testDecoding(result, n, block, num);

    FILE *fp2 = fopen(argv[2], "w");

    char blockflag = ' ';

    for (int i = 0; i < num; i++) {
        int value = *(res + i);

        fprintf(fp2, "%d", value);
        fputc(blockflag, fp2);

    }
    fclose(fp2);
}
    
    



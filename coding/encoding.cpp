
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
    return 0;
}


int main(int argc, char *argv[]) {


    int block = atoi(argv[3]);

    int n = atoi(argv[4]);


    /*
    Reading data:
    
    
    Read a series of data in data.txt
    
    */

    int a;

    int val[100];


    FILE *fp1 = fopen(argv[1], "r");

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

    FILE *fp2 = fopen(argv[2], "w");

    mpz_t result;

    mpz_init(result);

    testEncoding(val, n, block, num, result);

    mpz_out_str(fp2, 16, result);
    fclose(fp2);


}
    















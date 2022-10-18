#ifndef MATH_ADD_H__
#define MATH_ADD_H__
 #include <iostream>
#include <gmp.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
 
string toBinary(long long n, int length);
void trans(string s, mpz_t result);
int testEncoding(int value[], int n, int block, int num, mpz_t result);
int encoding(int block, int n,char *input,char *output);
 
#endif

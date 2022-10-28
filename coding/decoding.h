#ifndef DECODING_H__
#define DECODING_H__
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
 
long long translittle(string s);
int *testDecoding(mpz_t w, int n, int block, int num);
int decoding(int block,int n,int num, char *intput,char *output);
 
#endif

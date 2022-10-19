#ifndef SEAL_LSIC_H__
#define SEAL_LSIC_H__
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
using namespace seal;

int valueAtBit(int num, int bit);
vector<uint64_t> seal_lsic(mpz_t a, mpz_t b,int n,int block,int l);
 
#endif

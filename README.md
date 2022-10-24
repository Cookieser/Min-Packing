

## Introduction

Secure maximum(minimum) batching comparison scheme based on Paillier and BFV

* The maximum value comparison scheme is referred to [Machine Learning Classification over Encrypted Data](https://eprint.iacr.org/2014/331.pdf)
* Implementation of Paillier: https://github.com/camillevuillaume/Paillier-GMP
* Implementation of BFV: https://github.com/microsoft/SEAL

The scheme realizes batching process through FHE and Paillier on the basis of secure maximum comparison protocol. We can carry out parallel comparison of multiple groups of values. 

This is a complete beta version, and the performance test and optimization are still in progress......

## Project Structure

- CMakeLists.txt

- coding: Realize encoding and decoding function

- paillier: Implementation of Paillier encryption system and the basic maximum comparison in that paper

- seal-part: The tool of seal library 

- seal_lsic.cpp

- batching_encrypted_comparing.cpp

- lsic_test.cpp

- main.cpp

  

##  Preparation

> Some knowledge used in this project

* GMP Labrary
* SEAL
* Cmake
* FHE
* Paillier
* Cmake

## Use

```
mkdir build;
cd build;
cmake ..
make
./main
```

## For Example

```
INPUT:
{3, 18, 20, 8, 10}   
{13, 20, 29, 7, 13}    
{14, 25, 27, 6, 5} 
{14, 22, 23, 12,19}
OUTPUT:
MAX:
{14,25,29,12,19}

```

![image-20221024214938346](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20221024214938346.png)

![image-20221024215031338](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20221024215031338.png)

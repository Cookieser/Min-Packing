# Paillier-Packing

## Introduction

Through this program, we try to understand Paillier cryptosystem and complete the operation of batching in this encryption.

To ensure security, the plaintext space in this scheme has a fixed size (such as 3072 bits). When the plaintext to be encrypted belongs to a smaller space (such as 16bits), we make full use of the plaintext space and package multiple plaintexts into one for encryption and decryption. 

Compared with the original encryption of one plaintext at a time, this batching operation can greatly improve performance.

## Scheme

* Packing: concatenate a series of values

* Encryption: encrypt $m$ using Paillier algorithm to obtain ciphertext $c$ 
* Homomorphic operation: Use the homomorphic property to do some calculation and get a sum ciphertext $c'$
* Decryption: decrypt ciphertext $c'$ using Paillier decryption, obtain plaintext $m'$ 
* Unpacking: split $m'$ after decryption

## Demo

![20220916011143](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/20220916011143.png)

## Dependency

[Partially Homomorphic Encryption library for Python](https://github.com/data61/python-paillier)

## Reference

[Answering Aggregation Queries in a Secure System Model](http://cs.brown.edu/research/db/publications/vldb07_ge.pdf) 

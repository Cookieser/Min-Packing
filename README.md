# Paillier-Packing
## Overview

This  repository bases on these projects:

* https://github.com/camillevuillaume/Paillier-GMP

* https://github.com/jzhchu/Paillier-GMP

The Paillier cryptosystem is a public-key cryptosystem with a very interesting property: given the encryption of two messages  $m_1$ and $m_2$, anybody can compute the encryption of  $m_1+m_2$ ! There are multiple applications, including for instance secure electronic voting, or private information retrieval, where one can query a database without the database knowing which element has been retrieved, and far more. While there are other cryptosystems like pairing-based cryptography where it is also possible to compute one addition on top of additions, and even fully homomorphic cryptosystems, the Paillier cryptosystem has the advantage of being relatively simple, efficient and is based on well-understood mathematics. Furthermore, it is sufficient for many applications.

The motivation of this program is to implement the Paillier cryptosystem in C using the GMP library (GNU Multiple Precision Arithmetic Library) for low-level functions. The cryptosystem is provided as a shared library, and a small command interpreter is also available to execute various tasks like key generation, encryption, decryption, homomorphic operations from the command line. The program was developed from a Linux machine and has not been tested on a different environment.

More information about the Paillier cryptosystem and GMP can be found [here](https://en.wikipedia.org/wiki/Paillier_cryptosystem https://gmplib.org/). 

## How to use

### Syntax for the built-in interpreter

Available commands for the interpreter (in case of standalone interpreter, please replace `paillier` by `paillier_standalone`):

```
paillier keygen [public key file name] [private key file name] [bit length]
```

Generate two files, one storing the public key, the other the private key, based on the specified keylength. Example: `/paillier keygen pub2048 priv2048 2048` will generate the 2048-bit public and private keys and store them in two files.

```
paillier encrypt [output ciphertext file name] [input plain text file name] [public key file name]
```

From the public key and plaintext files specified in the input, the program calculates the ciphertext via encryption and stores it in a file. Example: `./paillier encrypt c1 m1 pub2048` will encrypt the plaintext from the file `m1` and store it in file `c1`, using the public key from file `pub2048`.

```
paillier decrypt [output plaintext file name] [input ciphertext file name] [private key file name]
```

From the private key and ciphertext files specified in the input, the program calculates the plaintext via decryption and stores it in a file. Example: `./paillier decrypt m2 c1 priv2048` will decrypt the ciphertext from the file `c1` and store it in file `m2`, using the private key from file `priv2048`.

```
paillier homoadd [output ciphertext 3 file name] [input ciphertext 1 file name] [input ciphertext 2 file name] [public key file name]
```

From two ciphertext and one public key files, the program homomorphically add the two input ciphertexts and stores the resulting ciphertext in a new file. Example: `./paillier homoadd c3 c2 c1 pub2048` will add the ciphertexts from the files `c1` and `c2` and store it in file `c3`, using the public key from file `pub2048`.

```
paillier homomul [output ciphertext 2 file name] [input ciphertext 1 file name] [input constant file name] [public key file name]
```

From a ciphertext, constant and public key files, the program homomorphically multiplies the constant and ciphertext and stores the resulting ciphertext in a new file. Example: `./paillier homomul c2 ct c1 pub2048` will multiply the ciphertext from the files `c1` with the constant stored in file `ct` and store it in file `c2`, using the public key from file `pub2048`.

Here is an example of a sequence of interpreter command executions.

```
./paillier keygen pub2048 priv2048 2048 ;
 echo 5 > m1 ;
 echo 6 > m2 ;
 ./paillier encrypt c1 m1 pub2048 ;
 ./paillier encrypt c2 m2 pub2048 ;
 ./paillier homoadd c3 c1 c2 pub2048 ;
 ./paillier decrypt m3 c3 priv2048 ;
 cat m3
```

Should yield 0xb=11=5+6.

### New

Just like the theme we talk in the python-branch, we enable to complete the packing operation to improve the efficiency and make the cryptosystem to be used more reasonable. Compared to the python one, we combine the GMP library to implement large number operation which is more closely to the real environment.

```
mkdir build
cd build/

# making the coding part
cmake ../coding
make

# making the paillier cryptosystem
make -C ..

# run
 ./paillier_standalone keygen pub2048 priv2048 2048 ;
 
# encoding a series of data in data.txt into one large number in m1 
# ./encoding data.txt block-bits value-bits;
./encoding data.txt m1 2 10;
./encoding data.txt m2 2 10;

./paillier_standalone encrypt c1 m1 pub2048 ;
./paillier_standalone encrypt c2 m2 pub2048 ;
./paillier_standalone homoadd c3 c1 c2 pub2048 ;
./paillier_standalone decrypt m3 c3 priv2048 ;
 
 # decoding the data in m3 and write to the output.txt
 # ./decoding out.txt num block-bits value-bits;
 ./decoding m3 output.txt 4 2 10
```

### Example

Let's use the data in `data.txt` as the  original data, add itself by Paillier cryptosystem, and write the output in `output.txt`

![image-20220924143754650](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20220924143754650.png)

![image-20220924143440565](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/image-20220924143440565.png)

![QQ图片20220924144752](https://pic-1306483575.cos.ap-nanjing.myqcloud.com/images/QQ%E5%9B%BE%E7%89%8720220924144752.png)

Try 100 numbers in `data.txt`, this program can work as well.

![image](https://user-images.githubusercontent.com/87306014/192086168-680f4e7a-6f10-4891-b051-c9ba9f844cdc.png)
![image](https://user-images.githubusercontent.com/87306014/192086232-1b8ecbd8-02b8-48bc-a4b2-a2773b1c2637.png)


![image](https://user-images.githubusercontent.com/87306014/192086210-b93f3b95-e3fa-40b0-b5eb-bb0451b09ed6.png)

![image](https://user-images.githubusercontent.com/87306014/192086252-2cfabaa1-2c6c-4881-af24-305f549547fc.png)

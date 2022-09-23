#include <iostream>
#include <gmp.h>
#include <string>


#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;


/*十进制转二进制字符串*/
string toBinary(long long n,int length)
{
    string r;
    char c = '0';
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    reverse(r.begin(),r.end());
    if(r.length()<length)
    {
    	r.insert(0,length-r.length(),c);
	}
    return r;
}
void trans(string s)
{	

	mpz_t result, base,b;  
    	mpz_init(base); 
    	mpz_init(b); 
    	mpz_set_si(base,2);
     
    	mpz_init(result); 
    	unsigned long int exponent; 
    	unsigned long int midvalue;
	long long res=0;
	for(int i =0;i<s.length();i++)
	{	
		midvalue=s[i]-48;
		exponent=s.length()-1-i;
		mpz_pow_ui(b, base, exponent);
		mpz_mul_ui(b,b,midvalue);
		mpz_add(result,b,result);
		
	}
	gmp_printf("%Zd", result); 
	
	mpz_clear(base); //gmp变量在用完过后需要clear，大概就是释放空间  
    	mpz_clear(b);   
	
}
long long testEncoding(int value[], int n ,int block,int num)
{
	int valuemax=pow(2,n)-1;
	string m;
	char c='0';
	for (int i=0;i<num;i++)
	{
		if(value[i]>valuemax) 
			{
				printf("Too large！");
				return 0;
			} 
			
			string q=toBinary(value[i],n);
			q.insert(0,block,c);
			cout <<"Adding value expressed by binary:" << q<<endl;
			m=m+q;
			
			}
   
    		cout <<"The value packed:"<< m<<endl;

	trans(m);
	return 0;
}
int main() 
{ 
    /*mpz_t result, base; //定义gmp整型变量 
    mpz_init(base); //gmp里面的变量赋值以前都要初始化，估计是分配内存空间 
    mpz_init(result); unsigned long int exponent; //定义长整型指数 
    printf("Please input a base:"); 
    gmp_scanf("%Zd", &base); //输入基数 
    printf("Please input a exponent:"); //输入指数 
    scanf("%ld", &exponent); 
    mpz_pow_ui(result, base, exponent); //调用gmp里面的指数函数 
    gmp_printf("%Zd", result); //调用gmp里面的printf，因为输出的结果可能会比较大，所以printf不够 
    mpz_clear(base); //gmp变量在用完过后需要clear，大概就是释放空间 
    mpz_clear(result); 
    return 0; 
    */
    
 
	int block =2;
	int n=6;
	int val[]={10,20,30};
	int num=3;
    testEncoding(val,n,block,num);
    //string m;
    //cin>>m;
    //gmp_printf("%Zd", transt(m)); 
} 

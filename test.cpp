#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;
#define MAXN 10001 //a������0~100��b��0~1000������a^b���Ϊ10^10000,���ᳬ��10001λ��


void modRes(int res[], int n) {//�ӵ�λ��ʼ���λ��λ
    for(int i=0;i<n-1;++i) {
        res[i+1] += (res[i]/10);
        res[i] %=10;
    }
}
int powInt(int a, int b)
{
    int i;
    int res[MAXN]={0};//��Ž�������飬���Կ���һ������
    res[0]=a;
    for(i=1;i<b;++i) {
        for(int j=0;j<MAXN-1;++j) {
            res[j] *= a;//������ÿһλ����a
        }
        modRes(res, MAXN);//��λ
    }
 
    for(i=MAXN-1;i>=0;--i) {//��λ�����0����Ҫ���
        if(res[i] != 0) break;
    }
    cout<<a<<"^"<<b<<"=";
    for(;i>=0;--i) {//�ӵ�һ������0�ĸ�λ��ʼ���
        cout<<res[i];
    }
    cout<<endl;
 
    return 0;
}
 


/*ʮ����ת�������ַ���*/
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

/*�ַ���������תʮ����*/
long long convertBinaryToDecimal(long long n)
{
    long long decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
long long trans(string s)
{
	long long res=0;
	for(int i =0;i<s.length();i++)
	{
		printf("%d",s[i]-48);
		//cout <<"res="<<res<<"+"<<s[i]-48<<"*2^" <<s.length()-1-i<<endl;
		res=res+(s[i]-48)*powInt(2,s.length()-1-i);
		
		
	}
	printf("The value  by decimal  %lld\n",res);
	return res;
	
}
/*
����value���飬nֵ��λ��block�����С������һ��packingʮ������ 
*/
long long testEncoding(int value[], int n ,int block,int num)
{
	int valuemax=pow(2,n)-1;
	string m;
	char c='0';
	for (int i=0;i<num;i++)
	{
		if(value[i]>valuemax) 
			{
				printf("Too large��");
				return 0;
			} 
			
			string q=toBinary(value[i],n);
			q.insert(0,block,c);
			cout <<"Adding value expressed by binary:" << q<<endl;
			m=m+q;
			
			}
   
    		cout <<"The value packed:"<< m<<endl;

	long long res=trans(m);
	return res;
}

int * testDecoding(long long w, int n ,int block,int num)
{
	int length=(n+block)*num;
	
	
	string b=toBinary(w,length);
	cout <<b.length()<<endl;
	cout <<b<<endl;
	
	
	
	int *value=new int[num];
	string val;
	for(int i=0;i<num;i++)
	{
		int a=block-1+ (n+block)*i;
		int c=1+n;
		val=b.substr(a,c);
		cout <<a<<endl;
		cout <<c<<endl;
		cout <<val<<endl;
		value[i]=trans(val);
		
	}
	return value;
	
}
int main(){
	const int eps = 1e-6;
	int block =2;
	int n=6;
	
	
	
	int i,datalen=0;
    int val[100];
    ifstream file("data.txt");
    while( ! file.eof() )
    file>>val[datalen++];
    for(int i=0;i<datalen;i++)
    {
        cout<<val[i]<<" ";
    }
    file.close();
	int num = datalen;
	
	
	
	printf("Quantity��%d\n",num);
	//testDecoding(testEncoding(val,n,block,num),n,block,num);
	trans("11001001000001100111000100110101000010011111001111111101");

	return 0;
} 
 //ʹ�ô����⣬ͬʱ����io����Դ����������Ӽ��� ���ܽ�̬ͬ���ܣ��Ķ��Ż����ģ��Ķ��й�c++������֪ʶ��pow����������� 

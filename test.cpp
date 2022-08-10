#include<cstring>
#include<string>
#include<iostream>
using namespace std;
 

void test(char m[],int n[])
{
	cout<<"inTest:"<<&m<<endl;
	cout<<"inTest:"<<&n<<endl;
}
int main()
{
    //string-->char*
    //c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同
    //这个数组的数据是临时的，当有一个改变这些数据的成员函数被调用后，其中的数据就会失效。
    //因此要么现用先转换，要么把它的数据复制到用户自己可以管理的内存中
    
    // const char *c;
    // string s = "1234";
    // c = s.c_str();
    // cout<<c<<endl;
    // s = "abcde";
    // cout<<c<<endl;
	char a[8]="hello";
	char b[9]="world";
	char c[10]={'a','b'};
	// test(a,c);
	cout<<a<<endl;//hello
	cout<<&a<<endl;
	cout<<c<<endl;//地址
	cout<<&c<<endl;//与c等价
	cout<<&c[0]<<endl;//与c等价
}

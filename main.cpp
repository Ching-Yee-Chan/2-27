#include <iostream>
#include<fstream>
#include<sys/time.h>
const double INTERVAL = 600;
typedef long long ll;
using namespace std;
const int N = 4e8;
int a[N];
fstream outfile;
void chain(int n)
{
	ll sum = 0;
	for(int i=0;i<n;i++)
		sum += a[i];
}
void mult(int n)
{
	ll sum1(0), sum2(0), sum(0);
	for(int i=0;i<n;i+=2)
	{
		sum1 += a[i];
		sum2 += a[i+1];
	}
	sum = sum1 + sum2;
}
void recursion(int n)
{
	if(n == 1) return;
	else
	{
		for(int i = 0;i<n/2;i++)
			a[i] += a[n-1-i];
		n = n/2;
		recursion(n);
	}
}
void fenzhi(int n)
{
	for(int m = n;m>1;m/=2)
		for(int i=0;i<m/2;i++)
			a[i] = a[i*2] + a[i*2+1];
}
void init(int n)
{
	for(int i=0;i<n;i++)
        a[i] = i;
}
void timing(void (*func)(int), int n)
{
    timeval tv_begin, tv_end;
    int counter(0);
    gettimeofday(&tv_begin, 0);
    double time = 0;
    while(INTERVAL>time)
    {
        func(n);
        gettimeofday(&tv_end, 0);
        counter++;
        time = ((ll)tv_end.tv_sec - (ll)tv_begin.tv_sec)*1000.0 + ((ll)tv_end.tv_usec - (ll)tv_begin.tv_usec)/1000.0;
    }
    outfile<<time/counter<<","<<counter<<",";
    cout<<time/counter<<","<<counter<<'\t';
}
int main()
{
	init(N);
	outfile.open("output-2.txt", ios::out);
	for(int i=1;i<N;i*=2)
    {
        //cout<<i<<" starts!"<<endl;
        cout<<i<<'\t';
        timing(chain, i);
        timing(mult, i);
        timing(recursion, i);
        init(N);
        timing(fenzhi, i);
        init(N);
        outfile<<endl;
        cout<<endl;
        //cout<<i<<" ends!"<<endl;
    }
    return 0;
}

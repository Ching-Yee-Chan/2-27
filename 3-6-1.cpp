#include<sys/time.h>
#include <iostream>
#include<fstream>
const double INTERVAL = 600;
typedef long long ll;
using namespace std;
fstream outfile("output-2.txt", ios::out);
const int N = 65536;
int a[N];
ll sum(0), sum1(0), sum2(0);
inline void timing(void (*func)())
{
	timeval tv_begin, tv_end;
	int counter(0);
	gettimeofday(&tv_begin, 0);
	double time = 0;
	while (INTERVAL > time)
	{
		gettimeofday(&tv_end, 0);
		func(); 
		counter++;
		time = ((ll)tv_end.tv_sec - (ll)tv_begin.tv_sec) * 1000.0 + ((ll)tv_end.tv_usec - (ll)tv_begin.tv_usec) / 1000.0;
	}
	outfile << time / counter << "," << counter << ",";
	cout << time / counter << "," << counter << '\t';
}
inline void init() {
	for (int i = 0;i < N;i++)
		a[i] = i;
}
template<int N>
class Loop {
public:
	static inline void chain() {
		sum += a[N - 1];
		Loop<N-1>::chain();
	}
	static inline void mult() {
		sum1 += a[N - 2];
		sum2 += a[N - 1];
		Loop<N - 2>::mult();
	}
	static inline void fenzhi() {
		Loop<N / 2>::fenzhi_inner(N);
		Loop<N / 2>::fenzhi();
	}
	static inline void fenzhi_inner(int tot) {
		a[tot/2 - N] = a[tot - 2 * N] + a[tot - 2 * N + 1];
		Loop<N - 1>::fenzhi_inner(tot);
	}
	
	static inline void run() {
		init();
		cout << N << '\t';
		outfile<<N<<','; 
		timing(Loop<N>::chain);
		timing(Loop<N>::mult);
		timing(Loop<N>::fenzhi);
		outfile << endl;
		cout << endl;
		Loop<N / 2>::run();
	}
};

template<>
class Loop<1>{
public:
	static inline void fenzhi() {
		return;
	}
	static inline void run() {
		return;
	}
	static inline void fenzhi_inner(int tot) {
		a[tot / 2 - 1] = a[tot - 2] + a[tot - 1];
	}
	static inline void chain() {
		sum += a[0];
	}
};

template<>
class Loop<0> {
public:
	static inline void mult() {
		return;
	}
};
int main()
{
	Loop<N>::run();
	return 0;
}


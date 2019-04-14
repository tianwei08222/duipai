#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) ((a)+rand()%((b)-(a)+1))
#define pb push_back
const int N = 1e5 + 10;

stringstream ss;
vector<int> v;

int main( int argc, char *argv[] )
{
    ///freopen("C:\\Users\\Administrator\\Desktop\\data.in","r",stdin);
    freopen("C:\\Users\\Administrator\\Desktop\\data.out","w",stdout);
    int seed=time(NULL);
    if(argc)
    {
        ss.clear();
        ss<<argv[1];
        ss>>seed;
    }
    srand(seed);
    //以上为随机数初始化，请勿修改
    //random(a,b)生成[a,b]的随机整数

    //以下写你自己的数据生成代码
	int t=1;
	while(t--) {
	    int n=100000;
        cout<<n<<endl;
        v.clear();
        for(int i=1;i<=n;i++) v.push_back(i);
        for(int i=0;i<n-1;i++) cout<<v[i]<<" ";
        cout<<v[n-1]<<endl;
	}
    return 0;
}
/*
3 4
*aa
aaaa
*/

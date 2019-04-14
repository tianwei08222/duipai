#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>

#define maxn 500005
#define MAXN 500005
#define mem(a,b) memset(a,b,sizeof(a))
const int N=200005;
const int M=200005;
const int INF=0x3f3f3f3f;
using namespace std;
int n;
struct Edge{
    int v,next;
    int cap,flow;
}edge[MAXN*20];//注意这里要开的够大。。不然WA在这里真的想骂人。。问题是还不报RE。。
int cur[MAXN],pre[MAXN],gap[MAXN],path[MAXN],dep[MAXN];
int cnt=0;//实际存储总边数
void isap_init()
{
    cnt=0;
    memset(pre,-1,sizeof(pre));
}
void isap_add(int u,int v,int w)//加边
{
    edge[cnt].v=v;
    edge[cnt].cap=w;
    edge[cnt].flow=0;
    edge[cnt].next=pre[u];
    pre[u]=cnt++;
}
void add(int u,int v,int w){
    isap_add(u,v,w);
    isap_add(v,u,0);
}
bool bfs(int s,int t)//其实这个bfs可以融合到下面的迭代里，但是好像是时间要长
{
    memset(dep,-1,sizeof(dep));
    memset(gap,0,sizeof(gap));
    gap[0]=1;
    dep[t]=0;
    queue<int>q;
    while(!q.empty())
    q.pop();
    q.push(t);//从汇点开始反向建层次图
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=pre[u];i!=-1;i=edge[i].next)
        {
            int v=edge[i].v;
            if(dep[v]==-1&&edge[i^1].cap>edge[i^1].flow)//注意是从汇点反向bfs，但应该判断正向弧的余量
            {
                dep[v]=dep[u]+1;
                gap[dep[v]]++;
                q.push(v);
                //if(v==sp)//感觉这两句优化加了一般没错，但是有的题可能会错，所以还是注释出来，到时候视情况而定
                //break;
            }
        }
    }
    return dep[s]!=-1;
}
int isap(int s,int t)
{
    if(!bfs(s,t))
    return 0;
    memcpy(cur,pre,sizeof(pre));
    //for(int i=1;i<=n;i++)
    //cout<<"cur "<<cur[i]<<endl;
    int u=s;
    path[u]=-1;
    int ans=0;
    while(dep[s]<=n)//迭代寻找增广路,n为节点数
    {
        if(u==t)
        {
            int f=INF;
            for(int i=path[u];i!=-1;i=path[edge[i^1].v])//修改找到的增广路
                f=min(f,edge[i].cap-edge[i].flow);
            for(int i=path[u];i!=-1;i=path[edge[i^1].v])
            {
                edge[i].flow+=f;
                edge[i^1].flow-=f;
            }
            ans+=f;
            u=s;
            continue;
        }
        bool flag=false;
        int v;
        for(int i=cur[u];i!=-1;i=edge[i].next)
        {
            v=edge[i].v;
            if(dep[v]+1==dep[u]&&edge[i].cap-edge[i].flow)
            {
                cur[u]=path[v]=i;//当前弧优化
                flag=true;
                break;
            }
        }
        if(flag)
        {
            u=v;
            continue;
        }
        int x=n;
        if(!(--gap[dep[u]]))return ans;//gap优化
        for(int i=pre[u];i!=-1;i=edge[i].next)
        {
            if(edge[i].cap-edge[i].flow&&dep[edge[i].v]<x)
            {
                x=dep[edge[i].v];
                cur[u]=i;//常数优化
            }
        }
        dep[u]=x+1;
        gap[dep[u]]++;
        if(u!=s)//当前点没有增广路则后退一个点
        u=edge[path[u]^1].v;
     }
     return ans;
}

struct sair{
    int num;
    int mp[505];
}mp[505];

int main(){
    std::ios::sync_with_stdio(false);
    int m,s,t,k;
    cin>>n>>m>>k;
    int a,b,c;
    isap_init();
    s=0,t=n+m+1;
    int ck=t+1;
    for(int i=1;i<=n;i++)
        add(s,i,1);
    add(s,ck,k);
    for(int i=1;i<=n;i++){
        cin>>a;
        for(int j=1;j<=a;j++){
            cin>>b;
            add(i,n+b,1);
        }
    }
    for(int i=1;i<=m;i++)
        add(n+i,t,1);
    for(int i=1;i<=n;i++){
        add(ck,i,1);
    }
    int tmp=n;
    n=ck+1;
    int ans=isap(s,t);
    cout<<ans<<endl;
}

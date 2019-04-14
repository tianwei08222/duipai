#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#define INF 0x2fffffff
using namespace std;
const int maxn = 1000+20 ;
int dis[maxn] ;
int vis[maxn] ;
int head[maxn];
int insect;
int n , k , t ;
int m ;
int testn,testm,testk ;
int ans = 0 ;
struct node{
	int u ; int v ; int cap ; int flow ;int next ;
}e[maxn*100];
void add(int x , int y , int w )
{
	e[ans] = { x , y , w , 0 , head[x] } ;
	head[x] = ans++ ;
	e[ans] = { y , x , 0 , 0 , head[y] } ;
	head[y] = ans++ ;
 }
 void getmap()
 {
 	ans = 0 ;
 	memset(head,-1,sizeof(head)) ;
 	for(int i = 1 ; i <= n ; i ++)
    {
        int num ;
        scanf("%d",&num) ;
        for(int j = 1 ; j <= num ; j ++)
        {
            int x ;
            scanf("%d",&x) ;
            add(i,x + n,1) ;
        }
    }
	 for(int i = 1 ; i <= n ; i++)
	 {
	 	add(0,i,2) ;
	 }
	 for(int i = 1 ; i <= m ; i ++)
     {
         add(n + i , insect , 1) ;
     }
 }
 bool bfs(int st ,int ed)
 {
    memset(vis,0,sizeof(vis)) ;
    memset(dis,-1,sizeof(dis)) ;
 	queue<int>q ;
	q.push(st) ;
	dis[st] = 0 ;
	vis[st] = 1 ;
	while(!q.empty())
    {
    	int u = q.front() ; q.pop() ;
    	for(int i = head[u] ; i != -1 ; i = e[i].next )
    	{
    		node E = e[i] ;
    		if(!vis[E.v] && E.cap>E.flow)
    		{
    			vis[E.v] = 1 ;
    			dis[E.v] = dis[u] + 1 ;
    			if(E.v == ed) return true ;
    			q.push(E.v) ;
			}
		}
	 }
	 return false ;
 }
 int dfs(int st , int ed , int a)
 {
    if(st == ed||a == 0 ) return a ;
    int num = 0 ;
 	for( int i = head[st] ; i != -1 ; i = e[i].next )
 	{
 		node E = e[i] ;
 		int f ;
 		if(dis[E.v] == dis[st] + 1 && (f = dfs(E.v , ed , min(a, E.cap - E.flow)))>0)
 		{
 			e[i].flow+= f ;
 			e[i^1].flow-= f ;
 			a -= f ;
 			num+= f ;
 			if(!a) break ;
		 }
	 }
	 return num ;
 }
int main()
{
	while(scanf("%d %d %d",&n,&m,&k) !=EOF)
	{


            insect = m + n + 1 ;
			getmap() ;
			int num = 0 ;
			while(bfs(0,insect))
			{
				num+=dfs(0,insect,INF) ;
			}
			printf("%d\n",min(num,n + k)) ;



	}
  }

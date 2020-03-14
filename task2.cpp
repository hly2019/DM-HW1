#include<iostream>//若商家和
#include<math.h>
#include<cstring>
#include<iomanip>
#define INF 10000000000.00
#define Inf 1000000000000.00
using namespace std;
double x[6000],y[6000];//每个节点的坐标；
int u[8000],v[8000];
double arr[5500][5500];//记录两点间距离；
int ep,eb,ec;//
double dp,db,dc;//
double d(int u,int v);//计算两个节点u，v之间的距离；
double locax(int,double);//求对应点的x坐标
double locay(int,double);//求对应点的y
double dis[6000];//起始点到各点的最短距离；
void dijkstra(int);
bool vis[6000];//判断是否已经走过；    
int n,m;
int main(){
    cin>>n;
    for(int i=0;i<=n+10;i++)
        for(int j=0;j<=n+10;j++)
            arr[i][j]=Inf;
    for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
    cin>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        u[i]=x;
        v[i]=y;
        arr[u[i]][v[i]]=d(u[i],v[i]);//u v是节点的编号；
        arr[v[i]][u[i]]=d(u[i],v[i]);
    }
    cin>>ep>>dp;
    x[n+1]=locax(ep,dp);
    y[n+1]=locay(ep,dp);
    arr[u[ep]][n+1]=d(u[ep],n+1);
    arr[n+1][u[ep]]=d(u[ep],n+1);
    arr[v[ep]][n+1]=d(v[ep],n+1);
    arr[n+1][v[ep]]=d(v[ep],n+1);
    cin>>eb>>db;
    x[n+2]=locax(eb,db);
    y[n+2]=locay(eb,db);
    arr[u[eb]][n+2]=d(u[eb],n+2);
    arr[n+2][u[eb]]=d(u[eb],n+2);
    arr[v[eb]][n+2]=d(v[eb],n+2);
    arr[n+2][v[eb]]=d(v[eb],n+2);
    cin>>ec>>dc;
    x[n+3]=locax(ec,dc);
    y[n+3]=locay(ec,dc);
    arr[u[ec]][n+3]=d(u[ec],n+3);
    arr[n+3][u[ec]]=d(u[ec],n+3);
    arr[v[ec]][n+3]=d(v[ec],n+3);
    arr[n+3][v[ec]]=d(v[ec],n+3);//前n个节点是路口，后三个节点为小哥商贩顾客；
    if(ep==eb){
        arr[n+1][n+2]=d(n+1,n+2);
        arr[n+2][n+1]=d(n+1,n+2);
    }
    if(eb==ec){
        arr[n+2][n+3]=d(n+2,n+3);
        arr[n+3][n+2]=d(n+2,n+3);
    }
    if(ep==ec){
        arr[n+1][n+3]=d(n+1,n+3);
        arr[n+3][n+1]=d(n+1,n+3);
    }
    for(int i=0;i<=n+10;i++)arr[i][i]=0.0;
    for(int i=0;i<=n+3;i++)dis[i]=Inf;
    for(int i=0;i<=n+3;i++)vis[i]=0;
    dijkstra(n+3);
    double a=dis[n+2];
    for(int i=0;i<=n+3;i++)dis[i]=Inf;
    for(int i=0;i<=n+3;i++)vis[i]=0;
    dijkstra(n+2);
    double b=dis[n+1];
    //cout<<setprecision(3)<<a+b<<endl;
    double ans=a+b;
    printf("%.2f", ans);
    //system("pasue");
    return 0;
}
double locax(int e,double de){//在道路e上，距离u[e]的距离是d，返回坐标
double x0;
x0=x[v[e]]-x[u[e]];
double z=d(u[e],v[e]);
return x0*de/z+x[u[e]];
}
double locay(int e,double de){
double y0;
y0=y[v[e]]-y[u[e]];
double z=d(u[e],v[e]);
return y0*de/z+y[u[e]];
}
double d(int l,int s){//节点x，y之间的距离；
double p=x[l]-x[s];
double q=y[l]-y[s];
double ans= sqrt(p*p+q*q);
return ans;
}
void dijkstra(int x){//从x开始的最短距离;
for(int i=1;i<=n+3;i++){
    dis[i]=arr[x][i];
}
vis[x]=1;
for(int i=1;i<=n+3;i++){
    double minn=INF;
    int tem=0;
    for(int j=1;j<=n+3;j++){
        if(!vis[j]&&dis[j]<minn){
            minn=dis[j];
            tem=j;
        }
        }
    vis[tem]=1;
    for(int l=1;l<=n+3;l++){
        if(arr[tem][l]+dis[tem]<dis[l]){
            dis[l]=arr[tem][l]+dis[tem];
        }
    }
    }
}
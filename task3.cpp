#include<iostream>
#include<cstring>
#define INF 10000000
using namespace std;
bool judge(int x);//返回第x节课如果加1学时是否会延长最短毕业时间;
int arr[1000][1000];//pt图邻接矩阵;
int t[1000];//每个工序完成所需时间;
int c[1000][1000];//每个课程的前序课程数量;
int key;//关键路径长度;
int zdu[1000];//每个点的正度
int fdu[1000];//每个节点的负度
int n;//课程数量
int brr[1000][1000],zdu1[1000],fdu1[1000];
int u[1000];//新的排序。即新的第一个为u[0]，存的是原来的序号
bool vis[1000];
int sum;
int dis[1000];
int edge[1000][1000];
int tao[1000];
void pt();
void pt_();
void sort();
int yw(int);
int main(){
    cin>>n;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            arr[i][j]=INF;
    for(int i=1;i<=n;i++){
        cin>>t[i];
        cin>>c[i][0];//前继结点个数
        for(int j=1;j<=c[i][0];j++)cin>>c[i][j];//输入前继结点
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=c[i][0];j++){
            arr[c[i][j]][i]=t[c[i][j]];
            zdu[c[i][j]]++;
            fdu[i]++;
            edge[c[i][j]][i]++;
        }
    }
    for(int i=1;i<=n;i++){
        bool judge1=0;
        for(int j=1;j<=n;j++){
            if(arr[i][j]<INF){
                judge1=1;
                break;
            }
        }
        if(!judge1){
            arr[i][n+1]=t[i];
            edge[i][n+1]=1;
            fdu[n+1]++;
            zdu[i]++;
        }
    }
    for(int i=1;i<=n;i++){
        bool judge2=0;
        for(int j=1;j<=n;j++){
            if(arr[j][i]<INF){
                judge2=1;
                break;
            }
        }
        if(!judge2){
            arr[0][i]=0;//设置虚拟的初始结点v0，其所需时间为0;
            edge[0][i]=1;
            zdu[0]++;
            fdu[i]++;
        }
    }
    for(int i=0;i<=n+1;i++){
        zdu1[i]=zdu[i];
        fdu1[i]=fdu[i];
    }
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=n+1;j++)
            brr[i][j]=arr[i][j];
    sort();
    pt();
    pt_();
    for(int i=1;i<=n;i++)
    cout<<dis[i]+t[i]<<" "<<yw(i)<<endl;
    //system("pause");
    return 0;
}

void sort(){
while(1){
    bool judge=0;
    for(int i=0;i<=n+1;i++){
        if(fdu1[i]==0&&!vis[i]){//发现一个负度为零的点,且之前没有访问过；
            vis[i]=1;
            judge=1;
            u[sum++]=i;//重新编号
            zdu[i]=0;
            for(int j=0;j<=n+1;j++){
                if(edge[i][j]==1){
                    fdu1[j]--;
                    brr[i][j]=INF;//删掉这个节点;
                }
            }
        break;

        }
    }
    if(!judge)break;
}
}
void pt(){
    dis[u[0]]=0;
    for(int j=1;j<=n+1;j++){
        int maxn=-INF;
        for(int i=0;i<=n+1;i++){
            if(edge[u[i]][u[j]]==1&&dis[u[i]]+arr[u[i]][u[j]]>maxn){
                 maxn=dis[u[i]]+arr[u[i]][u[j]];
            }
               
        }
        dis[u[j]]=max(maxn,dis[u[j]]);

    }
}
void pt_(){
    tao[u[n+1]]=dis[u[n+1]];
    for(int j=n;j>=0;j--){
        int minn=INF;
        for(int i=0;i<=n+1;i++){
            if(arr[u[j]][u[i]]<INF&&tao[u[i]]-arr[u[j]][u[i]]<minn)
                 minn=tao[u[i]]-arr[u[j]][u[i]];
        }
        tao[u[j]]=minn;
    }
}
int yw(int i){
    if(tao[i]-dis[i]>=1)return 0;
    else return 1;
}
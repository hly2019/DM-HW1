#include<iostream>
#include<cstring>
using namespace std;
int arr[210][210][200];
int out[1100];//输出的边
int du[1100];//节点的度;
int ass[1100];
bool j[1100];//判断点在不在图上
bool nbridge(int,int);//两点之间的连线是不是桥
bool judge(int);//判断图是不是联通图，若是返回true；
void dfs(int );
int main(){
    int n;
    cin>>n;
    int p=0,q=0;
    for(int i=0;i<=n-1;i++){
        cin>>p>>q;
        arr[p][q][0]++;
        arr[q][p][0]++;
        arr[p][q][arr[p][q][0]]=i;//三维数组，第三维第零个元素是重边个数，从第一个开始存边的序号；
        arr[q][p][arr[q][p][0]]=i;
        du[p]++;
        du[q]++;
        j[p]=true;
        j[q]=true;
    }
    int start=p;
    for(int i=0;i<=101;i++){
        if(du[i]%2==1){
            start=i;
            break;
        }
    }
int present=start,sum=0;//sum为输出边个数
while(1){
    int flag1=0,flag2=0,temp=0;
    for(int i=0;i<=101;i++){
        if(nbridge(present,i)){//判断是否有非桥;
            int t=arr[present][i][0];
            out[sum++]=arr[present][i][t];
            arr[present][i][0]--;
            arr[i][present][0]--;
            du[i]--;
            du[present]--;
            flag2=1;//有非桥
            present=i;
            break;
        }
        if(!nbridge(present,i)&&arr[present][i][0]==1){//是个桥;排除不相连的点;
            flag1=1;
            temp=i;//记下来
        }
    }
    if(flag2==0&&flag1==1){
        int t=arr[present][temp][0];
        out[sum++]=arr[present][temp][t];
        arr[present][temp][0]--;
        arr[temp][present][0]--;
        du[present]--;
        du[temp]--;
        present=temp;
    }

    if(flag2==0&&flag1==0){
        break;
    }
}

for(int i=0;i<=sum-1;i++)
    cout<<out[i]+1<<" ";
    system("pause");
    return 0;
}
bool nbridge(int a,int b){//判断a,b之间的连线是不是桥，若是则返回false
if(arr[a][b][0]>=2){
    return true;
}
else if(arr[a][b][0]==1){
    arr[a][b][0]--;
    arr[b][a][0]--;
    if(judge(b)&&judge(a)){
        arr[b][a][0]++;
        arr[a][b][0]++;
        return true;//如果去掉a b间的边后图连通，那么不是桥（judge若联通则返回true）
    }
    else {
        arr[b][a][0]++;
        arr[a][b][0]++;
        return false;
    }
}
else return false;
}
bool judge(int a){//判断从a点开始能否到达途中所有点
memset(ass,0,sizeof(ass));
dfs(a);
for(int i=0;i<=101;i++)
    if(ass[i]==0&&j[i]&&du[i]!=0)return false;//j[i]有问题。应该是
 return true;

}
void dfs(int x){
    ass[x]=1;
    for(int i=0;i<=101;i++){
        if(arr[x][i][0]!=0&&ass[i]==0)
            dfs(i);
    }
}
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
#define MAXSIZE 100

/*-------栈的设置-------*/
//定义栈中元素
typedef struct{
    int x;  //记录x坐标
    int y;  //记录y坐标
    int d;  //记录移动方向
}point;
//定义栈的结构
typedef struct{
    point data[MAXSIZE];
    int top;
}MazeStack;
//设置空栈
void setNull(MazeStack *s){
    s->top = -1;
}
//判断栈是否为空
bool isEmpty(MazeStack *s){
    if(s->top>=0) return false;
    else return true;
}
//进栈操作
MazeStack * push(MazeStack *s, point x){
    if(s->top>MAXSIZE-1){
        printf("栈上溢出！\n");
        return s;
    } else{
        s->top++;
        s->data[s->top] = x;
        return s;
    }
}
//退栈操作
point * pop(MazeStack *s){
    if(isEmpty(s)){
        printf("栈为空！\n");
        return NULL;
    } else{
        s->top--;
        return &(s->data[s->top+1]);
    }
}
//取栈顶元素
point * getTop(MazeStack *s){
    if(isEmpty(s)){
        printf("栈为空！\n");
        return NULL;
    } else{
        return &(s->data[s->top]);
    }
}

int chess[MAXSIZE][MAXSIZE] = {0};  //初始化棋盘
int count = 1;      //记录已走的步数
int move[8][2] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}}; //定义马的移动方向

//给定位置和棋盘大小的周游函数
void travel(int x, int y, int N);

int main(){
    int N, xp, yp, i, j;
    cout<<"-->>Welcome to the chessboard travel program.\n-->>This program calculates the travel path from any position (x,y) for given chessboard size (n).\n";
    cout<<"\n-->>Please input the chessboard size (n):\n";
    cin>>N;
    cout<<"\n-->>Please input the x position of starting point:\n";
    cin>>xp;
    cout<<"\n-->>Please input the y position of starting point:\n";
    cin>>yp;
    cout<<"\n-->>Please wait.\n"<<endl;

    //设置边界
    for(i=0;i<N+4;i++){
        for(j=0;j<N+4;j++){
            if(i==0 || i==1 || i==N+2 || i==N+3 || j==0 || j==1 || j==N+2 || j==N+3){
                chess[i][j]=-1;
            }
        }
    }

    travel(xp+1,yp+1, N);
    return 0;
}

void travel(int x, int y, int N){
    int i=0;    //i为移动方向的选择
    int m,n;
    int a,b;
    point start,*p,*q;  //初始化两个点

    chess[x][y]=1;  //将起点设为1
    MazeStack *s;   //设置栈
    s = (MazeStack*)malloc(sizeof(MazeStack));  //给栈分配空间
    setNull(s); //初始化栈

    start.x=x;  //起点的设置
    start.y=y;
    p=(point*)malloc(sizeof(point));    //给点分配空间

    s = push(s, start); //将起点压入栈

    while(count<N*N){
        for(;i<8;i++){
            a = x+move[i][0];
            b = y+move[i][1];
            if(chess[a][b]==0){
                break;
            }
        }
        if(i<8){
            chess[a][b]=++count;
            q = pop(s); //从栈中取点
            q->d = i;
            s = push(s, *q);    //将点压入栈中
            point nw;   //将新点设为现在的点
            nw.x = a;
            nw.y = b;
            s = push(s, nw);    //将点压入栈中
            x = a;  //将新点的x,y设为现在的x,y坐标
            y = b;
            i = 0;
        } else {
            count--;
            chess[x][y]=0;
            pop(s); //无效点退栈
            if(s->top==-1){ //无解的情况
                printf("no solution.\n");
                break;
            }
            point *now = getTop(s); //取栈顶点为现在的点
            x = now->x;
            y = now->y;
            i = now->d;
            i++;    //尝试下一个方向
        }
    }
    //输出路径
    if(count==N*N){
        while(!isEmpty(s)){
        p=pop(s);
        if(s->top!=-1)
            printf("(%d, %d)<-", p->x-1, p->y-1);
        else printf("(%d, %d)", p->x-1, p->y-1);
        }
    }
    printf("\n");
    //输出棋盘
    for(m=2;m<N+2;m++){
        for(n=2;n<N+2;n++){
            cout<<chess[m][n]<<"\t";
        }
        cout<<endl;
    }
}

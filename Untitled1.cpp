#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define MAXSIZE 100
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

int chess[12][12] = {0};
int count = 1;      //记录已走的步数
int move[8][2] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};

void travel(int x, int y);

int main(){
    int N, xp, yp, i, j;
    cout<<"Welcome to the chessboard program, this program calculates the travel path from any position (x,y) for given chessboard size (n).\n";
    cout<<"Please input the chessboard size (n):\n";
    cin>>N;
    cout<<"Please input the x position of starting point:\n";
    cin>>xp;
    cout<<"Please input the y position of starting point:\n";
    cin>>yp;
    cout<<"Please wait."<<endl;
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            if(i==0 || i==1 || i==10 || i==11 || j==0 || j==1 || j==10 || j==11){
                chess[i][j]=-1;
            }
        }
    }
    travel(2,2);
    return 0;
}


void travel(int x, int y){
    int i=0;
    int m,n;
    int a,b;
    point start,*p,*q;

    chess[x][y]=1;
    MazeStack *s;
    s = (MazeStack*)malloc(sizeof(MazeStack));
    setNull(s);

    start.x=x;
    start.y=y;
    p=(point*)malloc(sizeof(point));

    //将起点压入栈
    s = push(s, start);
    while(count<64){
        for(;i<8;i++){
            a = x+move[i][0];
            b = y+move[i][1];
            if(chess[a][b]==0){
                break;
            }
        }
        if(i<8){
            chess[a][b]=++count;
            q = pop(s);
            q->d = i;
            s = push(s, *q);
            point nw;
            nw.x = a;
            nw.y = b;
            s = push(s, nw);
            x = a;
            y = b;
            i = 0;
        } else {
            count--;
            chess[x][y]=0;
            pop(s);
            point *now = getTop(s);
            x = now->x;
            y = now->y;
            i = now->d;
            i++;
        }
    }
    if(count==64){
        while(!isEmpty(s)){
        p=pop(s);
        printf("(%d, %d)\t", p->x, p->y);
        }
    }

    printf("\n");
    for(m=2;m<10;m++){
        for(n=2;n<10;n++){
            cout<<chess[m][n]<<"\t";
        }
        cout<<endl;
    }
}

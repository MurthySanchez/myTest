#include <graphics.h>      // 就是需要引用这个图形库
#include <stdio.h>
void main()
{
    initgraph(640, 480);   // 这里和 TC 略有区别
    circle(200, 200, 100); // 画圆，圆心(200, 200)，半径 100
    getch();               // 按任意键继续
    closegraph();          // 关闭图形界面
}


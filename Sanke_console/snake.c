#include "snake.h"

/*全局变量定义*/
Snake snake;
Food food;
char now_Dir = RIGHT;       //当前蛇头方向变量
char direction = RIGHT;     //预期蛇头方向变量

/*主菜单实现*/
void GotoXY(int x,int y){
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);  //这个函数返回标准输出设备的句柄，表示当前程序的标准输出流（通常是控制台窗口）。
    cor.X = (SHORT)x;
    cor.Y = (SHORT)y;
    SetConsoleCursorPosition(hout,cor);
}

void Hide(){
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    /*
    Windows API 对struct _CONSOLE_CURSOR_INFO的定义
    typedef struct _CONSOLE_CURSOR_INFO {
    DWORD dwSize;       // 光标的大小（百分比）
    BOOL  bVisible;     // 光标是否可见
    } CONSOLE_CURSOR_INFO;*/

    CONSOLE_CURSOR_INFO cor_info = {1,0};
    SetConsoleCursorInfo(hout,&cor_info);
}

int Menu(){
    GotoXY(40,12);
    printf("欢迎来到贪吃蛇小游戏");
    GotoXY(43,14);
    printf("1.开始游戏");
    GotoXY(43,16);
    printf("2.帮助");
    GotoXY(43,18);
    printf("3.关于");
    GotoXY(43,20);
    printf("其他任意键退出");
    Hide();                                  //隐藏光标

    char ch;
    int result=0;
    ch = (char)_getch();                           //从控制台读取用户输入的一个字符 
    switch (ch){
        case '1': result=1 ; break;
        case '2': result=2 ; break;
        case '3': result=3 ; break;
    }
    system("cls");
    return result;
}

/*关于菜单的实现*/
void About(){
    GotoXY(30,12);
    printf("杭州电子科技大学--程序设计综合实践项目");
    GotoXY(43,14);
    printf("贪吃蛇游戏");
    GotoXY(43,16);
    printf("按任意键返回上级菜单");
    Hide();
    int d = _getch();
    system("cls");
}

/*帮助菜单实现*/
void Help(){
    GotoXY(40,12);
    printf("w上");
    GotoXY(40,14);
    printf("s下");
    GotoXY(40,16);
    printf("a左");
    GotoXY(40,18);
    printf("d右");
    GotoXY(40,20);
    printf("当蛇撞到自身或撞墙时游戏结束");
    GotoXY(45,22);
    printf("按任意键返回上级菜单");
    Hide();
    int d = _getch();
    system("cls");
}

/*初始化地图函数*/
void InitMap(){
    Hide();
    //设置蛇头位置在地图的中间
    snake.snakeNode[0].x = MAP_WIDTH/2 -1;
    snake.snakeNode[0].y = MAP_HEIGHT/2 -1;
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);     //将光标移到蛇头位置
    printf("@");                                            //输出蛇头
    snake.length = 3;                                       //设置蛇长的初始值为3节
    snake.speed = 250;
    now_Dir = RIGHT;                                        //当前蛇头方向
    
    //显示蛇身
    for (int i=1 ;i<snake.length; i++){
        //设置蛇身的纵坐标位置和蛇头位置相同
        snake.snakeNode[i].y = snake.snakeNode[0].y;
        //设置蛇身坐标位置，蛇身在蛇头左边，所以横坐标依次减一
        snake.snakeNode[i].x = snake.snakeNode[i-1].x - 1;
        //移动光标到蛇身位置
        GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
        //输出蛇身
        printf("o");

    }

    //生成地图上下边界
    for (int i=0; i<MAP_WIDTH; i++){
        GotoXY(i,0);
        printf("-");
        GotoXY(i,MAP_HEIGHT-1);
        printf("-");
    }
    //生成地图左右边界
    for (int i=1; i<MAP_HEIGHT; i++){
        GotoXY(0,i);
        printf("|");
        GotoXY(MAP_WIDTH-1,i);
        printf("|");
    }

    //生成食物
    PrintFood();
    //得分说明
    GotoXY(5,50);
    printf("当前得分：0");
}

/*生成食物的函数*/
void PrintFood(){
    int flag = 1;
    while (flag){
        flag = 0;
        //设置随机的食物坐标位置
        food.x = rand() % (MAP_WIDTH-2) + 1;
        food.y = rand() % (MAP_HEIGHT-2) + 1;
        //循环判断食物位置和蛇的位置是否重叠，如果重叠，则需要重新设置食物的位置
        for (int k=0; k <=snake.length -1; k++){
            if (snake.snakeNode[k].x==food.x && snake.snakeNode[k].y==food.y){
                flag = 1;            //位置有重叠，需要继续循环
                break;
            }
        }
    }
    GotoXY(food.x, food.y);
    printf("$");
}

/*蛇移动函数的实现，返回值为1表示蛇继续移动，为0表示蛇停止移动*/
int MoveSnake(){
    Snakenode temp;
    int flag = 0; 
    temp = snake.snakeNode[snake.length-1];          //记录蛇尾
    for (int i=snake.length-1; i>=1; i--){
        snake.snakeNode[i] = snake.snakeNode[i-1];   //将所有蛇身向前移动一位
    }GotoXY(snake.snakeNode[1].x,snake.snakeNode[1].y);
    printf("o");                                     //在原来蛇头的位置打印一个蛇身节点o，其他蛇身不需要显示

    //非阻塞地响应键盘输入事件
    if (_kbhit()){                           //检查当前是否有键盘输入，若有，则返回一个非0的值，否则返回0
        direction = (char)_getch();
        switch (direction){
            case UP:                         //按下w键
                if (now_Dir != DOWN){        //如果蛇头向上，按向下移动的w键时不起作用
                    now_Dir = direction;
                }break;
            case DOWN:                       //按下s键
                if (now_Dir != UP){          //如果蛇头向上，按向下移动的s键时不起作用
                    now_Dir = direction;
                }break;
            case LEFT:                       //按下a键
                if (now_Dir != RIGHT){       //如果蛇头向上，按向下移动的a键时不起作用
                    now_Dir = direction;
                }break;
            case RIGHT:                      //按下d键
                if (now_Dir != LEFT){        //如果蛇头向上，按向下移动的d键时不起作用
                    now_Dir = direction;
                }break;
        }
    }
    switch (now_Dir){                        //根据现在的方向改变蛇头位置
        case UP:    snake.snakeNode[0].y--;   break;        //向上移动
        case DOWN:  snake.snakeNode[0].y++;   break;        //向下移动
        case LEFT:  snake.snakeNode[0].x--;   break;        //向左移动
        case RIGHT: snake.snakeNode[0].x++;   break;        //向右移动
    }

    //显示蛇头
    GotoXY(snake.snakeNode[0].x,snake.snakeNode[0].y);
    printf("@");

    //判断是否吃到了食物，如果蛇头位置和食物位置相同表示吃到了食物
    if (snake.snakeNode[0].x==food.x&&snake.snakeNode[0].y==food.y){
        snake.length++;             //吃到食物，蛇长加1节
        flag = 1;                   //flag为1，表示迟到食物；为0，表示没有吃到食物
        snake.snakeNode[snake.length-1] = temp;     //temp是移动前蛇尾的位置
    } 

    //若没有吃到食物，则原来的蛇尾显示一个空格，去掉原来的蛇尾
    if (!flag){
        GotoXY(temp.x,temp.y);
        printf(" ");
    }//吃到了食物，则需要在地图上重新更新一个食物
    else{
        PrintFood();
        GotoXY(50,5);
        printf("当前得分：%d",snake.length-3);
    }

    //判断是否死亡
    if (!IsCorrect()){
        system("cls");
        GotoXY(45,14);
        printf("Game Over!");
        GotoXY(45,16);
        printf("最终得分：%d",snake.length-3);
        GotoXY(45,18);
        printf("按任意键返回菜单");
        int d = _getch();
        system("cls");
        return 0;
    }

    //调整速度
    SpeedControl();
    Sleep((DWORD)snake.speed);      //将进程挂起一段时间，用于控制蛇的移动速度
    return 1;
}

/*判断是否子撞或撞墙，返回值为0表示自撞或撞墙，否则为1*/
int IsCorrect(){
    //判断蛇头是否撞墙
    if (snake.snakeNode[0].x==0 || snake.snakeNode[0].y==0 || snake.snakeNode[0].x==MAP_WIDTH-1 || snake.snakeNode[0].y==MAP_HEIGHT-1){
        return 0;
    }//判断蛇头和蛇身是否重叠，重叠表示自撞
    for (int i=1; i<snake.length; i++){
        if (snake.snakeNode[0].x==snake.snakeNode[i].x && snake.snakeNode[0].y==snake.snakeNode[i].y){
            return 0;
        }
    }return 1;
}

/*移动速度调整函数*/
void SpeedControl(){
    //根据蛇长调整蛇的移动速度
    switch (snake.length){   
        case 6:   snake.speed=200; break;
        case 9:   snake.speed=180; break;
        case 12:  snake.speed=160; break;
        case 15:  snake.speed=140; break;
        case 18:  snake.speed=120; break;
        case 21:  snake.speed=100; break;
        case 24:  snake.speed=80;  break;
        case 27:  snake.speed=60;  break;
        case 30:  snake.speed=40;  break;
        default:  break;
    }
}

  
#include "snake.c"

int main(){

    srand((unsigned int)time(0));        //生成随机数种子
    int end = 1, result;
    while (end){
        result = Menu();                 //显示主菜单，并根据用户选择菜单选项决定游戏的执行
        switch (result){
            case 1:
                InitMap();               //初始化地图
                while (MoveSnake());       //如果返回0，则蛇停止移动；返回1，蛇继续移动
                break;
            case 2:
                Help();                  //显示帮助信息
                break;
            case 3:
                About();                 //显示关于信息
            case 0:
                end = 0;
                break;    
        }
    }
}


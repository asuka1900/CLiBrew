#include "SSMS.c"

/* 
1.输入学生信息
2.查找学生信息
3.修改学生信息
4.查看课程相关
5.学生成绩统计
6.从磁盘读取学生记录
7.学生记录存磁盘 */

int main(){
    system("chcp 65001");  // 设置终端为UTF-8
    int StuNum=0,CouNum=0,first=1;
    int op;
    int right = 0;
    //创建链表
    STU* head = (STU*)malloc(sizeof(STU));
    if (!head) {
        printf("内存分配失败\n");
        exit(1);
    }memset(head, 0, sizeof(STU));  // 初始化结构体，确保指针为空
    head->next = NULL;
    //读取磁盘信息
    system("mode con cols=130 lines=60");      //设置控制台的宽度为130个字符，高度为60行
    system("color 0E");                        //改变控制台的颜色主题
    int safe = 123456;
    int safeguard;
    int mode;
label1:
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("欢迎来到学生成绩管理系统！");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\n请选择你的身份：教师（1）/学生（2）：");
    scanf("%d", &mode);
    system("cls");
    if (mode == 1) {
        printf("请输入教职工密码：");
        scanf("%d", &safeguard);
        if (safeguard == safe) {
            system("cls");
        }
        else {
            printf("\n\n密码错误！请重新输入...");
            Sleep(1000);
            goto label1;
        }
    }
    else {
        right += 1;
    }
    while(1){
        system("cls");
        op = Menu();
        switch(op){
            case 1: //输入学生信息
                system("cls");
                InputRecord(head,&StuNum,&CouNum,&first);  
                break;
            case 2: 
                system("cls");
                SearchMenu(CouNum,head);
                break;
            case 3: //修改学生信息
                system("cls");
                ModifyRecord(CouNum,StuNum,head,right);
                break;
            case 4:
                system("cls");
                PrintRecordMenu(&head,CouNum); 
                break;
            case 5:
                system("cls");
                StatisticAnalysis(StuNum,CouNum,head); 
                break;
            case 6:
                system("cls");
                // if (first){
                //     SetPosition(POS_X3,POS_Y);
                //     printf("系统中尚无学生成绩信息，请先输入！\n");
                //     system("pause");
                //     break;
                // }
                WriteToFile(head,StuNum,CouNum);
                getch();
                break;
            case 7:      //从磁盘中读取学生信息
                system("cls");
                ReadFromFile(&StuNum,&CouNum,head,&first);
                getch();
                break;
            case 0:
                system("cls");
                printf("退出系统!\n"); 
                freeList(head);  // 释放链表
                exit(0);
            default:
                system("cls");
                printf("输入错误，请重新选择操作!\n"); 
                system("pause");
        }
    }return 0;
}

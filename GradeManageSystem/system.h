#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define STU_NUM 50                //教学班人数上限
#define COURSE_NUM 10             //一学期的课程门数上限
#define NAME_LEN 10               //学生名字（字符串）最大长度
#define POS_X1 35                
#define POS_X2 40
#define POS_X3 45                 //提示“系统中尚无此学生”的起始位置的x坐标值
#define POS_X4 50
#define POS_Y 3
#define RANGE_COUNT (sizeof(ranges) / sizeof(ranges[0]))

//定义学生结构体
typedef struct Student{
    long num;                         //学号
    char name[NAME_LEN];              //学生姓名
    float score[COURSE_NUM];          //各门课成绩
    float sum;                        //各门课总分
    float aver;                       //各门课平均分
    struct Student *next;
}STU;

// 定义分数区间
typedef struct {
    int min;
    int max;
    char label[10];
} GradeRange;





int Menu();
void SearchMenu();
void SetPosition(int x,int y);
STU * createStudent(long num,char *name,float *score,float sum,float aver);
void CalculateScore(STU *current,int CouNum);
void CorrectInfo(STU *stu,STU **head);
void PrintDividor(int pos_X,int *posy);




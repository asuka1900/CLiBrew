#include "system.h"

int Menu(){
    int posy = 5;
    int option;                            //保存用户输入的操作代号
    SetPosition(POS_X3,posy);
    printf("学生管理系统\n");
    //输出系统名称和功能说明之间的两行短横线
    PrintDividor(POS_X1,&posy);
    //输出系统支持的功能和对应的功能代号
    SetPosition(POS_X3,++posy);
    printf("1.输入学生信息");
    SetPosition(POS_X3,++posy);
    printf("2.查找学生信息");
    SetPosition(POS_X3,++posy);
    printf("3.修改学生信息");
    SetPosition(POS_X3,++posy);
    printf("4.学生成绩统计");
    SetPosition(POS_X3,++posy);
    printf("5.查看课程相关");
    SetPosition(POS_X3,++posy);
    printf("6.学生记录写入磁盘");
    SetPosition(POS_X3,++posy);
    printf("7.从磁盘中读取学生记录");
    SetPosition(POS_X3,++posy);
    printf("0.退出");
    posy++;
    PrintDividor(POS_X1,&posy);
    SetPosition(POS_X1,posy);
    printf("请选择你想进行的操作[0~7][： ]\b\b\b");
    scanf("%d",&option);
    return option;
}
 //打印分割线,打印完后posy自动顺延一行
void PrintDividor(int pos_X,int *posy){
    for (int i=0;i<2;i++){
        SetPosition(pos_X,++(*posy));
        for (int j=0;j<55;j++){
            printf("-");
        }
    }(*posy)++;
}

void SetPosition(int x,int y){
    HANDLE hOut;
    COORD pos;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut,pos);
}

//遍历链表
STU * TravelList(STU *head){
    while (head == NULL) return NULL;
    STU *current = head;
    while(current->next!=NULL){
        current = current->next;
    }return current;
}

void freeList(STU* head) {
    STU* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);  // 释放当前节点
    }
}



/* 输入学生信息,可以将手动输入和磁盘收入作为两个分选项
待录入信息人数：
输入课程门数： */

void InputRecord(STU *head,int *StuNum,int *CouNum,int *first){
    int posy = 6;
    first = 0;
    STU * current = TravelList(head);
    SetPosition(POS_X2,posy);
    printf("待录入信息人数(n<%d)：",STU_NUM);
    scanf("%d",StuNum);
    SetPosition(POS_X2,posy+=2);
    printf("输入课程门数(m<%d)：",COURSE_NUM);
    scanf("%d",CouNum);
    for (int i=0;i<2;i++){
        SetPosition(POS_X1,++posy);
        for (int j=0;j<55;j++){
            printf("-");
        }
    }int ClearPosition = ++posy;
    for (int k=0;k<*StuNum;k++){
        if (current != NULL && current->sum!=0 && current->aver !=0){
            STU* newStudent = (STU*)malloc(sizeof(STU));
            memset(newStudent, 0, sizeof(STU));
            for (int i = 0; i < COURSE_NUM; i++) {
                newStudent->score[i] = 0.0f;
            }
            current->next = newStudent;
            current = newStudent;
        }system("cls");
        posy = 5;
        SetPosition(POS_X2,++posy);
        printf("输入第%d个学生的信息：\t",k+1);
        SetPosition(POS_X2,++posy);
        printf("学号：");
        scanf("%ld",&current->num);
        SetPosition(POS_X2,++posy);
        while (getchar() != '\n');  // 清除残留字符
        printf("姓名：");
        scanf("%s",current->name);
        while (getchar() != '\n');  // 清除残留字符
        SetPosition(POS_X2,++posy);
        printf("各门课成绩：");
        for (int p=0;p<*CouNum;p++){
            scanf("%f",&current->score[p]);
        }while (getchar() != '\n');  // 清除残留字符
        CalculateScore(current,*CouNum);
        system("cls");
    }return;
    
}
//计算平均分和总分
void CalculateScore(STU *current,int CouNum){
    float sum=0;
    for (int i=0;i<CouNum;i++){
        sum += current->score[i];
    }current->sum = sum;
    current->aver = sum/CouNum;
    return;
}   


/*计算课程成绩*/
void AnalyseCourse(STU *head,int CouNum){
    int posy = 7;
    float sum[COURSE_NUM]={0},aver[COURSE_NUM];
    SetPosition(POS_X1,posy);
    printf("各门课程的总分和平均分的计算结果为：");
    STU *current = head;
    while (current!=NULL){
        for (int i=0;i<CouNum;i++){
            sum[i] += current->score[i];      //计算第i门课程的总分
        }current = current->next;
    }for (int k=0;k<CouNum;k++){
        aver[k] = sum[k]/CouNum;
        SetPosition(POS_X1,++posy);
        printf("第%d门课程，总分=%.2f，平均分=%.2f\n",k+1,sum[k],aver[k]);
    }
}

/*查找学生记录*/
void ShowInformation(int CouNum,STU *current,int posy){
    SetPosition(POS_X1,++posy);
    printf("学号：%ld",current->num);
    SetPosition(POS_X1,++posy);
    printf("姓名：%s",current->name);
    SetPosition(POS_X1,++posy);
    printf("各门课成绩如下：");
    for (int i=0;i<CouNum;i++){
        SetPosition(POS_X1+3,++posy);
        printf("课程%d：%.2f",i+1,current->score[i]);
    }SetPosition(POS_X1,++posy);
    printf("各门课总分：%.2f",current->sum);
    SetPosition(POS_X1,++posy);
    printf("各门课平均分：%.2f",current->aver);
}
//按学号查找
void SearchByNumber(int CouNum,STU *head){
    system("cls");
    int posy = 7;
    long id;
    STU *current = head;
    SetPosition(POS_X1,posy);
    printf("请输入待查找的学生的学号：");
    scanf("%ld",&id);
    while(current!=NULL){
        if (current->num == id){
            SetPosition(POS_X1,++posy);
            printf("该学生已录入，其信息如下：");
            ShowInformation(CouNum,current,posy);
            system("pause");  // 这里添加暂停，防止结果瞬间消失
            return;
        }current = current->next;  // 移动到下一个节点
    }SetPosition(POS_X1,++posy);
    printf("未找到该学号对应的学生记录");
    system("pause");  // 这里添加暂停，防止结果瞬间消失
    return;
}

//按姓名查找
void SearchByName(int CouNum,STU *head){
    system("cls");
    int posy = 7;
    char stu_name[NAME_LEN];
    STU *current = head;
    SetPosition(POS_X1,posy);
    printf("请输入待查找的学生的姓名：");
    scanf("%s",stu_name);
    while(current!=NULL){
        if (strcmp(current->name, stu_name) == 0){
            SetPosition(POS_X1,++posy);
            printf("该学生已录入，其信息如下：");
            ShowInformation(CouNum,current,posy);
            system("pause");  // 这里添加暂停，防止结果瞬间消失
            return;
        }current = current->next;  // 移动到下一个节点
    }SetPosition(POS_X1,++posy);
    printf("未找到该学号对应的学生记录");
    system("pause");  // 这里添加暂停，防止结果瞬间消失
    return;
}
void SearchMenu(int CouNum,STU *head){
    int posy = 5;
    int op;
    for (int i=0;i<2;i++){
        SetPosition(POS_X1,++posy);
        for (int j=0;j<55;j++){
            printf("-");
        }
    }posy++;
    SetPosition(POS_X3,++posy);
    printf("1.按学号查找");
    SetPosition(POS_X3,++posy);
    printf("2.按姓名查找");
    SetPosition(POS_X3,++posy);
    printf("0.返回上级菜单");
    SetPosition(POS_X3,++posy);
    printf("请选择你想要进行的操作[0~2]：");
    scanf("%d",&op);
    switch (op){
        case 1:  SearchByNumber(CouNum,head);  break;
        case 2:  SearchByName(CouNum,head);    break;
        case 0:  return;                       break;
    }
}

/*修改学生信息*/
void ModifyRecord(int CouNum,int StuNum,STU *head,int right){
    if (right == 1){
        printf("非教职工没有修改权限！！");
        getch();
        return;
    }
    int posy = 7;
    int op;
    long id;
    char ch;
    STU *current = head;
    SetPosition(POS_X1,posy);
    printf("请输入待修改信息的学生的学号：");
    scanf("%ld",&id);
    while(current!=NULL){
        if (current->num == id){
            SetPosition(POS_X1,++posy);
            printf("该学生已录入，其信息如下：");
            ShowInformation(CouNum,current,posy);      //将学生信息展示出来便于查看哪处要修改
            SetPosition(POS_X1,++posy);
            printf("请确认是否要修改？(Y/N 或 y/n)：");
            getchar();
            scanf("%c",&ch);
            //处理修改逻辑
            if (ch == 'Y' || ch == 'y'){
                CorrectInfo(current,&head);
            }else if(ch == 'N' || ch == 'n'){
                SetPosition(POS_X1,++posy);
                printf("撤销修改，按任意键返回上级菜单");
            }else{
                SetPosition(POS_X1,++posy);
                printf("输入错误!");
                return;
            }
            break;
        }current = current->next;
    }SetPosition(POS_X1,++posy);
    printf("未找到该学生记录");
}

//修改内容逻 
void CorrectInfo(STU *stu,STU **head){
    int posy = 7;
    int op;
    while(1){
        system("cls");
        SetPosition(POS_X1,posy);
        printf("请选择待修改的选项：");
        SetPosition(POS_X1+3,++posy);
        printf("1.修改学生姓名");
        SetPosition(POS_X1+3,++posy);
        printf("2.修改课程成绩");
        SetPosition(POS_X1+3,++posy);
        printf("3.删除该学生信息");
        SetPosition(POS_X1+3,++posy);
        printf("0.退出");
        op = (char)_getch();                           //从控制台读取用户输入的一个字符 
        switch (op){
            case '1': 
                ModifyName(stu);
                break;
            case '2': 
                ModifyScore(stu);
                break;
            case '3':
                DeleteRecord(head,stu,posy);
                break;
            case '0':
                return;
        }
    }
}

void ModifyName(STU *stu){
    int posy = 7;
    system("cls");
    SetPosition(POS_X1,++posy);
    printf("学号为%ld的存档姓名%s修改为：",stu->num,stu->name);
    scanf("%10s",stu->name);
    return;
}
//修改课程成绩
void ModifyScore(STU *stu){
    int posy = 7;
    int op;
    system("cls");
    SetPosition(POS_X1,++posy);
    printf("请输入要修改成绩的课程编号(1~)：");
    scanf("%d",&op);
    SetPosition(POS_X1,++posy);
    printf("课程%d原始成绩%.2f修改为：",op,stu->score[op-1]);
    scanf("%f",&stu->score[op-1]);
    return;
}
//删除学生信息
void DeleteRecord(STU **head,STU *stu,int posy){
    char ch;
    STU *current;
    SetPosition(POS_X1,++posy);
    printf("请确定是否要删除该学生信息?(Y/y 或 N/n)：");
    getchar();
    scanf("%c",&ch);
    if (ch=='Y' || ch=='y'){
        if (*head == stu) {
            *head = (*head)->next;  // 头节点直接指向下一个节点
            free(stu);  // 释放原头节点
            printf("学生信息已删除（头节点）。\n");
            return;
        }STU *prev = *head;
        // **找到 stu 的前驱节点**
        while (prev->next != NULL && prev->next != stu) {
            prev = prev->next;
        }// **删除节点**
        prev->next = stu->next;
        free(stu);
        printf("学生信息已删除。\n");   
        return;
    }else if(ch=='N' || ch=='n'){
        SetPosition(POS_X1,++posy);
        printf("撤销删除操作");
        return;
    }else{
        SetPosition(POS_X1,++posy);
        printf("输入错误！");
        return;
    }
}

/*课程相关*/
// 生成课程编号
void generateCourses(int courses[], int count) {
    for (int i = 0; i < count; i++) {
        courses[i] = 101 + i;  // 课程编号从 101 开始递增
    }
}

void StatisticAnalysis(int StuNum,int CouNum,STU *head){
    int courses[CouNum];  // 课程编号数组
    // 调用函数生成课程编号
    generateCourses(courses, CouNum);
    // 设定分数段
    GradeRange ranges[] = {
        {90, 100, "100-90"},
        {80, 89, "89-80"},
        {70, 79, "79-70"},
        {60, 69, "69-60"},
        {0, 59, "59-0"}
    };
    int posy = 1;
    int count[CouNum][RANGE_COUNT]; // VLA 仅限局部变量
    float sum[CouNum];

    memset(count, 0, sizeof(count)); // 全部初始化为 0
    memset(sum, 0, sizeof(sum));     // 直接初始化
    STU *current = head;
    while (current!=NULL){
        for (int i=0;i<CouNum;i++){
            //统计各个分数段人数
            for (int k = 0; k < RANGE_COUNT; k++) {
                if (current->score[i] >= ranges[k].min && current->score[i] <= ranges[k].max) {
                    count[i][k]++;
                    break;
                }
            }sum[i] += current->score[i];
        }current = current->next;
    }SetPosition(POS_X3,posy);
    printf("课程成绩统计结果\n");
    //输出系统名称和功能说明之间的两行短横线
    for (int i=0;i<2;i++){
        SetPosition(0,++posy);
        for (int j=0;j<90;j++){
            printf("-");
        }
    }// 打印标题行
    printf("\n%-15s", "课程编号");  
    for (int k = 0; k < RANGE_COUNT; k++) {
        printf("%-15s", ranges[k].label);
    }printf("%-10s\n", "平均分");
    //打印数据行
    for (int p=0;p<CouNum;p++){
        printf("%-10d", courses[p]); 
        for (int k = 0; k < RANGE_COUNT; k++) {
            double percentage = (double)count[p][k] / StuNum * 100;
            printf("%3d (%.1f%%)    ", count[p][k], percentage);
        }
        printf("%6.2f\n", sum[p]/StuNum);
    }system("pause");
    return;
}

/* 学生记录存磁盘 */
int WriteToFile(STU *head,int StuNum,int CouNum){
    FILE *fp;
    STU *current = head;
    if ((fp = fopen("student.txt","w"))==NULL){
        printf("文件student.txt无法正常打开");
        exit(0);
    }//将数据以指定格式写入文件
    //先写入学生人数StuNum，课程门数CouNum
    fprintf(fp,"%10d%10d\n",StuNum,CouNum);
    while (current!=NULL){
        fprintf(fp,"%10ld%10s\n",current->num,current->name);
        for (int j=0;j<CouNum;j++){
            fprintf(fp,"%10.1lf",current->score[j]);
        }fprintf(fp,"%10.1f%10.1f\n",current->sum,current->aver);
        current = current->next;
    }//关闭文件
    fclose(fp);
    //提示用户存盘操作完毕
    printf("存盘完毕！\n");
    return 0;
}

/* 读取学生记录 */
int ReadFromFile(int *StuNum,int *CouNum,STU *head,int *first){
    //定义文件指针
    FILE *fp;
    STU *current = head;
    // 找到链表末尾
    while (current->next != NULL) {
        current = current->next;
    }int posy = 8;
    SetPosition(POS_X1,posy);
    if ((fp = fopen("student.txt","r"))==NULL){
        printf("磁盘文件student.txt无法打开,请先输入");
        return 1;
    }
    // 读取学生数和课程数
    int newStuNum, newCouNum;
    fscanf(fp, "%10d%10d", &newStuNum, &newCouNum);
    
    // 更新总的学生数和课程数
    *StuNum += newStuNum;
    *CouNum = (*CouNum > newCouNum) ? *CouNum : newCouNum; // 取最大课程数

    // 读取新学生数据并追加到链表
    for (int i = 0; i < newStuNum; i++) {
        if (current != NULL && current->sum!=0 && current->aver !=0){
            STU *newStudent = (STU *)malloc(sizeof(STU));
            if (!newStudent) {
                printf("内存分配失败\n");
                fclose(fp);
                return 1;
            }memset(newStudent, 0, sizeof(STU));
            newStudent->next = NULL;
            current->next = newStudent; // 追加到链表
            current = newStudent;       // 更新当前指针
        }
        // 读取学生信息
        fscanf(fp, "%10ld", &current->num);
        fscanf(fp, "%10s", current->name);
        for (int j = 0; j < newCouNum; j++) {
            fscanf(fp, "%10f", &current->score[j]);
        }
        fscanf(fp, "%10f%10f", &current->sum, &current->aver);
    }

    *first = 0; // 修改标准变量
    fclose(fp);
    printf("数据从磁盘读取完毕!");
    return 0;

}


/*打印学生成绩、
1.按姓名排序
2.按学号排序
3.按总分排序
4.按平均分排序*/
// 打印学生信息
void printStudentList(STU* head,int CouNum) {
    system("cls");
    STU* current = head;
    printf("ID\tName\t");
    for (int i=1;i<=CouNum;i++){
        printf("\tScore%d",i);
    }printf("\tTotal\tAverage\n");
    while (current != NULL) {
        // 打印学号、姓名、各科分数、总分和平均分
        printf("%ld\t%-8s\t", current->num, current->name);
        for (int i=0;i<CouNum;i++){
            printf("\t%.2f",current->score[i]);
        }printf("\t%.2f\t%.2f\n",current->sum,current->aver);
        current = current->next;
    }system("pause");
}

void sortByTotal(STU** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    STU *ptr1, *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->sum < ptr1->next->sum) {
                // 交换数据，而不是交换节点
                long tempNum = ptr1->num;
                char tempName[50];
                strcpy(tempName, ptr1->name);
                float tempScore[10];  // 假设最多10门课
                memcpy(tempScore, ptr1->score, sizeof(ptr1->score));
                float tempSum = ptr1->sum;
                float tempAver = ptr1->aver;

                ptr1->num = ptr1->next->num;
                strcpy(ptr1->name, ptr1->next->name);
                memcpy(ptr1->score, ptr1->next->score, sizeof(ptr1->score));
                ptr1->sum = ptr1->next->sum;
                ptr1->aver = ptr1->next->aver;

                ptr1->next->num = tempNum;
                strcpy(ptr1->next->name, tempName);
                memcpy(ptr1->next->score, tempScore, sizeof(tempScore));
                ptr1->next->sum = tempSum;
                ptr1->next->aver = tempAver;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void sortByAver(STU** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    STU *ptr1, *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->aver < ptr1->next->aver) {  // 按平均分降序排序
                // 交换数据，而不是交换节点
                long tempNum = ptr1->num;
                char tempName[50];
                strcpy(tempName, ptr1->name);
                float tempScore[10];  // 假设最多10门课
                memcpy(tempScore, ptr1->score, sizeof(ptr1->score));
                float tempSum = ptr1->sum;
                float tempAver = ptr1->aver;

                ptr1->num = ptr1->next->num;
                strcpy(ptr1->name, ptr1->next->name);
                memcpy(ptr1->score, ptr1->next->score, sizeof(ptr1->score));
                ptr1->sum = ptr1->next->sum;
                ptr1->aver = ptr1->next->aver;

                ptr1->next->num = tempNum;
                strcpy(ptr1->next->name, tempName);
                memcpy(ptr1->next->score, tempScore, sizeof(tempScore));
                ptr1->next->sum = tempSum;
                ptr1->next->aver = tempAver;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void sortById(STU** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    STU *ptr1, *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->num > ptr1->next->num) {
                // 交换数据，而不是交换节点
                long tempNum = ptr1->num;
                char tempName[50];
                strcpy(tempName, ptr1->name);
                float tempScore[10];  // 假设最多10门课
                memcpy(tempScore, ptr1->score, sizeof(ptr1->score));
                float tempSum = ptr1->sum;
                float tempAver = ptr1->aver;

                ptr1->num = ptr1->next->num;
                strcpy(ptr1->name, ptr1->next->name);
                memcpy(ptr1->score, ptr1->next->score, sizeof(ptr1->score));
                ptr1->sum = ptr1->next->sum;
                ptr1->aver = ptr1->next->aver;

                ptr1->next->num = tempNum;
                strcpy(ptr1->next->name, tempName);
                memcpy(ptr1->next->score, tempScore, sizeof(tempScore));
                ptr1->next->sum = tempSum;
                ptr1->next->aver = tempAver;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// 交换两个节点（需要前驱节点）
void swapNodes(STU** head, STU* node1, STU* node2) {
    if (node1 == node2) return;

    STU* prev1 = NULL, *prev2 = NULL, *temp = *head;

    // 查找 node1 和 node2 的前驱节点
    while (temp != NULL && temp->next != NULL) {
        if (temp->next == node1) prev1 = temp;
        if (temp->next == node2) prev2 = temp;
        temp = temp->next;
    }

    // 交换前驱节点的 next 指针
    if (prev1) prev1->next = node2;
    if (prev2) prev2->next = node1;

    // 交换 node1 和 node2 的 next 指针
    temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;

    // 处理头结点情况
    if (*head == node1) *head = node2;
    else if (*head == node2) *head = node1;
}

void sortByName(STU** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    STU* ptr1;
    STU* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) { // 按字母顺序
                swapNodes(head, ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void PrintRecordMenu(STU **head,int CouNum){
    int op;
    while(1){
        int posy = 7;
        system("cls");
        SetPosition(POS_X1,posy);
        printf("学生信息输出：");
        SetPosition(POS_X1+3,++posy);
        printf("1.按历史记录输出");
        SetPosition(POS_X1+3,++posy);
        printf("2.按姓名排序");
        SetPosition(POS_X1+3,++posy);
        printf("3.按学号排序");
        SetPosition(POS_X1+3,++posy);
        printf("4.按平均分排序");
        SetPosition(POS_X1+3,++posy);
        printf("5.按总分排序");
        SetPosition(POS_X1+3,++posy);
        printf("0.退出");
        scanf("%d",&op);                          //从控制台读取用户输入的一个字符 
        
        switch (op) {
            case 1:
                printStudentList(*head,CouNum);
                break;
            case 2:
                sortByName(head);
                printf("按姓名排序完成\n");
                printStudentList(*head, CouNum);
                break;
            case 3:
                sortById(head);
                printf("按学号排序完成\n");
                printStudentList(*head, CouNum);
                break;
            case 4:
                sortByAver(head);
                printf("按平均分排序完成\n");
                printStudentList(*head, CouNum);
                break;
            case 5:
                sortByTotal(head);
                printf("按总分排序完成\n");
                printStudentList(*head, CouNum);
                break;
            case 0:
                return;
            default:
                printf("Invalid choice\n");
        }
    }return;
}


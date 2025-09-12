#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//1.线性表（顺序表）的定义  初始化
//静态
// #define MaxSize 10
// typedef struct{
//     int data[MaxSize];
//     int length;
// }SeqList;

//定义（动态）
#define InitSize 10000
typedef struct{
    int *data;
    int MaxSize,length;
}SeqList;

//1.顺序表的初始化

//静态
// void InitList(SeqList &L)//静态
// {
//     L.length=0; 
// }

void InitList(SeqList *L)
{
    L->data=(int *)malloc(sizeof(int)*InitSize);
    L->length=0;         //初始长度
    L->MaxSize=InitSize;  //初始存储量
    //设置表长
    printf("设置当前表长\n");
    scanf("%d",&L->length);
    printf("设置表长最大上限\n");
    scanf("%d",&L->MaxSize);
    printf("分别输入表值\n");
    for(int i=0;i<L->length;i++)
    scanf("%d",&L->data[i]);
}



//2.插入操作
//在顺序表L的第i(1<i<=L.length+1)个位置插入新元素e
//要求
//*若i的输入不合法，返回false，表示插入失败
//*否则将第i个元素及其后的所有元素往后移动一个位置，腾出一个空位置插入新元素e
//*顺序表长度增加1，插入成功，返回true

bool ListInsert(SeqList *L,int i,int e){                   //返回true||false bool类型
  if(i<1||i>L->length+1){                                 //可以插入到最后一个元素的后面，就该线性表目前长度加1
    return false;
  }        
  if(L->length>L->MaxSize){                                  //存储空间满了
    return false;
  }      

  for(int j=L->length;j>=i;j--)                       
  {
    L->data[j]=L->data[j-1];
  }
  L->data[i-1]=e;               //时刻牢记数组下标 与 位序不同 位序大于数组下标 1
  L->length++;
  return true;

}
//3.删除操作
//删除顺序表L中第i(1<=i<=L.length)个位置的元素
// 用引用变量e引回

//若i的输入不合法，则返回false
//否则将被删元素赋给引用变量e
//并将第i+1个元素及其后的所有元素依次往前移动一格位置，返回true

bool ListDelete(SeqList *L,int i,int *e){
  if(i<1||i>L->length){
    return false;
  }
  *e=L->data[i-1];
  for(int j=i-1;j<L->length;j++){//循环变量逻辑错误：移动元素时，j 从 i-1 开始，却修改 data[j-1]，会导致数组越界（j=0 时 j-1=-1 是非法下标），破坏数据。
    L->data[j]=L->data[j+1];
  }
  L->length--;
  return true;
}

//4.按值查找
//在顺序表L中查找第一个元素值等于e的值，并返回其位序
int LocateElem(SeqList L,int e)
{
  for(int i=0;i<L.length;i++)
  {
    if(L.data[i]==e)
    return i+1;
  }
  printf("此表无此值");
}


//打印
void PrintList(SeqList *L)
{
  
  printf("当前顺序表的值为\n");
  for(int i=0;i<L->length;i++)
  {
    printf("%d\n",L->data[i]);
  }
  printf("长度为:%d\n",L->length);


}





int main()
{
  SeqList L;
  InitList(&L);
  int D=1;


  while(D!=0){
    printf("请输入您要对线性表进行的操作\n");
printf("1——插入\n2——删除\n3——查找\n4——查看表\n");
int ToDo;
scanf("%d",&ToDo);

  if(ToDo!=1&&ToDo!=4&&ToDo!=2&&ToDo&&3){
  printf("当前输入的操作不存在");
  }


  //1.插入
if(ToDo==1){
  int e=88;
  int locat;
  
  printf("输入要插入的位置\n");
  scanf("%d",&locat);
  printf("输入要插入的值\n");
  scanf("%d",&e);
  if(ListInsert(&L,locat,e)){
  printf("插入成功，位置：%d 值：%d\n",locat,L.data[locat-1]);

    printf("继续操作请输入任意数字\n退出请按0\n");
  scanf("%d",&D);
  }
  else
  printf("输入的位置有误\n");
}

  //2.删除
if(ToDo==2){
   int e1,loc;
  printf("输入删除的数位\n");
  scanf("%d",&loc);
  //条件判断颠倒：ListDelete 返回 true 表示删除成功，你却在 if 里打印 “位置错误”，逻辑完全反了。
  if(ListDelete(&L,loc,&e1)){
    printf("删除成功，删除的数为：%d\n",e1);

      printf("操作完成\n继续操作请输入任意数字\n退出请按0\n");
  scanf("%d",&D);
  }
  else{
  printf("输入的位置错误\n");
    printf("操作完成\n继续操作请输入任意数字\n退出请按0\n");
  scanf("%d",&D);
  }
}


  //3.按值查找（顺序查找）
  if(ToDo==3){
      printf("请输入要查找的值");
  int Find;
  scanf("%d",&Find);
  printf("值%d的位置在%d\n",Find,LocateElem(L,Find));

   printf("操作完成\n继续操作请输入任意数字\n退出请按0\n");
  scanf("%d",&D);
  }

  if(ToDo==4){
  PrintList(&L);
  printf("操作完成\n继续操作请输入任意数字\n退出请按0\n");
  scanf("%d",&D);
  }



  }
}

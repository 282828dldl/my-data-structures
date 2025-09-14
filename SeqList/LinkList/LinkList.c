#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  //布尔类型

//1.单链表的定义
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;


//2.单链表的初始化

//(1).无头结点    只需将头指针初始化为NULL
// bool InitList(LinkList *L){
//     L=NuLL;
//     return ture;
// }

//(2).有头节点   
//需创建一个头节点
//并让头指针指向头节点
//头节点的next域初始化为NULL
bool InitList(LinkList *L){      //这里要加*  记住：要改变地址 就要得到地址的地址 这里我们要修改的时头指针地址的地址  LinkList是头指针的地址  LinkList * 是头指针地址的地址  
    *L=(LNode *)malloc(sizeof(LNode));   //L为头节点 malloc函数创建的内存转化为LNode类型指针后传递给L
    if(*L==NULL){
        return false;  //判断内存
    }
    // L->next=NULL;你收到这个错误是因为 L 是一个指向指针的指针（LinkList *L），而你直接用 L->next，实际上应该先解引用再访问成员。正确写法是 (*L)->next = NULL;。
    (*L)->next=NULL;
    return true;
}


//(3).判断单链表是否为空(带头结点)
bool Empty(LinkList L){
    if(L->next==NULL){
        return true;
    }
    else{
        return false;
    }
    //更简单的写法
    //return (L->next==NULL)
}


//3.插入






//(1).1按位序插入(带头结点) 在第几个位置插入元素



//在第i个位置插入元素e(带头结点)
// 插入操作：在第i个位置插入数据e，i从1开始
bool ListInsert(LinkList *L,int i,int e){
    if(i<1)
        return false;    //位序从1开始
    LNode *p;               //定义一个结点型指针p 指向当前扫描到的结点
    int j = 0;              //当前p指向的是第几个结点，初始化为0
                    //p=L; 这里 L 是 LinkList *，但 p 是 LNode *，类型不匹配，应该初始化为 p = *L;，表示从头节点开始遍历。
    p=*L;           
    //下面这句话是完全错误的 这里的p初始化 只是用于将L的头指针给p 用于循环找到第i-1的结点 并不需要头指针的地址的地址
    //将头节点的地址的地址给 p 这样p才能修改L的地址  表示从头节点开始遍历 

    while(p!=NULL&&j<i-1) {                 //两者必须全满足：(1):地址不为空 为空说明超过了链表长度
        p=p->next;                                           //(2):j的值要小于i-1   最后的结果是j=i-1
    } 
    if(p==NULL){
        return false;    //i值不合法 要查找的位置已经超出了链表的长度
    }

    //改地址过程
    LNode *s=(LNode*)malloc(sizeof(LNode));   //加e插入到链表 就要给他创建一个空间 该空间就是该结[构体LNode
    if(s == NULL) {
        return false; // 内存分配失败
    }
    s->data=e;
    //s->next=(*p)->next;s->next=(*p)->next; 此处 p 是 LNode *，应写为 s->next=p->next;。
    s->next=p->next;
    p->next=s;
    return true;
}




/*(1).2.按位序插入(不带头结点)


不存在第0个结点,因此i等于1时需要特别处理 
原理仍然是找到 第i-1个结点,将新结点插入其后*/

bool ListInsert(LinkList *L,int i,int e){
    if(i<1)
        return false;
    if(i==1){               //插入第一个节点的操作与其它结点不同
        LNode *s=(LNode *)malloc(sizeof(LNode));
        s->data=e;
        s->next=(*L);
        (*L)=s;    //头指针指向新结点  L 相当于整个链表的头 他的指向是头指针
        //如果 $i==1$ 时插入后没有 return，后续代码会继续执行，导致重复插入并可能出现空指针异常。应在插入后直接 return true。
        return true;    //非常重要 不能忘记

    }
    LNode *p=*L;     //指针p指向当前扫描到的结点   此时p指向第一个结点
    int j=1;         //当前p指向的是第几个结点
    while(p!=NULL && j<i-1){
        p=p->next;
        j++;        //循环后就可找到第i-1个头结点的地址
    }
    LNode *s=(LNode *)malloc(sizeof(LNode));
    //每一次分配内存 都应检查是否合法
    if(s==NULL) {
        return false; 
    }
    s->data=e;
    s->next=p->next;
    p->next=s;
    return true;  //插入成功

}
             


 //(2).指定结点的后插操作   


 //时间复杂度O(1)
 /*在p结点之后插入元素e
 p 指向插入位置的结点指针
 插入成功返回 true，失败返回 false
 e 要插入的元素值*/


 bool InsertNextNode(LNode *p,int e){   
    //先判断给的p结点是否存在
    if(p==NULL){
        return false;
    }
    LNode *s=(LNode *)malloc(sizeof(LNode));
    //分配内存记得判断空间
    if(s==NULL) {
        return false;
    }
    s->data=e;
    s->next=p->next;
    p->next=s;
    return true;  // 返回插入操作是否成功
 }
 
 




 //(1).PRO指定结点(在第i个位置插入元素e) 与 后插(在结点p的后面插入元素e) 结合的后插



bool ListInsertPro(LinkList *L,int i,int e){
    if(i<1){
        return false;
    }
    LNode *p=(*L);
    int j=0;
    while(p!=NULL && j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL){
        return false;
    }

     //后插就是在前插找到第i-1个元素后执行的操作

     return InsertNextNode(p,e)
    /*InsertNextNode(p,e);
    InsertNextNode(p,e); 的返回值未检查。
    如果插入失败，ListInsertPro 不会反馈错误，
    建议将其返回值用于 ListInsertPro 的返回值。*/
    
}

//(3).前插操作 


//在结点p之前插入元素e
bool InsertPriorNode(LNode *p,int e){
    if(p==NULL){
        return false;
    }
    LNode *s=(LNode *)malloc(sizeof(LNode)); 
    //内存分配后未检查 s 是否为 NULL，应加合法性判断避免空指针异常。
    if(s==NULL){
        return false;
    }
    //建议先设置 s->data 再设置 s->next，以保持与其他插入函数一致的顺序，提升代码一致性。
   /* s->next=p->next;
    s->data=p->data;*/
    s->data=e;
    s->next=p->next;
    p->data=e;
    p->next=s;

    return true;
}







int main(){
    LinkList L;
//  InitList(L);
//     你在 Test() 函数里调用 InitList(L);，但 InitList 的参数类型是 LinkList *，而你传递的是 LinkList（即 L），这会导致类型不匹配。

// 正确做法：
// 应该传递头指针的地址，即 &L。
    InitList(&L);
}

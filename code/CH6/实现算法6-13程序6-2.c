 #include<string.h>
 #include<ctype.h>
 #include<malloc.h> /* malloc()等 */
 #include<limits.h> /* INT_MAX等 */
 #include<stdio.h> /* EOF(=^Z或F6),NULL */
 #include<stdlib.h> /* atoi() */
 #include<io.h> /* eof() */
 #include<math.h> /* floor(),ceil(),abs() */
 #include<process.h> /* exit() */
 /* 函数结果状态代码 */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 /* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
 typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
 typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
 
 typedef struct
 {
   unsigned int weight;
   unsigned int parent,lchild,rchild;
 }HTNode,*HuffmanTree; /* 动态分配数组存储赫夫曼树 */
 typedef char **HuffmanCode; /* 动态分配数组存储赫夫曼编码表 */
 
 int min1(HuffmanTree t,int i)
 { /* 返回i个结点中权值最小的树的根结点序号，函数select()调用 */
   int j,flag;
   unsigned int k=UINT_MAX; /* 取k为不小于可能的值(无符号整型最大值) */
   for(j=1;j<=i;j++)
     if(t[j].weight<k&&t[j].parent==0) /* t[j]是树的根结点 */
       k=t[j].weight,flag=j;
   t[flag].parent=1; /* 给选中的根结点的双亲赋1，避免第2次查找该结点 */
   return flag;
 }

 void select(HuffmanTree t,int i,int *s1,int *s2)
 { /* 在i个结点中选择2个权值最小的树的根结点序号，s1为其中序号小的那个 */
   int j;
   *s1=min1(t,i);
   *s2=min1(t,i);
   if(*s1>*s2)
   {
     j=*s1;
     *s1=*s2;
     *s2=j;
   }
 }
 
 void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n) /* 前半部分为算法6.12 */
 { /* w存放n个字符的权值(均>0)，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC */
   int m,i,s1,s2; /* 此句与algo6-1.c不同 */
   unsigned c,cdlen; /* 此句与algo6-1.c不同 */
   HuffmanTree p;
   char *cd;
   if(n<=1)
     return;
   m=2*n-1;
   *HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); /* 0号单元未用 */
   for(p=*HT+1,i=1;i<=n;++i,++p,++w)
   {
     (*p).weight=*w;
     (*p).parent=0;
     (*p).lchild=0;
     (*p).rchild=0;
   }
   for(;i<=m;++i,++p)
     (*p).parent=0;
   for(i=n+1;i<=m;++i) /* 建赫夫曼树 */
   { /* 在HT[1～i-1]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2 */
     select(*HT,i-1,&s1,&s2);
     (*HT)[s1].parent=(*HT)[s2].parent=i;
     (*HT)[i].lchild=s1;
     (*HT)[i].rchild=s2;
     (*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
   }
   /* 以下为算法6.13，无栈非递归遍历赫夫曼树，求赫夫曼编码，以上同算法6.12 */
   *HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
   /* 分配n个字符编码的头指针向量([0]不用) */
   cd=(char*)malloc(n*sizeof(char)); /* 分配求编码的工作空间 */
   c=m;
   cdlen=0;
   for(i=1;i<=m;++i)
     (*HT)[i].weight=0; /* 遍历赫夫曼树时用作结点状态标志 */
   while(c)
   {
     if((*HT)[c].weight==0)
     { /* 向左 */
       (*HT)[c].weight=1;
       if((*HT)[c].lchild!=0)
       {
         c=(*HT)[c].lchild;
         cd[cdlen++]='0';
       }
       else if((*HT)[c].rchild==0)
       { /* 登记叶子结点的字符的编码 */
         (*HC)[c]=(char *)malloc((cdlen+1)*sizeof(char));
         cd[cdlen]='\0';
         strcpy((*HC)[c],cd); /* 复制编码(串) */
       }
     }
     else if((*HT)[c].weight==1)
     { /* 向右 */
       (*HT)[c].weight=2;
       if((*HT)[c].rchild!=0)
       {
         c=(*HT)[c].rchild;
         cd[cdlen++]='1';
       }
     }
     else
     { /* HT[c].weight==2，退回 */
       (*HT)[c].weight=0;
       c=(*HT)[c].parent;
       --cdlen; /* 退到父结点，编码长度减1 */
     }
   }
   free(cd);
 }

 int main()
 { /* 主程序同algo6-1.c */
   HuffmanTree HT;
   HuffmanCode HC;
   int *w,n,i;
   printf("请输入权值的个数(>1): ");
   scanf("%d",&n);
   w=(int *)malloc(n*sizeof(int));
   printf("请依次输入%d个权值(整型):\n",n);
   for(i=0;i<=n-1;i++)
     scanf("%d",w+i);
   HuffmanCoding(&HT,&HC,w,n);
   for(i=1;i<=n;i++)
     puts(HC[i]);
   
   return 0;
 }
 
 

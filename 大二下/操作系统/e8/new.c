#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define INVALID -1
#define total_instruction 320 //模拟的指令数
#define total_vp 32 //模拟的虚拟页面数
#define TOTAL_INSTRUCTION 320
#define TOTAL_VP 32
typedef struct //页面结构
{
int pn; //页号
int pfn; //内存块号
int counter; //一个周期内访问页面的次数
int time; //访问时间
}p1_type;
p1_type p1[total_vp];
typedef struct pfc_struct //页面控制结构
{
int pn; //页号
int pfn; //内存块号
struct pfc_struct *next;
}pfc_type;
pfc_type pfc[total_vp]; //用户进程虚页控制结构
pfc_type *freepf_head; //空内存页头指针
pfc_type *busypf_head; //忙内存页头指针
pfc_type *busypf_tail; //忙内存页尾指针
int disaffect; //页面失效次数
int a[total_instruction]; //指令流数据组
int page[total_instruction]; //每条指令所属页号
int offset[total_instruction]; //每页装人 10 条指令后取得的页号偏移值
void initialize(int); //初始化数据
void FIFO(int); //计算使用 FIFO 算法时的访问命中率
int main()
{
int s,i,j;
srand (10*getpid());
s=(float)319*rand()/32767/32767/2+1;
for(i=0;i<total_instruction;i+=4) //通过随机函数随机生成 320 条指令
{
if(s<0||s>319)
{
printf("when i==%d, Error, s==%d\n",i,s);
exit(0);
}
a[i]=s;
a[i+1]=a[i]+1;
a[i+2]=(float)a[i]*rand()/32767/32767/2;a[i+3]=a[i+2]+1;
s=(float)(318-a[i+2])*rand()/32767/32767/2+a[i+2]+2;
if((a[i+2]>318)||(s>319))
printf("a[%d+2],a number which is: %d and s==%d\n",i,a[i+2],s);
}
//将指令序列转换为页面地址流
for(i=0;i<total_instruction;i++)
{
page[i]=a[i]/10;
offset[i]=a[i]%10;
}
//用户工作区从 4 个页面变换到 32 个页面
for(i=4;i<=32;i++)
{
printf("%2d page frames",i);
FIFO(i);
printf("\n");
}
}
void initialize(int total_pf)
{
int i;
disaffect=0;
for(i=0;i<total_vp;i++)
{
p1[i].pn=i;
p1[i].pfn=INVALID;
p1[i].counter=0;
p1[i].time=-1;
}
for(i=0;i<total_pf-1;i++)
{
pfc[i].next=&pfc[i+1];
pfc[i].pfn=i;
} 
pfc[total_pf-1].next=NULL;
pfc[total_pf-1].pfn=total_pf-1;
freepf_head=&pfc[0];
}
void FIFO(int total_pf)
{
int i,j;
pfc_type *p;
initialize(total_pf);busypf_head=busypf_tail=NULL;
for(i=0;i<total_instruction;i++)
{
if(p1[page[i]].pfn==INVALID) //页面失效
{
disaffect+=1; //页面失效次数
if(freepf_head==NULL) //无空闲页面
{
p=busypf_head->next;
p1[busypf_head->pn].pfn=INVALID;
freepf_head=busypf_head; //释放忙页面的第一个页面
freepf_head->next=NULL;
busypf_head=p;
}
p=freepf_head->next; //按 FIFO 方式将新页面调人内存页面
freepf_head->next=NULL;
freepf_head->pn=page[i];
p1[page[i]].pfn=freepf_head->pfn;
if(busypf_tail==NULL)
busypf_head=busypf_tail=freepf_head;
else
{
busypf_tail->next=freepf_head; //减少一个空闲页面
busypf_tail=freepf_head;
} 
freepf_head=p;
}
}
printf(" FIFO:%6.4f",1-(float)disaffect/320);
}

void LRU(int total_pf)
{
    int i, j, current_time = 0;
    int lru_page, lru_time;
    pfc_type *p, *q;
    initialize(total_pf);
    busypf_head = NULL;
    busypf_tail = NULL;
    for (i = 0; i < TOTAL_INSTRUCTION; i++)
    {
        current_time++;
        if (p1[page[i]].pfn == INVALID)
        {
            disaffect++;
            if (freepf_head == NULL)
            {
                // Find LRU page
                lru_page = -1;
                lru_time = current_time;
                for (j = 0; j < TOTAL_VP; j++)
                {
                    if (p1[j].pfn != INVALID && p1[j].time < lru_time)
                    {
                        lru_time = p1[j].time;
                        lru_page = j;
                    }
                }
                // Rep1ace LRU page
                p = busypf_head;
                q = NULL;
                while (p != NULL && p->pn != lru_page)
                {
                    q = p;
                    p = p->next;
                }
                if (p == NULL)
                {
                    printf("Error: LRU page not found in busy list\n");
                    return;
                }
                if (q == NULL)
                {
                    busypf_head = p->next;
                }
                else
                {
                    q->next = p->next;
                }
                if (p == busypf_tail)
                {
                    busypf_tail = q;
                }
                p1[lru_page].pfn = INVALID;
                freepf_head = p;
                freepf_head->next = NULL;
            }

            p = freepf_head->next;
            freepf_head->next = NULL;
            freepf_head->pn = page[i];
            p1[page[i]].pfn = freepf_head->pfn;
            p1[page[i]].time = current_time;
            if (busypf_head == NULL)
            {
                busypf_head = busypf_tail = freepf_head;
            }
            else
            {
                busypf_tail->next = freepf_head;
                busypf_tail = freepf_head;
            }
            freepf_head = p;
        }
        else
        {
            p1[page[i]].time = current_time;
        }
    }
    printf(" LRU:%6.4f\n", 1 - (float)disaffect / TOTAL_INSTRUCTION);
}

void LFU(int total_pf)
{
    int i, j, lfu_page, min_counter;
    pfc_type *p, *q;
    initialize(total_pf);
    busypf_head = NULL;
    busypf_tail = NULL;
    for (i = 0; i < TOTAL_INSTRUCTION; i++)
    {
        if (p1[page[i]].pfn == INVALID)
        {
            disaffect++;
            if (freepf_head == NULL)
            {
                // Find LFU page
                lfu_page = -1;
                min_counter = TOTAL_INSTRUCTION;
                for (j = 0; j < TOTAL_VP; j++)
                {
                    if (p1[j].pfn != INVALID && p1[j].counter < min_counter)
                    {
                        min_counter = p1[j].counter;
                        lfu_page = j;
                    }
                }
                // Rep1ace LFU page
                p = busypf_head;
                q = NULL;
                while (p != NULL && p->pn != lfu_page)
                {
                    q = p;
                    p = p->next;
                }
                if (p == NULL)
                {
                    printf("Error: LFU page not found in busy list\n");
                    return;
                }
                if (q == NULL)
                {
                    busypf_head = p->next;
                }
                else
                {
                    q->next = p->next;
                }
                if (p == busypf_tail)
                {
                    busypf_tail = q;
                }
                p1[lfu_page].pfn = INVALID;
                freepf_head = p;
                freepf_head->next = NULL;
            }

            p = freepf_head->next;
            freepf_head->next = NULL;
            freepf_head->pn = page[i];
            p1[page[i]].pfn = freepf_head->pfn;
            p1[page[i]].counter = 1; // Initialize the counter
            if (busypf_head == NULL)
            {
                busypf_head = busypf_tail = freepf_head;
            }
            else
            {
                busypf_tail->next = freepf_head;
                busypf_tail = freepf_head;
            }
            freepf_head = p;
        }
        else
        {
            p1[page[i]].counter++; // Increment the counter
        }
    }
    printf(" LFU:%6.4f\n", 1 - (float)disaffect / TOTAL_INSTRUCTION);
}

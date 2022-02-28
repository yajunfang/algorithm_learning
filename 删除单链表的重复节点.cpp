#include <iostream>

// 单链表节点结构如下
typedef struct node
{
    char data;
    struct node* next;
} NODE;


// 尾插法创建单链表(带头节点)
NODE* createEnd(char arr[], int len)
{
    NODE* head = (NODE*)malloc(sizeof(NODE)); // 生成头节点
    head->next = NULL;
    NODE* end = head;  // 尾指针初始化

    for (int i = 0; i < len; i++) {

        NODE* p = (NODE*)malloc(sizeof(NODE)); // 为每个数组元素建立一个节点
        p->data = arr[i];
        end->next = p;  // 将节点p插入到终端节点之后
        end = p;
    }

    end->next = NULL;  // 单链表建立完毕，将终端节点的指针域置空

    return head;
}

// 单链表打印
void print(NODE* head)
{
    if (head == NULL) return;

    NODE* p = head->next;
    while (p != NULL) {
        printf("%c  ", p->data);
        p = p->next;
    }
}


// 第三种方法：递归方法
NODE* delSame_3(NODE* head)
{
    NODE* p, * temp = head; // 递归过程中head是在不断变化的，但初始时temp都指向新的head。
    if (head->next == NULL)
        return head;

    head->next = delSame_3(head->next); // 递归到head->next指向链表的尾节点；此时head指向链表倒数第二个节点。
    p = head->next; // 让p指向head的下一个节点，注意此时temp＝head；

    while (p != NULL)
    {
        if (head->data == p->data) // 单次递归中，head是不变的，每次都把head的数据和head之后所有节点的数据比较，若相同，则删除该节点。
        {
            temp->next = p->next;
            free(p);
            p = temp->next;
        }
        else
        {
            p = p->next;
            temp = temp->next; // temp初始时是指向新的head的，之后作为临时变量，随着p一起后移，始终作为p的前驱节点，是为了当p节点的数据和head数据一样时，在删除p节点时，用temp->next来保存p的后继节点。
        }
    }

    return head;
}


// 第二种方法：非递归实现去重
NODE* delSame_2(NODE* head)
{
    NODE* p, * q, * r;
    p = head->next; // 适用于有头节点的单链表；对于不带头节点的单链表，此处改为 p＝head 即可。
    while (p != NULL)    // p用于遍历链表
    {
        q = p;
        while (q->next != NULL) // q遍历p后面的结点，并与p数值比较
        {
            if (q->next->data == p->data)
            {
                r = q->next; // r保存需要删掉的结点
                q->next = r->next;   // 需要删掉的结点的前后结点相接
                free(r);
            }
            else
                q = q->next;
        }

        p = p->next;
    }

    return head;
}


//双指针方法
NODE* delSame_1(NODE* head)
{
    if (head->next == NULL)
        return head;
    NODE* current = head;
    while (current)
    {
        NODE* p = current;
        while (p->next)
        {
            if (p->next->data == current->data)
            {
                p->next = p->next->next;
            }
            else
            {
                p = p->next;

            }
         
        }
        current = current->next;
    }
    return head;

}





// 第一种方法：hash表去重
NODE* delSame(NODE* head)
{
    if (head == NULL || head->next == NULL)
        return head;

    const int size = 256;
    unsigned int count[size]; // 可用 unsigned int count[size] = {0}; 将数组中每一个元素都初始化为0。
    for (int i = 0; i < size; i++) // 可能上述方法，不一定对所有编译器都适用，所以采用循环的方式更稳妥。
        count[i] = 0;

    // count[(unsigned char)(head->data)] = 1; // 当使用没有头节点的单链表时，打开此行代码即可。

    NODE* p = head; // head是单链表的头节点，注意，头节点没有数据，它的存在仅仅是为了方便计算。
    NODE* q = p->next;
    NODE* r;
    while (q != NULL)
    {
        if (count[(unsigned char)(q->data)] == 0)
        {
            count[(unsigned char)(q->data)] = 1;
            p = q;
            q = q->next; // 始终让p作为q的前驱节点
        }
        else
        {
            r = q; // r存储要删除的节点
            p->next = q->next;
            q = p->next; // 始终让p作为q的前驱节点
            free(r);
        }
    }

    return head;

}

int main(int argc, const char* argv[]) {

    char arr[] = "123321";
    int len = (int)strlen(arr);

    NODE* head = createEnd(arr, len);

    // 去重之前
    print(head);
    printf("\n");

    delSame_1(head);

    // 去重之后
    print(head);
    printf("\n");


    return 0;
}
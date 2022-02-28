#include <iostream>

// ������ڵ�ṹ����
typedef struct node
{
    char data;
    struct node* next;
} NODE;


// β�巨����������(��ͷ�ڵ�)
NODE* createEnd(char arr[], int len)
{
    NODE* head = (NODE*)malloc(sizeof(NODE)); // ����ͷ�ڵ�
    head->next = NULL;
    NODE* end = head;  // βָ���ʼ��

    for (int i = 0; i < len; i++) {

        NODE* p = (NODE*)malloc(sizeof(NODE)); // Ϊÿ������Ԫ�ؽ���һ���ڵ�
        p->data = arr[i];
        end->next = p;  // ���ڵ�p���뵽�ն˽ڵ�֮��
        end = p;
    }

    end->next = NULL;  // ����������ϣ����ն˽ڵ��ָ�����ÿ�

    return head;
}

// �������ӡ
void print(NODE* head)
{
    if (head == NULL) return;

    NODE* p = head->next;
    while (p != NULL) {
        printf("%c  ", p->data);
        p = p->next;
    }
}


// �����ַ������ݹ鷽��
NODE* delSame_3(NODE* head)
{
    NODE* p, * temp = head; // �ݹ������head���ڲ��ϱ仯�ģ�����ʼʱtemp��ָ���µ�head��
    if (head->next == NULL)
        return head;

    head->next = delSame_3(head->next); // �ݹ鵽head->nextָ�������β�ڵ㣻��ʱheadָ���������ڶ����ڵ㡣
    p = head->next; // ��pָ��head����һ���ڵ㣬ע���ʱtemp��head��

    while (p != NULL)
    {
        if (head->data == p->data) // ���εݹ��У�head�ǲ���ģ�ÿ�ζ���head�����ݺ�head֮�����нڵ�����ݱȽϣ�����ͬ����ɾ���ýڵ㡣
        {
            temp->next = p->next;
            free(p);
            p = temp->next;
        }
        else
        {
            p = p->next;
            temp = temp->next; // temp��ʼʱ��ָ���µ�head�ģ�֮����Ϊ��ʱ����������pһ����ƣ�ʼ����Ϊp��ǰ���ڵ㣬��Ϊ�˵�p�ڵ�����ݺ�head����һ��ʱ����ɾ��p�ڵ�ʱ����temp->next������p�ĺ�̽ڵ㡣
        }
    }

    return head;
}


// �ڶ��ַ������ǵݹ�ʵ��ȥ��
NODE* delSame_2(NODE* head)
{
    NODE* p, * q, * r;
    p = head->next; // ��������ͷ�ڵ�ĵ��������ڲ���ͷ�ڵ�ĵ������˴���Ϊ p��head ���ɡ�
    while (p != NULL)    // p���ڱ�������
    {
        q = p;
        while (q->next != NULL) // q����p����Ľ�㣬����p��ֵ�Ƚ�
        {
            if (q->next->data == p->data)
            {
                r = q->next; // r������Ҫɾ���Ľ��
                q->next = r->next;   // ��Ҫɾ���Ľ���ǰ�������
                free(r);
            }
            else
                q = q->next;
        }

        p = p->next;
    }

    return head;
}


//˫ָ�뷽��
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





// ��һ�ַ�����hash��ȥ��
NODE* delSame(NODE* head)
{
    if (head == NULL || head->next == NULL)
        return head;

    const int size = 256;
    unsigned int count[size]; // ���� unsigned int count[size] = {0}; ��������ÿһ��Ԫ�ض���ʼ��Ϊ0��
    for (int i = 0; i < size; i++) // ����������������һ�������б����������ã����Բ���ѭ���ķ�ʽ�����ס�
        count[i] = 0;

    // count[(unsigned char)(head->data)] = 1; // ��ʹ��û��ͷ�ڵ�ĵ�����ʱ���򿪴��д��뼴�ɡ�

    NODE* p = head; // head�ǵ������ͷ�ڵ㣬ע�⣬ͷ�ڵ�û�����ݣ����Ĵ��ڽ�����Ϊ�˷�����㡣
    NODE* q = p->next;
    NODE* r;
    while (q != NULL)
    {
        if (count[(unsigned char)(q->data)] == 0)
        {
            count[(unsigned char)(q->data)] = 1;
            p = q;
            q = q->next; // ʼ����p��Ϊq��ǰ���ڵ�
        }
        else
        {
            r = q; // r�洢Ҫɾ���Ľڵ�
            p->next = q->next;
            q = p->next; // ʼ����p��Ϊq��ǰ���ڵ�
            free(r);
        }
    }

    return head;

}

int main(int argc, const char* argv[]) {

    char arr[] = "123321";
    int len = (int)strlen(arr);

    NODE* head = createEnd(arr, len);

    // ȥ��֮ǰ
    print(head);
    printf("\n");

    delSame_1(head);

    // ȥ��֮��
    print(head);
    printf("\n");


    return 0;
}
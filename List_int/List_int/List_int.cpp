// List_int.cpp	������ͷ��㣩������������
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "List_int.h"
using namespace std;

// ����Ϊ4�������ĺ����Ķ��壬�亯������������ԭ�ͣ���List_int.h�ļ�

/* ��ʾ��������������� <<��ʹ֮�ܹ�������Node *�����ͽ������
1. ����� << ��˫Ŀ���㣬����Ҫ���������������� cout << a; �У�cout�ǵ�һ��������a�ĵڶ�����������
2. operator<< Ϊ��������������ʽ��������Ϊ��һ���ڶ���������
3. ��һ����ʽ����Ϊ�����Ͳ�����������std���ֿռ��е�ȫ�ֶ���cout����ͬһ���������͡�
   �༴���������£�����out����cout������������out��cout�ı�������
   Ȼ������������cout��ʵ�Ρ������������ļ�������ʵ�Σ���ô�Ϳ���ֱ��������ļ���
4. �ڶ�����ʽ�������ڴ���������׵�ַ��
5. �����ķ���������Ƴɣ����÷���out��������ֵ���أ������ⴴ�����(�豸)���󣬶���ֱ�ӷ��ص�һ�������󶨵����(�豸)����
   �༴�������һ�������� cout����ô������Ҳ���� cout���������ɱ�֤����� << ʵ���������
   ����������ʽ��cout << a << ", " << b ʵ������ (((cout << a) << ", ") << b������(cout << a)����cout��
   �ʿ��Լ���ִ��(cout << ", ")���������cout����һ��ִ�� cout << b���������cout��
*/
ostream& operator<<(ostream& out, const Node* head)// ��������������<<����ʹ���ܹ�ֱ���������<<�����������
{													// ����C++����printf�������������ԭ��֮һ
    const Node* ptr = head->next;
    for (; ptr != NULL; ptr = ptr->next)
        out << ptr->data << endl;					// �����ÿ����������ռһ��
    return out;
}

/* ˼����
1. ��ʽ����newsearch��������ʲô��
2. ��ʽ���� num �к����ã�
3. ΪʲôҪ�� p��k��data ��Ƴɾ�̬�ֲ�������
4. �ֲ��Զ�ָ����� temp ��������ʲô��
5. �����ķ���ֵ��ʲô����������Ƿ��ҵ����������Ľ��
6. ���β�newsearchΪfalse����ʱ�β� x �������ã�ΪʲôҪ������ƣ�
�𣺶���һ�����������������ܴ�������һ�������ļ�����������ˣ���ʱ��Ҫ����ϵ�x��
*/
Node* Locate(Node* head, int x, int& num, bool newsearch)
{
    static Node* p = head;
    static int data = x;			// ���������������ͬ
    static int k = 0;				// ���ͣ�������
    Node* temp;
    if (newsearch)
    {
        p = head;
        data = x;
        k = 0;
    }
    for (; p != NULL && p->data != data; p = p->next, k++)	// �������"��ǰ"������������
        ;
    temp = p;
    num = k;
    if (p != NULL)		// ����ҵ����ڷ����ҵ��Ľ���ַ��temp��֮ǰ��p"����"����ǰ��һ����Ϊ������������׼��
    {
        p = p->next;
        k++;
    }
    return temp;
}

/* ��ʾ
1. �õ��ļ����༰����󣨲μ��̲ĵ�14�µ�2�� �ļ�I/O������
2. �˴����ļ�����Ĭ�ϵ��ı��ļ���ʽ��
3. ������������������������(int)��Ҫ���ܽ��� << �� >> ����(OK)��
4. ������ļ��ĸ�ʽҪ�ܹ�ʹLoad������ȷ�ض�ȡ��
*/
int Save(const char* filename, const Node* head)
{
    ofstream outfile(filename);			// ���ļ������ڽ�����д�����У�
    if (outfile.fail())
        return 0;
    int n = 0;							// ���ڼ��������ͱ���
#if(1)									// �� #if(1) �ĳ� #if(0) �Կ�
    const Node* p;						// �������Ϊ��n�ļ������˴�����ֱ���� outfile << head; ȡ������� for ѭ��
    for (p = head; p != NULL; p = p->next, n++)	// ��������������������������������ļ���
        outfile << p->data << endl;
#else
    outfile << head;					// ���� operator<< ����
    n = NumNodes(head);
#endif
    outfile.close();					// �ر��ļ������������е���������д�뵽�ļ��У���һ�����Ҫ��
    return n;
}

int Load(const char* filename, Node*& head)
{
    int n;							// ���ڼ��������ͱ���
    int x;							// ��������������ͬ�ı���
    ifstream infile(filename);		// ���ļ������ڶ�ȡ���е����ݣ�
    if (infile.fail())
        return 0;
    for (n = 0; infile >> x; n++)		// �������ļ��ж�ȡ���ݣ����γ�һ������
        Append(head, x);
    infile.close();					// �ر��ļ�
    return n;
}

// ���ڴ����6��������Create��NumNodes��ShowList��Insert��Append��FreeList���Ķ���

Node*& Create(Node*& tHead, int tSize, int* tArray)
{
    tHead = new Node{ 114514,nullptr };
    Node* p = tHead;
    for (int i = 0; i < tSize; ++i) {
        p->next = new Node{ tArray[i],nullptr };
        p = p->next;
    }
    return tHead;
}

int NumNodes(const Node* tPtr2Head)
{
    int cnt = 0;
    tPtr2Head = tPtr2Head->next;
    while (tPtr2Head) {
        tPtr2Head = tPtr2Head->next;
        ++cnt;
    }
    return cnt;
}

int ShowList(const Node* tPtr2Head)
{
    int cnt = 0;
    cout << "head => ";
    tPtr2Head = tPtr2Head->next;
    while (tPtr2Head) {
        cout << tPtr2Head->data << " => ";
        tPtr2Head = tPtr2Head->next;
        ++cnt;
    }
    cout << "nullptr";
    cout << "\n*** Show List finished.\n";
    return cnt;
}

Node* Insert(Node*& tHead, int tData)
{
    tHead->next = new Node{ tData, tHead->next };
    return tHead;
}

Node* Append(Node*& tHead, int tData)
{
    if (!tHead->next) {
        tHead->next = new Node{ tData,nullptr };
        return tHead;
    }
    Node* ptr = tHead;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = new Node{ tData,nullptr };
    return tHead;
}

void FreeList(Node* tHead)
{
    Node* nextNode = nullptr;
    while (tHead) {
        nextNode = tHead->next;
        delete tHead;
        tHead = nextNode;
    }
}
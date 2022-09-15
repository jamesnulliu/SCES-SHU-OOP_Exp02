// List_int.h		�����������������֯��ʽ����
#ifndef LIST_INT_H
#define LIST_INT_H
#include <iostream>
using namespace std;

struct Node
{
    int data;			// ������(��Ȼ�������һ�����ݣ�������������datum�ĸ�����ʽ)
    Node* next;		// ָ����
};

// ����Ϊ4�������ĺ���ԭ�ͣ��䶨������ɣ���List_int.cpp�ļ���
ostream& operator<<(ostream& out, const Node* head);
Node* Locate(Node* head, int x, int& num, bool newsearch = false);	// �����ҵ��Ľ���ַ��"����"�ý������num
int Save(const char* filename, const Node* head);
int Load(const char* filename, Node*& head);

// ���ڴ˲���6��������Create��NumNodes��ShowList��Insert��Append��FreeList���ĺ���ԭ������
Node*& Create(Node*& tHead, int tSize, int* tArray);

int NumNodes(const Node* tPtr2Head);

int ShowList(const Node* tPtr2Head);

Node* Insert(Node*& tHead, int tData);

Node* Append(Node*& tHead, int tData);

void FreeList(Node* tPtr2Head);

#endif
#ifndef CHAINLIST
#define CHAINLIST
#include <iostream>
#include "myExceptions.h"

template <typename T>
struct Node
{
    T data;
    Node<T>* next;
    // Initialize the node.
    Node(T e = 0, Node<T>* n = nullptr) :data(e), next(n) {}
};

template <class T>
class ChainList
{
public: // Firend function needs to be declared as a template function in class template.
    template <class TT> friend std::ostream& operator<<(std::ostream&, const ChainList<TT>& tChain);
    // @brief Return the data of node[index].
    // [NOTE] {headnode} is the 0th node, BUT node[0] is {headnode->next}.
    T& operator[](int index) { return getNode(index + 1)->data; }

private:
    // Initialize member {headnode} with default constructor of class {ChianNode}.
    void init();
public:
    // @brief Constructor: Invoke function {init()} to initialize the list.
    ChainList();
    // @brief Constructor: Initialize the list while storing information {info} into {headnode}.
    ChainList(T info);
    // @brief Destructor.
    ~ChainList();
public:
    int size() const { return m_size; }
    bool empty() const { return !m_size; }

    // Return the reference of the information in headnode.
    T& info() { return headnode->data; }

    // Return the pointer of the first node, i.tData., {headnode->next}.
    Node<T>* getFirstNode() const { return headnode ? headnode->next : nullptr; }

    // Create a new node with data {tData} and insert it after {headnode}.
    void insert(const T& tData);

    // Create a new node with data {tData} and insert it after {tNode}.
    void insert(Node<T>* tNode, const T& tData);

    // @brief Create a new node with data {tData} and insert it after the {i}th node.
    // [NOTE] Although the new node is inserted after the {i}th node,
    //        it's INDEX is [i] among the data-stroing nodes (all except {headnode}).
    // [E.G.] `insert(0, tData)` inserts the new node after {headnode},
    //        and the new node's index is [0], because {headnode->next} is the first data-storing node.
    void insert(int i, const T& tData);

    void push_back(const T& tData) { insert(m_size - 1, tData); }

    // @brief Erase the ({index}+1)th node (whose index is {index}).
    void erase(int index);

    // @brief Return the pointer of the {i}th node.
    // [NOTE] {headnode} is the 0th, while {headnode->next} is the 1th.
    Node<T>* getNode(int i);

    // Bin Sort.
    void binSort(int);

protected:
    int m_size;
    Node<T>* headnode;
    // Initialize the header.
};

template<class T>
void ChainList<T>::init()
{
    headnode = new Node<T>;
    headnode->next = nullptr;
    m_size = 0;
}

template<class T>
ChainList<T>::ChainList()
{
    init();
}

template<class T>
ChainList<T>::ChainList(T info)
{
    init();
    headnode->data = info;
}

template<class T>
ChainList<T>::~ChainList()
{
    Node<T>* p = headnode;
    while (headnode) {
        p = p->next;
        delete headnode;
        headnode = p;
    }
}

template<class T>
inline void ChainList<T>::insert(const T& tData)
{
    m_size++;
    Node<T>* p = new Node<T>(tData, headnode->next);
    headnode->next = p;
}

template<class T>
inline void ChainList<T>::insert(Node<T>* tNode, const T& tData)
{
    if (!tNode) return;
    m_size++;
    Node<T>* s = new Node<T>(tData, tNode->next);
    tNode->next = s;
}

template<class T>
inline void ChainList<T>::insert(int i, const T& tData)
{
    insert(getNode(i), tData);
}

template<class T>
inline Node<T>* ChainList<T>::getNode(int i)
{
    int j = 0;
    Node<T>* p = headnode;
    while (p && j < i) { p = p->next; ++j; }
    if (!p || j != i) {
        throw EmptyChain("{getNode()} The node does not exist.");
        return nullptr;
    } else return p;
}
template<class T>
void ChainList<T>::erase(int index)
{
    if (index >= m_size) {
        throw EmptyChain("{erase()} The node does not exist.");
    }
    Node<T>* p = getNode(index), * target = p->next;
    p->next = target->next;
    delete target;
    --m_size;
}

template<>
void ChainList<int>::binSort(int range)
{
    // Allocate the firstNode to "pNode".
    Node<int>* pNode = getFirstNode();

    // Create and initialize the bins.
    Node<int>** bottom, ** top;
    bottom = new Node<int>*[range + 1];
    top = new Node<int>*[range + 1];
    for (int i = 0; i <= range; i++) {
        bottom[i] = nullptr;
    }

    // Allocate the nodes to the bins,
    // in each bin, it should be empty or a chain in which nodes have same elements.
    for (; pNode != nullptr; pNode = pNode->next) {
        int theBin = pNode->data;
        // The bin is empty:
        if (bottom[theBin] == nullptr) {
            top[theBin] = pNode;
            bottom[theBin] = top[theBin];
        }
        // The bin is not empty:
        else {
            top[theBin]->next = pNode;
            top[theBin] = pNode;
        }
    }

    // Collect the nodes in the bins and assemble them to an ordered chain.
    Node<int>* temp = nullptr;
    for (int theBin = 0; theBin <= range; theBin++) {
        if (bottom[theBin] != nullptr) {
            // The first non-empty bin.
            if (temp == nullptr) {
                headnode->next = bottom[theBin];
            }
            // Not the first non-empty bin.
            else {
                temp->next = bottom[theBin];
            }
            temp = top[theBin];
        }
    }
    if (temp != nullptr) {
        temp->next = nullptr;
    }

    delete[] bottom;
    delete[] top;
}

template <class TT> std::ostream& operator<<(std::ostream& out, const ChainList<TT>& tChain)
{
    Node<TT>* p = tChain.getFirstNode();
    if (!p) {
        out << "Output failed.";
        throw EmptyChain();
        return out;
    }
    int index = 0;
    out << "Output the chian list: \n*** headnode -> ";
    while (p) {
        out << '[' << index++ << "] " << p->data << " -> ";
        p = p->next;
    }
    out << "nullptr *** \nOutput ended.";
    return out;
}

#endif // !CHAINLIST

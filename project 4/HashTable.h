#ifndef __project__HashTable__
#define __project__HashTable__
#include <string>
#include <functional>
using namespace std;
template <typename KeyType, typename ValueType>
struct Node
{
    Node(ValueType value,KeyType key,bool permanent)
    {next=nullptr;
        prev=nullptr;
        m_value=value;
        m_key=key;
        pmnt=permanent;
        t_prev=nullptr;
        t_next=nullptr;
    } ValueType m_value;
    KeyType m_key;
    Node* next;
    Node* prev;
    bool pmnt;
    Node* t_prev;
    Node* t_next;
};

template <typename KeyType, typename ValueType>
class linkedList
{
public:
    linkedList()
    {
        head=nullptr;
    }
    void add(ValueType value,KeyType key,bool permanent)
    {
        if (head==nullptr) {
            Node<KeyType,ValueType>* p=new Node<KeyType,ValueType>(value,key,permanent);
            head=p;
            return;
        }
        Node<KeyType,ValueType>* q;
        q=head;
        Node<KeyType,ValueType>* a=new Node<KeyType,ValueType>(value,key,permanent);
        head=a;
        a->next=q;
        q->prev=a;
        
    }
    
    Node<KeyType,ValueType>* contain(KeyType key)
    {
        Node<KeyType,ValueType>* p=head;
        while (p!=nullptr) {
            if (p->m_key==key)
                return p;
            p=p->next;
        }
        return nullptr;
    }
    void update(ValueType value,Node<KeyType, ValueType>* p)
    {
        p->m_value=value;
    }
    ~linkedList()
    {
        Node<KeyType, ValueType>* p;
        if (head==nullptr) {
            return;
        }
        while (head->next!=nullptr) {
            p=head->next;
            head->next=p->next;
            delete p;
        }
        p=head->next;
        delete p;
    }
    Node<KeyType, ValueType>* getHead()
    {
        return head;
    }
    
private:
    
           Node<KeyType,ValueType>* head;
};

template <typename KeyType, typename ValueType>
class HashTable {
public:
    HashTable(unsigned int numBuckets, unsigned int capacity)
    {
        itemCount=numBuckets;
        hashTableSize=capacity;
        crtcap=0;
        table=new linkedList<KeyType,ValueType>[numBuckets];
        prev=nullptr;
        next=nullptr;
    }
    bool isFull() const
    {
        return crtcap==hashTableSize;
    }
    bool set(const KeyType& key, const ValueType& value, bool permanent=false)
    {   unsigned int temp=getBucketForKey(key);
        Node<KeyType,ValueType>* p=table[temp].contain(key);
        if (p==nullptr)
        {
            if (isFull())
                return false;
            table[temp].add(value,key,permanent);
            
            Node<KeyType, ValueType>* q=table[temp].getHead();
            if (!q->pmnt)
            {q->t_prev=next;
            next=q;
            if (q->t_prev!=nullptr)
            {
                q->t_prev->t_next=q;
            }
            else
                prev=q;}
        }
        else
        {
            table[temp].update(value,p);
            if (p->t_next!=nullptr&&(!p->pmnt)) {
                Node<KeyType, ValueType>* tempNode=p->t_next;
                if (p->t_prev!=nullptr)
                    p->t_prev->t_next=tempNode;
                else
                    prev=tempNode;
                tempNode->t_prev=p->t_prev;
                p->t_prev=next;
                next=p;
                p->t_next=nullptr;
            }
            
        }
        return true;
    }
    unsigned int getBucketForKey(const KeyType& key)
    {
        unsigned int computeHash(const string&s);
        unsigned int computeHash(unsigned short num);
        unsigned int result=computeHash(key);
        
        unsigned int bucketNum=0;
        if (itemCount!=0)
        bucketNum=result%itemCount;
        return bucketNum;
    }
    bool get(const KeyType& key, ValueType& value)
    {
        unsigned int temp=getBucketForKey(key);
        Node<KeyType,ValueType>* p=table[temp].contain(key);
        if (p==nullptr)
            return false;
        value=p->m_value;
        return true;
    }
    bool touch(const KeyType& key)
    {
        unsigned int temp=getBucketForKey(key);
        Node<KeyType,ValueType>* p=table[temp].contain(key);
        if (p!=nullptr&&!p->pmnt)
        {if (p->t_next!=nullptr) {
            Node<KeyType, ValueType>* tempNode=p->t_next;
            if (p->t_prev!=nullptr)
                p->t_prev->t_next=tempNode;
            else
                prev=tempNode;
            tempNode->t_next->t_prev=p->t_prev;
            p->t_prev=next;
            next=p;
            p->t_next=nullptr;
        }
            return true;
        }
        return false;
    }

bool discard(KeyType& key, ValueType& value)
    {
        if (prev==nullptr)
        {
            return false;
        }
        Node<KeyType,ValueType>* p=prev;
        prev=p->t_next;
        key=p->m_key;
        value=p->m_value;
        if (p->prev!=nullptr) {
            p->prev->next=p->next;
            p->next->prev=p->prev;
            delete p;
        }
        else if (p->next!=nullptr)
        {
            p->m_key=p->next->m_key;
            p->m_value=p->next->m_value;
            Node<KeyType, ValueType>* tempNode=p->next;
            p->next=tempNode->next;
            delete tempNode;
        }
        else
        {
            delete p;
        }
        return true;
    }
private:
    HashTable(const HashTable&);
    HashTable& operator=(const HashTable&);
   unsigned int itemCount,hashTableSize,crtcap;
    linkedList<KeyType,ValueType>* table;
    Node<KeyType, ValueType>* prev;
    Node<KeyType,ValueType>* next;//prev hold the pointer of the earlist added node, and next hold the pointer of the latest added node
};

#endif /* defined(__project__HashTable__) */

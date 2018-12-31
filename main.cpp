//
//  main.cpp
//  List:
//  链表的操作：
//     1.头插入
//     2.尾插入建立链表;
//     3.遍历链表；
//     4.链表是否为空
//     5.销毁
//     6.求链表的长度
//     7.排序
//     8.插入结点
//     9.删除结点：记得要释放删除节点的存储空间，避免内存泄漏
//     10.将链表逆置
//     11.退出

#include <iostream>
using namespace std;

struct Node { // 结点定义
    int data; // 数据域
    Node *next; // 指针域：指向下一个结点
};

// 头插入建立链表:引入头结点（不存放数据的结点，为了方便对链表操作）
// 注意区分头结点和首结点（链表中第一个存放有效数据的结点，即头结点指向的下一个结点）
Node *headCreate() {
    int len, val; // val临时存放用户输入的结点的值
    
    // 动态分配内存空间，
    Node *head = new Node(); // 头结点
    head->next = NULL;
    if(head == NULL) {
        cerr << "申请空间失败，程序终止！" << endl;
        exit(1);
    }
    cout << "请输入你需要生成的链表结点的个数:";
    cin >> len;
    cout << "请输入各个结点的值:";
    for(int i = 0; i < len; i++) {
        cin >> val;
        Node *newNode = new Node(); // 新结点
        if(newNode == NULL) {
            cerr << "申请空间失败，程序终止！" << endl;
            exit(1);
        }
        newNode->data = val;
        // 因为head是头结点（指向首结点），所以新结点应该挂入到原头结点指向
        // 的下一个有效结点（即首结点）前面，成为新的首结点
        newNode->next = head->next; // 先保存原首结点
        // 头结点往前移，永远都是头结点
        // 注意，因为头结点是不存放数据的，所以是head->next 指向新结点
        head->next = newNode; // 挂入到头结点的下一个结点，成为新的首结点
    }
    return head; // 把头结点返回
}

// 尾插入建立链表
Node *tailCreate() {
    int len, val; // val临时存放用户输入的结点的值
    
    // 动态分配内存空间，引入头结点（不存放数据的结点，为了方便对链表操作）
    Node *head = new Node();
    Node *tail = head; // 尾结点，跟着链表走
    tail->next = NULL; // 可以不写，默认为空
    if(head == NULL) {
        cerr << "申请空间失败，程序终止！" << endl;
        exit(1);
    }
    cout << "请输入你需要生成的链表结点的个数:";
    cin >> len;
    cout << "请输入各个结点的值:";
    for(int i = 0; i < len; i++) {
        cin >> val;
        Node *newNode = new Node(); // 新结点
        if(newNode == NULL) {
            cerr << "申请空间失败，程序终止！" << endl;
            exit(1);
        }
        newNode->data = val;
        newNode->next = NULL; // 可以省略，默认为空
        tail->next = newNode; // 尾结点指向新结点
        tail = newNode; // 尾结点往后移，永远都是尾结点
    }
    return head; // 把头结点返回
}

// 遍历链表
void Traverse(Node *head) {
    Node *curr = head->next;
    
    while(curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next; // 往后移，移向下一个结点
    }
    cout << endl;
}

// 判断链表是否为空
bool isEmpty(Node *head) {
    Node *p = head->next;
    
    if(NULL == p)
        return true;
    return false;
}

// 销毁(清空)链表
void clearList(Node *head) {
    Node *cur = head->next; // 先保存头结点指向的下一个结点
    Node *curNext = NULL;
    
    head->next = NULL; // 指向空
    while(cur != NULL) {
        // 先保存好下一个结点，防止删除当前结点，丢失链表
        curNext = cur->next;
        delete cur; // 释放cur存储空间
        cur = NULL; // 指向空
        cur = curNext; // 移动到下一个结点
    }
}

// 求链表的长度
int listLength(Node *head) {
    Node *cur = head->next;
    int len = 0;
    
    while(cur != NULL) {
        len++;
        cur = cur->next;
    }
    return len;
}

// 链表排序
void Sort(Node *head, int len) {
    int i, j, temp;
    
    Node *cur, *curNext;
    // 类似选择排序
    for(i = 0, cur = head->next; i < len-1; i++, cur = cur->next) {
        for(j = i+1, curNext = cur->next; j < len; j++, curNext = curNext->next) {
            if(cur->data > curNext->data) { // 类似于a[i] > a[j]
                // 交换两个结点中的值
                temp = cur->data;
                cur->data = curNext->data;
                curNext->data = temp;
            }
        }
    }
}

// 插入函数：在第pos位置前面插入val值
bool Insert(Node *head, int pos, int val) {
    int i = 1;
    Node *cur = head->next;
    
    while(cur != NULL && i < pos-1) {
        cur = cur->next;
        i++;
    }
    
    if(i > pos-1 || cur == NULL) // 其实i > pos-1可以不写
        return false;
    Node *newNode = new Node();
    if(newNode == NULL) {
        cerr << "动态内存分配失败！" <<endl;
        exit(1);
    }
    // 将newNode挂入到pos位置
    newNode->data = val;
    Node *q = cur->next;
    cur->next = newNode;
    newNode->next = q;
    return true;
}

// 删除函数：删除第pos位置的结点
bool Delete(Node *head, int pos, int &pVal) {
    int i = 1;
    Node *cur = head->next;
    
    while(cur != NULL && i < pos-1) {
        cur = cur->next;
        i++;
    }
    
    if(i > pos-1 || cur == NULL) // 其实i > pos-1可以不写
        return false;
    Node *q = cur->next;
    pVal = q->data; // 保存删除结点的数据
    cur->next = cur->next->next;
    delete q;
    q = NULL;
    return true;
}

// 逆置链表：
void ReverseList(Node *head) {
    Node *p = head->next;
    Node *q;
    
    head->next = NULL; // 要先将头结点的next指向空,防止出现循环
    while(p != NULL) {
        q = p->next; // 先保存下一个的下一个结点
        p->next = head->next; // 拆下来进行头插入
        head->next = p; // 头结点往前移
        p = q; // 重新找回原链表的首结点
    }

}

int main(int argc, const char * argv[]) {
    Node *head = NULL; // 头指针
    int finished = 0, choice, len; // len存储链表的长度
    int pos, val;
    
    while(!finished) {
        std::cout << "\n*********菜单*********\n";
        std::cout << "1:头插入建链\n";
        std::cout << "2:尾插入建链\n";
        std::cout << "3:遍历链表\n";
        std::cout << "4:链表是否为空\n";
        std::cout << "5:销毁链表\n";
        std::cout << "6:求链表的长度\n";
        std::cout << "7:排序\n";
        std::cout << "8:插入\n";
        std::cout << "9:删除\n";
        std::cout << "10:逆置链表\n";
        std::cout << "11:退出\n";
        std::cout << "请输入选择（1-11）：" << endl;
        std::cin >> choice;
        switch(choice) {
            case 1:
                head = headCreate(); // 头插入建立链表
                break;
            case 2:
                head = tailCreate(); // 尾插入建立链表
                break;
            case 3:
                Traverse(head); // 遍历链表
                break;
            case 4:
                if(isEmpty(head)) // 判断链表是否为空
                    cout << "链表为空！" << endl;
                else
                     cout << "链表不为空！" << endl;
                break;
            case 5:
                clearList(head); // 销毁链表
                break;
            case 6:
                len = listLength(head); // 求链表的长度
                cout << "链表的长度为：" << len <<endl;
                break;
            case 7:
                cout << "排序前，链表的元素顺序为：" << endl;
                Traverse(head);
                len = listLength(head);
                Sort(head, len); // 排序
                cout << "排序后，链表的元素从小到大为：" << endl;
                Traverse(head);
                break;
            case 8:
                cout << "请输入插入的位置pos和相应的值val" << endl;
                cin >> pos >> val;
                cout << "插入前链表中的元素为：" << endl;
                Traverse(head);
                if(Insert(head, pos, val)) { // 插入
                    cout << "插入后链表中的元素为：" << endl;
                    Traverse(head);
                }
                else
                    cout << "插入失败！" << endl;
                break;
            case 9:
                cout << "请输入要删除的位置pos" << endl;
                cin >> pos;
                cout << "删除结点前链表中的元素为：" << endl;
                Traverse(head);
                if(Delete(head, pos, val)) { // 删除函数
                    cout << "删除成功!" << endl;
                    cout << "删除结点后链表的元素顺序为:" << endl;
                    Traverse(head);
                    cout << "删除的结点的值为：" << val << endl;
                }
                else
                    cout << "删除失败！" << endl;
                break;
            case 10:
                ReverseList(head); // 逆置链表
                break;
            case 11:
                finished = 1; // 退出while循环
                break;
            default:
                cout << "输入错误，请重新输入" << endl;
        }
    }
    return 0;
}

struct Node{
    int data;
    Node* next;
};

struct List{
    Node *head;
    Node *tail;
    List();
    void InsertInTail(int data);
    void InsertInHead(int data);
    int Remove();
};
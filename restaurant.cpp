#include "main.h"
bool isSeated[MAXSIZE + 1];
int arrayIDrelateResult[MAXSIZE + 1];
queue<string> FIFO;
vector<string> LRCO;
bool isValidCLE(string infor)
{
    regex pattern("^CLE -?[0-9]+$");
    return regex_match(infor, pattern);
}
bool isValidREG(string infor) {
    regex pattern("^REG [A-Za-z]+$");
    return regex_match(infor, pattern);
}
void insertLRCO(vector<string> &v, string name)
{
    auto it = find(v.begin(), v.end(), name);
    if (it != v.end())
    {
        v.erase(it);
    }
    v.push_back(name);
}
void deleteLRCO(vector<string> &v, string name)
{
    auto it = find(v.begin(), v.end(), name);
    if (it != v.end()) v.erase(it);
}
void removeElementFromQueue(queue<string>& FIFO, string elementToRemove) 
{
    string Elementfirst = FIFO.front();
    if (Elementfirst == elementToRemove)
    {
        FIFO.pop();
        return;
    }
    else
    {
        FIFO.pop();
        FIFO.push(Elementfirst);
        while(FIFO.front() != Elementfirst)
        {
            string frontElement = FIFO.front();
            if (frontElement == elementToRemove)
            {
                FIFO.pop();
                frontElement = FIFO.front();
            }
                FIFO.pop();
                FIFO.push(frontElement);
        }
    }
}
struct MinHeapNode {
    char data;
    unsigned freq;
    unsigned order;
    MinHeapNode *left, *right;
    MinHeapNode(char data, unsigned freq, unsigned order)
    {
        left = right = NULL;
        this -> data = data;
        this -> freq = freq;
        this -> order = order;
    }
};
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        if (l -> freq == r -> freq )
        {
            if (r -> data == l -> data)
            {
                return (l -> order > r -> order);
            }
            return (l -> data > r -> data);
        }
        return (l -> freq > r -> freq );
    }
};
void deleteMinHeap(MinHeapNode *node)
{
    if (node == NULL) return;
    deleteMinHeap(node -> left);
    deleteMinHeap(node -> right);
    delete node;
} 
void saveCodes(struct MinHeapNode* root, string str, string EncodeHuffman[])
{ 
    if (!root) return;
    if (root -> data != '~') EncodeHuffman[int(root -> data)] = str;
    saveCodes(root -> left, str + "0", EncodeHuffman);
    saveCodes(root -> right, str + "1", EncodeHuffman);
}
void HuffmanCodes(int asciiArray[], int size, string EncodeHuffman[])
{
    struct MinHeapNode *left, *right, *top;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    unsigned order = 0;
    for (int i = 0; i < 255; i++)
    {
        if (asciiArray[i] != 0)
        minHeap.push(new MinHeapNode(char(i), asciiArray[i], order++));
    }
    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('~', left -> freq + right -> freq, order++);
        top -> left = left;
        top -> right = right;
        minHeap.push(top);
    }
    saveCodes(minHeap.top(), "", EncodeHuffman);
    deleteMinHeap(minHeap.top());
}
int convertbin2dec(string bin)
{
    int dec = 0;
    int len = bin.size();
    for(int i = 0; i < len; i++)
    {
        int bit = bin[i] - '0';
        dec += bit * pow(2, len - i - 1);
    }
    return dec;
}
struct Customer
{
    string Name;
    int ID;
    int Result;
    int NumsofOrder;
    bool status;
};
int OrderEntry = 0;
class MinHeap 
{
private:
    vector<Customer> heap;
    void Reheap_Up(int idx) 
    {
        int parent = (idx - 1) / 2;
        while (idx > 0 && heap[idx].NumsofOrder <= heap[parent].NumsofOrder)
        {
            if ((heap[idx].NumsofOrder == heap[parent].NumsofOrder) && (heap[idx].Result > heap[parent].Result)) break;
            swap(heap[idx], heap[parent]);
            idx = parent;
            parent = (idx - 1) / 2;
        }
    }
    void Reheap_Down(int idx) 
    {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;
        int size = heap.size();
        if (left < size && ((heap[left].NumsofOrder < heap[smallest].NumsofOrder) || (heap[left].NumsofOrder == heap[smallest].NumsofOrder && heap[left].Result < heap[smallest].Result))) smallest = left;
        if (right < size && ((heap[right].NumsofOrder < heap[smallest].NumsofOrder) || (heap[right].NumsofOrder == heap[smallest].NumsofOrder && heap[right].Result < heap[smallest].Result))) smallest = right;
        if (left < size && right < size && heap[right].NumsofOrder == heap[left].NumsofOrder && ((left == smallest) ||(right == smallest)))
        {
            if (heap[left].Result < heap[right].Result)
            {
                smallest = left;
            }
            else smallest = right;
        }
        if (smallest != idx) 
        {
            swap(heap[idx], heap[smallest]);
            Reheap_Down(smallest);
        }
    }
public:
    int getsize()
    {
         return heap.size();
    }
    void push(Customer cus) 
    {
        heap.push_back(cus);
        OrderEntry++;
        Reheap_Up(heap.size() - 1);
    }
    void delete_element(int idx)
    {
        heap[idx] = heap.back();
        heap.pop_back();
        int parent = (idx - 1) / 2;
        if (heap[idx].NumsofOrder <= heap[parent].NumsofOrder)
        {
            Reheap_Up(idx);
        }
            Reheap_Down(idx);
    }
    void deletefollowName(string Name)
    {
        int size = heap.size();
        for (int i = 0; i < size; i++)
        {
            if (heap[i].Name == Name)
            {
                delete_element(i);
            }
        }
    }
    string pop()
    {
        Customer cus = heap.front();
        heap[0] = heap.back();
        heap.pop_back();
        Reheap_Down(0);
        return cus.Name;
    }
    void upnumOrder(string name)
    {
        int i;
        Customer newCus;
        int size = heap.size();
        for (int index = 0; index < size; index++)
        {
            if (heap[index].Name == name)
            {
                i = index;
                newCus = heap[index];
                break;
            }
        }
        newCus.NumsofOrder = newCus.NumsofOrder + 1;
        delete_element(i);
        push(newCus);
    }
    bool empty()
    {
        return heap.empty();
    }
    void printPreorder(int idx)
    {
        int size = heap.size();
        if (idx >= size) return;
        cout << heap[idx].ID << "-" << heap[idx].NumsofOrder << "\n";
        printPreorder(2 * idx + 1);
        printPreorder(2 * idx + 2);
    }
};
    MinHeap LFCO;
    class HashTable
    {
        private:
        Customer *table;
        int numElements;

        int hashFunc(int key)
        {
            return key % (MAXSIZE / 2);
        }
        public:
        HashTable()
        {
            table = new Customer[MAXSIZE / 2];
            for (int i = 0; i < MAXSIZE / 2; i++)
            {
                table[i].Name = "";
                table[i].ID = -1;
                table[i].Result = -1;
                table[i].NumsofOrder = 0;
                table[i].status = false;
            }
            numElements = 0;
        }
        ~HashTable()
        {
            delete[] table;
        }
        void insert(int ID, int Result, string Name)
        {
            for (int i = 0; i < MAXSIZE / 2; i++)
            {
                if (table[i].Name == Name)
                {
                    table[i].NumsofOrder++;
                    LFCO.upnumOrder(Name);
                    insertLRCO(LRCO, Name);
                    return;
                }
            }
            bool forChecking = false;
            if(isSeated[ID] == true)
            {   
                for (int i = ID + 1; i <= MAXSIZE; i++)
                {
                    if(isSeated[i] == false)
                    {
                        ID = i;
                        forChecking = true;
                        break;
                    }
                }
                if (forChecking == false)
                {
                    for (int i = 1; i < ID; i++)
                    {
                         if(isSeated[i] == false)
                            {
                                ID = i;
                                break;
                            }
                    }
                }
            }
            int index = hashFunc(Result);
            while(table[index].status != false)
            {
                index = (index + 1) % (MAXSIZE / 2);
            }
            table[index].Name = Name;
            table[index].ID = ID;
            table[index].Result = Result;
            table[index].NumsofOrder = 1;
            table[index].status = true;
            numElements++;
            isSeated[ID] = true;
            //fifo
            FIFO.push(Name);
            // min heap
            Customer cus;
            cus.Name = Name;
            cus.ID = ID;
            cus.Result = OrderEntry;
            cus.NumsofOrder = 1;
            LFCO.push(cus);
            insertLRCO(LRCO, Name);
        }
        void remove(int ID)
        {
            bool check = false;
            int position;
            for (int i = 0; i < MAXSIZE / 2; i++)
            {
                if (table[i].ID == ID)
                {
                    check = true;
                    position = i;
                    break;
                }
            }
            if (check)
            {
                deleteLRCO(LRCO, table[position].Name);
                LFCO.deletefollowName(table[position].Name);
                removeElementFromQueue(FIFO, table[position].Name);
                isSeated[table[position].ID] = false;
                table[position].Name = "";
                table[position].ID = -1;
                table[position].Result = -1;
                table[position].NumsofOrder = 0;
                table[position].status = false;
                numElements--;
            }
            else
            {
                return;
            }
        }
        void removeALL()
        {
            queue<string> temp_FIFO = FIFO;
            int arrayDelete[numElements];
            int i = 0;
            while (!temp_FIFO.empty())
            {
                int IDdelete = IDfollowName(temp_FIFO.front());
                temp_FIFO.pop();
                if (IDdelete != -1)
                {
                    arrayDelete[i] = IDdelete;
                    i++;
                }
            }
            for (int j = 0; j < i; j++)
            {
                remove(arrayDelete[j]);
            }
        }
        int IDfollowName(string Name)
        {
            for (int i = 0; i < MAXSIZE / 2; i++)
            {
                if (table[i].Name == Name)
                {
                    int idReturn = table[i].ID;
                    return idReturn;
                }
            }
            return - 1;
        }
        int getnumElements()
        {
            return numElements;
        }
        void print()
        {
            for (int i = 0; i < MAXSIZE / 2; i++)
            {
                if (table[i].status != false)
                {
                    cout << table[i].ID << '-' << table[i].Result << "-" << table[i].NumsofOrder << "\n";
                }
            }
        }
    };
enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};
class AVLTree
{
    public:
    class Node;
    private:
    Node *root;
    int numElements = 0;
    public:
    Node* searchNode(string name, Node * temp)
    {
        if (temp == NULL) return NULL;
        if (temp -> Name == name)
        {
            return temp;
        }
        Node *check1 = searchNode(name, temp -> pLeft);
        if (check1 != NULL) return check1;
        else
        {
            Node * check2 = searchNode(name, temp -> pRight);
            return check2;
        }
    }
    Node* isExist(string Name)
    {
        Node *temp = root;
        return searchNode(Name, temp);
    }
    bool SolveDuplicate(const int &value, string Name)
    { 
        Node *check = isExist(Name);
        if (check != NULL)
        {
            check -> NumofOrder = check -> NumofOrder + 1;
            LFCO.upnumOrder(Name);
            return 1;
        }
        return 0;
    }
    void deleteTree()
    {
        queue<string> temp_FIFO = FIFO;
        int arrayDelete[numElements];
        int i = 0;
        while (!temp_FIFO.empty())
        {
            int IDdelete = searchIDfollowName(temp_FIFO.front());
            if (IDdelete != -1)
            {
                arrayDelete[i] = IDdelete;
                i++;
            }
            temp_FIFO.pop();
        }
        for (int j = 0; j < i; j++)
        {
            remove(arrayDelete[j]);
        }
    }
    int searchIDfollowName2(string name, Node * temp)
    {
        if (temp == NULL) return -1;
        if (temp -> Name == name)
        {
            return temp -> ID;
        }
        int check1 = searchIDfollowName2(name, temp -> pLeft);
        if (check1 != -1) return check1;
        else
        {
            int check2 = searchIDfollowName2(name, temp -> pRight);
            return check2;
        }
    }
    int searchIDfollowName(string Name)
    {
        Node *temp = root;
        return searchIDfollowName2(Name, temp);
    }
    int getnumElements()
    {
        return numElements;
    }
    void PrintAVL(Node *temp)
    {
        if (root == NULL) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) 
        {
            Node* temp = q.front();
            q.pop();
            cout << temp -> ID << "-" << temp -> data << "-" << temp -> NumofOrder << "\n";
            if (temp -> pLeft != NULL) q.push(temp -> pLeft);
            if (temp -> pRight != NULL) q.push(temp -> pRight);
        }
    }
    void printAVL()
    {
        Node *temp = root;
        PrintAVL(temp);
    }
    Node* rotateRight(Node* root)
    {
        Node* temp = root -> pLeft;
        root -> pLeft = temp -> pRight;
        temp -> pRight = root;
        return temp;
    }
    Node* rotateLeft(Node* root)
    {
        Node* temp = root -> pRight;
        root -> pRight = temp -> pLeft;
        temp -> pLeft = root;
        return temp;
    }
    Node* leftbalance(Node* root, bool &taller)
    {
        Node* ltree = root -> pLeft;
        if (ltree -> balance == LH)
        {
            root = rotateRight(root);
            root -> balance = EH;
            root -> pRight -> balance = EH;
            taller = false;
        }
        else
        {
            Node* rtree = ltree -> pRight;
            if (rtree -> balance == LH)
            {
                root -> balance = RH;
                ltree -> balance = EH;
            }
            else if (rtree -> balance == EH) 
            {
                ltree -> balance = EH;
                root -> balance = EH;
            }
            else 
            {
                root -> balance = EH;
                ltree -> balance = LH;
            }
            rtree -> balance = EH;
            root -> pLeft = rotateLeft(ltree);
            root = rotateRight(root);
            taller = false;
        }
        return root;
    }
    Node* rightbalance(Node* root, bool &taller)
    {
        Node* rtree = root -> pRight;
        if (rtree -> balance == RH)
        {
            root = rotateLeft(root);
            root -> balance = EH;
            root -> pLeft -> balance = EH;
            taller = false;
        }
        else
        {
            Node* ltree = rtree -> pLeft;
            if (ltree -> balance == RH)
            {
                root -> balance = LH;
                rtree -> balance = EH;
            }
            else if (ltree -> balance == EH) 
            {
                rtree -> balance = EH;
                root -> balance = EH;
            }
            else 
            {
                root -> balance = EH;
                rtree -> balance = RH;
            }
            ltree -> balance = EH;
            root -> pRight = rotateRight(rtree);
            root = rotateLeft(root);
            taller = false;
        }
        return root;
    }
    Node*insertAVL(Node*root, int value, bool& taller, string Name, int ID)
    {
        if (root == NULL)
        {
            Node* temp = new Node(value);
            root = temp;
            taller = true;
            root -> balance = EH;
            root -> ID = ID;
            root -> Name = Name;
            return root;
        }
        if (root -> data > value)
        {
            root -> pLeft = insertAVL(root -> pLeft, value, taller, Name, ID);
            if (taller)
            {
                if (root -> balance == LH) root = leftbalance(root, taller);
                else if (root -> balance == EH) root -> balance = LH;
                else
                {
                    root -> balance = EH;
                    taller = false;
                }
            }
        }
        else
        {
            root -> pRight = insertAVL(root -> pRight, value, taller, Name, ID);
            if (taller)
            {
                if (root -> balance == RH) root = rightbalance(root, taller);
                else if (root -> balance == EH) root -> balance = RH;
                else
                {
                    root -> balance = EH;
                    taller = false;
                }
            }       
        }
        return root;
    }
    Node* deleteleft(Node* root, bool &shorter)
    {
        if (root -> balance == RH)
        {
            root -> balance = EH;
        }
        else if (root -> balance == EH)
        {
            root -> balance = LH; 
            shorter = false;
        }
        else
        {
            Node* ltree = root -> pLeft;
            if (ltree -> balance == RH)
            {
                Node* rtree = ltree -> pRight;
                if (rtree -> balance == RH)
                {
                    ltree -> balance = LH;
                    root -> balance = EH;
                }
                else if (rtree -> balance == EH)
                {
                    root -> balance = EH;
                    ltree -> balance = EH;
                }
                else
                {
                    root -> balance = RH;
                    ltree -> balance = EH;
                }
                rtree -> balance = EH;
                root -> pLeft = rotateLeft(ltree);
                root = rotateRight(root);
            }
            else
            {
                if (ltree -> balance != EH)
                {
                    root -> balance = EH;
                    ltree -> balance = EH;
                }
                else
                {
                    root -> balance = LH;
                    ltree -> balance = RH;
                    shorter = false;
                }
                root=rotateRight(root);
            }
        }
    return root;
}
Node* deleteright(Node* root, bool &shorter)
{
    if (root -> balance == LH)
    {
        root -> balance = EH;
    }
    else if (root -> balance == EH)
    {
        root -> balance = RH; 
        shorter = false;
    }
    else
    {
        Node* rtree = root -> pRight;
        if (rtree -> balance == LH)
        {
            Node* ltree = rtree -> pLeft;
            if (ltree -> balance == LH)
            {
                rtree -> balance = RH;
                root -> balance = EH;
            }
            else if (ltree -> balance == EH)
            {
                root -> balance = EH; // sua here LH
                rtree -> balance = EH;
            }
            else
            {
                root -> balance = LH;
                rtree -> balance = EH;
            }
                ltree -> balance = EH;
                root -> pRight = rotateRight(rtree);
                root = rotateLeft(root);
        }
        else 
        {
            if (rtree -> balance != EH)
            {
                root -> balance = EH;
                rtree -> balance = EH;
            }
            else
            {
                root -> balance = RH;
                rtree -> balance = LH;
                shorter = false;
            }
            root = rotateLeft(root);
        }
    }
    return root;
}
    Node* AVLDelete(Node* root, int value, bool &shorter, bool &success, int ID, bool check)
    {
        if (root == NULL)
        {
            shorter = false;
            success = false;
            return NULL;
        }
        if (value < root -> data)
        {
            root -> pLeft = AVLDelete(root -> pLeft, value, shorter, success, ID, check);
            if (shorter) 
            {
                root = deleteright(root, shorter);
            }
        }
        else if (value > root->data)
        {
            root -> pRight = AVLDelete(root -> pRight, value, shorter, success, ID, check);
            if (shorter) 
            {
                root = deleteleft(root, shorter);
            }
        }
        else
        {
            Node* deleteNode = root;
            if (check == false)
                {
                    string namedelete = deleteNode -> Name;
                    numElements--;
                    arrayIDrelateResult[ID] = -1;
                    isSeated[deleteNode -> ID] = false;
                    LFCO.deletefollowName(namedelete);
                    removeElementFromQueue(FIFO, namedelete);
                    deleteLRCO(LRCO, namedelete);
                    check = true;
                }
            if (root -> pRight == NULL)
            {
                Node* newRoot = root -> pLeft;
                success = true;
                shorter = true;
                delete deleteNode;
                return newRoot;
            }
            else if (root -> pLeft == NULL)
            {
                Node* newRoot = root -> pRight;
                success = true;
                shorter = true;
                delete deleteNode;
                return newRoot;
            }
            else
            {
                Node* exchPtr = root -> pRight;
                while(exchPtr -> pLeft != NULL)
                {
                    exchPtr = exchPtr -> pLeft;
                }  
                root -> ID = exchPtr -> ID;
                root -> data = exchPtr -> data;
                root -> Name = exchPtr -> Name;
                root -> NumofOrder = exchPtr -> NumofOrder;
                root -> pRight=AVLDelete(root -> pRight, exchPtr->data, shorter, success, ID, check);
                if (shorter)
                {
                    root = deleteleft(root, shorter);
                }
            }
        }
        return root;
    }
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    void insert(const int &value, int ID, string Name)
    {
        insertLRCO(LRCO,Name);
        if (SolveDuplicate(value, Name) == true) return;
        bool taller=false;
        bool forChecking = false;
        if(isSeated[ID] == true)
        {
            for (int i = ID + 1; i <= MAXSIZE; i++)
            {
                if(isSeated[i] == false)
                {
                    ID = i;
                    forChecking = true;
                    break;
                }
            }
            if (forChecking == false)
            {
                for (int i = 1; i < ID; i++)
                {
                    if(isSeated[i] == false)
                    {
                        ID = i;
                        break;
                    }
                }
            }
            
        }
        arrayIDrelateResult[ID] = value;
        isSeated[ID] = true;
        Customer cus;
        cus.Name = Name;
        cus.ID = ID;
        cus.Result = OrderEntry;
        cus.NumsofOrder = 1;
        LFCO.push(cus);
        FIFO.push(Name);
        root=insertAVL(root,value,taller,Name,ID);
        numElements++;
        
    }
    void remove(const int &ID)
    {
        bool shorter = false;
        bool success = false;
        int value = arrayIDrelateResult[ID];
        root=AVLDelete(root, value, shorter, success, ID, false);
    }
class Node
{
    private:
    int data;
    int ID;
    string Name;
    int NumofOrder;
    Node *pLeft, *pRight;
    BalanceValue balance;
    friend class AVLTree;
    public:
    Node(int value) : data(value), ID(-1), Name(""), NumofOrder(1), pLeft(NULL), pRight(NULL), balance(EH) {}
    ~Node() {}
};
};
HashTable hashtable;
AVLTree avl;
void DoingREG(string Infor)
{
	string Name = Infor.substr(Infor.find(' ') + 1);
	int size = 0;
    int asciiArray[256] = {0};
    string EncodeHuffman[256] = {""};
    int sizeName = Name.size();
    string Encode = "";
    if (sizeName != 1)
    {
        for (int i = 0; i < sizeName; i++)
        {
            int position = int(Name[i]);
            if (asciiArray[position] == 0) size++;
            asciiArray[position]++;
        }
        HuffmanCodes(asciiArray, size, EncodeHuffman);
        for (int i = 0; i < sizeName; i++)
        {
            Encode += EncodeHuffman[int(Name[i])];
        }
        if (Encode.size() > 15)
        {
            Encode = Encode.substr(Encode.size() - 15);
        }
    }
    else
    {
        Encode = "1";
    }
    int Result = convertbin2dec(Encode);
    int ID = Result % MAXSIZE + 1;
    if (Result % 2 != 0) // khu vuc 1
    {
        if (hashtable.getnumElements() == MAXSIZE / 2)
        {
            int idCheck1 = hashtable.IDfollowName(Name);
            int idCheck2 = avl.searchIDfollowName(Name);
            if (avl.getnumElements() != MAXSIZE / 2)
            {
                avl.insert(Result, ID, Name);
            }
            else if(avl.getnumElements() == MAXSIZE / 2 && (idCheck1 != -1 || idCheck2 != -1))
            {
                if (idCheck1 != -1) hashtable.insert(ID, Result, Name);
                if (idCheck2 != -1) avl.insert(Result, ID, Name);
            }
            else
            {
                int OPT = Result % 3;
                if (OPT == 0)
                {
                    string Namedelete = FIFO.front();
                    FIFO.pop();
                    deleteLRCO(LRCO, Namedelete);
                    LFCO.deletefollowName(Namedelete);
                    int IDdeleteHashTable = hashtable.IDfollowName(Namedelete);
                    if (IDdeleteHashTable != -1)
                    {
                        hashtable.remove(IDdeleteHashTable);
                        hashtable.insert(ID, Result, Name);
                    }
                    else
                    {
                        int IDdeleteAVL = avl.searchIDfollowName(Namedelete);
                        if (IDdeleteAVL != -1)
                        {
                            avl.remove(IDdeleteAVL);
                            avl.insert(Result, ID, Name);
                        }
                    }
                }
                else if (OPT == 1)
                {
                    string Namedelete = LRCO[0];
                    deleteLRCO(LRCO, Namedelete);
                    LFCO.deletefollowName(Namedelete);
                    removeElementFromQueue(FIFO, Namedelete);
                    int IDdeleteHashTable = hashtable.IDfollowName(Namedelete);
                    if (IDdeleteHashTable != -1)
                    {
                        hashtable.remove(IDdeleteHashTable);
                        hashtable.insert(ID, Result, Name);
                    }
                    else
                    {
                        int IDdeleteAVL = avl.searchIDfollowName(Namedelete);
                        if (IDdeleteAVL != -1)
                        {
                            avl.remove(IDdeleteAVL);
                            avl.insert(Result, ID, Name);
                        }
                    }
                }
                else
                {
                    string Namedelete = LFCO.pop();
                    removeElementFromQueue(FIFO, Namedelete);
                    deleteLRCO(LRCO, Namedelete);
                    int IDdeleteHashTable = hashtable.IDfollowName(Namedelete);
                    if (IDdeleteHashTable != -1)
                    {
                        hashtable.remove(IDdeleteHashTable);
                        hashtable.insert(ID, Result, Name);
                    }
                    else
                    {
                        int IDdeleteAVL = avl.searchIDfollowName(Namedelete);
                        if (IDdeleteAVL != -1)
                        {
                            avl.remove(IDdeleteAVL);
                            avl.insert(Result, ID, Name);
                        }
                    }
                }
            }
        }
        else hashtable.insert(ID, Result, Name);
    }
    else // khu vuc 2
    {
        if (avl.getnumElements() == MAXSIZE / 2)
        {
            int idCheck1 = hashtable.IDfollowName(Name);
            int idCheck2 = avl.searchIDfollowName(Name);
            if (hashtable.getnumElements() != MAXSIZE / 2)
            {
                hashtable.insert(ID, Result, Name);
            }
            else if(avl.getnumElements() == MAXSIZE / 2 && (idCheck1 != -1 || idCheck2 != -1))
            {
                if (idCheck1 != -1) hashtable.insert(ID, Result, Name);
                if (idCheck2 != -1) avl.insert(Result, ID, Name);
            }
            else// hang cho
            {
                int OPT = Result % 3;
                if (OPT == 0)
                {
                    string Namedelete = FIFO.front();
                    FIFO.pop();
                    deleteLRCO(LRCO, Namedelete);
                    LFCO.deletefollowName(Namedelete);
                    int IDdeleteHashTable = hashtable.IDfollowName(Namedelete);
                    if (IDdeleteHashTable != -1)
                    {
                        hashtable.remove(IDdeleteHashTable);
                        hashtable.insert(ID, Result, Name);
                    }
                    else
                    {
                        int IDdeleteAVL = avl.searchIDfollowName(Namedelete);
                        if (IDdeleteAVL != -1)
                        {
                            avl.remove(IDdeleteAVL);
                            avl.insert(Result, ID, Name);
                        }
                    }
                }
                else if (OPT == 1)
                {
                    string Namedelete = LRCO[0];
                    deleteLRCO(LRCO, Namedelete);
                    LFCO.deletefollowName(Namedelete);
                    removeElementFromQueue(FIFO, Namedelete);
                    int IDdeleteHashTable = hashtable.IDfollowName(Namedelete);
                    if (IDdeleteHashTable != -1)
                    {
                        hashtable.remove(IDdeleteHashTable);
                        hashtable.insert(ID, Result, Name);
                    }
                    else
                    {
                        int IDdeleteAVL = avl.searchIDfollowName(Namedelete);
                        if (IDdeleteAVL != -1)
                        {
                            avl.remove(IDdeleteAVL);
                            avl.insert(Result, ID, Name);
                        }
                    }
                }
                else
                {
                    string Namedelete = LFCO.pop();
                    removeElementFromQueue(FIFO, Namedelete);
                    deleteLRCO(LRCO, Namedelete);
                    int IDdeleteHashTable = hashtable.IDfollowName(Namedelete);
                    if (IDdeleteHashTable != -1)
                    {
                        hashtable.remove(IDdeleteHashTable);
                        hashtable.insert(ID, Result, Name);
                    }
                    else
                    {
                        int IDdeleteAVL = avl.searchIDfollowName(Namedelete);
                        if (IDdeleteAVL != -1)
                        {
                            avl.remove(IDdeleteAVL);
                            avl.insert(Result, ID, Name);
                        }
                    }
                }
            }
        }
        else avl.insert(Result, ID, Name);
    }
}
void DoingCLE (string Infor)
{
    string NUM = Infor.substr(Infor.find(' ') + 1);
    int Num = stoi(NUM);
    if (Num < 1)
    {
        hashtable.removeALL();
    }
    else if (Num > MAXSIZE)
    {
        avl.deleteTree();
    }
    else
    {
        avl.remove(Num);
        hashtable.remove(Num);
    }
}
void DoingPrintHT()
{
    hashtable.print();
}
void DoingPrintAVL()
{
    avl.printAVL();
}
void DoingPrintMH()
{
    LFCO.printPreorder(0);
}
void simulate(string filename)
{
    for (int i = 1; i <= MAXSIZE; i++)
    {
        isSeated[i] = false;
        arrayIDrelateResult[i] = -1;
    } 
	ifstream file;
	file.open(filename);
	string x;
	while(getline(file, x))
	{
		if (x.substr(0, x.find(' ')) == "REG" && isValidREG(x)) DoingREG(x);
        if (x.substr(0, x.find(' ')) == "CLE" && isValidCLE(x)) DoingCLE(x);
        if (x == "PrintHT") DoingPrintHT();
        if (x == "PrintAVL") DoingPrintAVL();
        if (x == "PrintMH") DoingPrintMH();
	}
        avl.deleteTree();
}

#include <iostream>
#include <vector>
#include <map>
#include <string.h>

struct ListNode
{
    ListNode *prev = nullptr; // pointer to the previous element or `nullptr` for first element
    ListNode *next = nullptr; // pointer to the next element or `nullptr` for last element
    ListNode *rand = nullptr; // pointer to a random element of this list or `nullptr`
    std::string data;         // user data
};

class List
{
public:
    void Serialize(FILE *file);   // save list to file, `fopen(path, "wb")`
    void Deserialize(FILE *file); // read list from file, `fopen(path, "rb")`

    // methods for filling the list
    void AddHead(std::string nodeData, ListNode *randNode = nullptr); // push head
    void AddTail(std::string nodeData, ListNode *randNode = nullptr); // push tail
    void PrintList();
    ListNode *GetRandomNode(); // create pointer to a random element of this list or `nullptr`
    void CleanList();

private:
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int count = 0;
};

ListNode *List::GetRandomNode()
{
    if (count <= 0)
    {
        return nullptr;
    }
    int random = rand() % count + 1;
    auto r = head;
    while (random-- > 0)
    {
        r = r->next;
    }
    return r;
}

void List::AddHead(std::string nodeData, ListNode *randNode)
{
    ListNode *newHead = new ListNode{nullptr, head, randNode, nodeData};
    ListNode *oldHead = head;
    if (head != nullptr)
    {
        head->prev = newHead;
    }
    head = newHead;
    count++;
    if (oldHead == nullptr)
    {
        tail = head;
    }
}

void List::AddTail(std::string nodeData, ListNode *randNode)
{
    ListNode *newTail = new ListNode{tail, nullptr, randNode, nodeData};
    ListNode *oldTail = tail;
    if (tail != nullptr)
    {
        tail->next = newTail;
    }
    tail = newTail;
    count++;
    if (oldTail == nullptr)
    {
        head = tail;
    }
}

void List::PrintList()
{
    std::cout << "Head -> ";
    auto curNode = head;
    while (curNode != nullptr)
    {
        std::cout << "\n Data: \'" << curNode->data
                  << "\' CurrentList: " << curNode
                  << " PrevList: " << curNode->prev
                  << " NextList: " << curNode->next
                  << " RandList: " << curNode->rand;
        curNode = curNode->next;
    }
    std::cout << "\n <- Tail" << std::endl;
}

void List::Serialize(FILE *file)
{
    if (!file)
    {
        return;
    }
    if (!head || !tail || count <= 0)
    {
        fprintf(file, "%i\n", 0);
        return;
    }
    fprintf(file, "%i\n", count);
    auto node = head;
    std::map<std::string, int> mapRandomNodes;
    int ind = 0;
    while (node != nullptr)
    {
        mapRandomNodes[reinterpret_cast<const char *>(&node)] = ind++;
        fprintf(file, "%s\n", node->data.c_str());
        node = node->next;
    }
    node = head;
    while (node != nullptr)
    {
        auto randNode = mapRandomNodes.find(reinterpret_cast<const char *>(&node->rand));
        int randIndex = -1;
        if (randNode != mapRandomNodes.end())
        {
            randIndex = randNode->second;
        }
        fprintf(file, "%i\n", randIndex);
        node = node->next;
    }
}

void List::CleanList()
{
    while (head != nullptr)
    {
        auto temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

void List::Deserialize(FILE *file)
{
    if (!file)
    {
        return;
    }
    CleanList();
    char data[1000];
    int listCount = std::stoi(fgets(data, sizeof(data), file));
    if (listCount <= 0)
    {
        return;
    }
    std::vector<ListNode *> listNodes(listCount);
    for (auto i = 0; i < listCount; i++)
    {
        fgets(data, sizeof(data), file);
        data[strcspn(data, "\n")] = 0;
        AddTail(data);
        listNodes[i] = tail;
    }
    for (auto i = 0; i < listCount; i++)
    {
        auto randNum = std::stoi(fgets(data, sizeof(data), file));
        if (randNum < 0)
        {
            listNodes[i]->rand = nullptr;
        }
        else
        {
            listNodes[i]->rand = listNodes[randNum];
        }
    }
}

List *createTestList()
{
    srand(time(0));
    List *list = new List();
    list->AddHead("First line", list->GetRandomNode());
    list->AddHead("Second line", list->GetRandomNode());
    list->AddHead("Third line", list->GetRandomNode());
    list->AddTail("Add tail", list->GetRandomNode());
    list->AddTail("Last line", list->GetRandomNode());
    list->AddTail("Tail line", list->GetRandomNode());
    return list;
}

int main()
{
    /* Testing */
    List *list = createTestList();
    list->PrintList();

    FILE *fileWrite = fopen("testListSerialize.txt", "wb");
    list->Serialize(fileWrite);
    fclose(fileWrite);

    FILE *fileRead = fopen("testListSerialize.txt", "rb");
    List *readList = new List();
    readList->Deserialize(fileRead);
    readList->PrintList();
    fclose(fileWrite);
}
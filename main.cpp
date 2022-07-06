#include <iostream>
#include <string>


using namespace std;


struct Algorithm
{
private:
    
    string name;
    string complexity;
    bool benefit;
    
public:
    
    Algorithm()
    {
        name = "";
        complexity = "";
        benefit = false;
    }
    
    Algorithm(string name, string complexity, bool benefit)
    {
        this->name = name;
        this->complexity = complexity;
        this->benefit = benefit;
    }
    
    
    string getName() { return name; }
    string getComplexity() { return complexity; }
    bool getBenefit() { return benefit; }
    
    void setName(string name) { this->name = name; }
    void setComplexity(string complexity) { this->complexity = complexity; }
    void setBenefit(bool benefit) { this->benefit = benefit; }
    
    friend ostream& operator<< (ostream &out, Algorithm &algorithm);
};


struct DynamicArray
{
private:
    
    int size = 0;
    int capacity = 1;
    const int k = 2;
    Algorithm *array = new Algorithm[capacity];
    Algorithm none;
    
public:
    
    ~DynamicArray()
    {
        delete [] array;
    }
    
    void realloc()
    {
        capacity *= k;
        Algorithm *newArray = new Algorithm[capacity];
        
        for (int i = 0; i < size; i++)
        {
            newArray[i] = array[i];
        }
        
        delete[] array;
        array = newArray;
    }
    
    
    void push_back(Algorithm element)
    {
        if(size == capacity)
        {
            realloc();
        }
        
        array[size++] = element;
    }
    
    
    Algorithm pop_back()
    {
        if (size)
        {
            Algorithm object = array[size - 1];
            size--;
            return object;
        }
        
        cout << "Array is empty!!" << endl;
        
        return none;
    }
    
    
    void push_front(Algorithm element)
    {
        if(size == capacity)
        {
            realloc();
        }
        
        for (int i = size; i > 0; i--)
        {
            array[i] = array[i - 1];
        }
        
        array[0] = element;
        size++;
    }
    
    
    Algorithm pop_front()
    {
        if (size)
        {
            Algorithm object = array[0];
            
            for (int i = 0; i < size - 1; i++)
            {
                array[i] = array[i + 1];
            }
            
            size--;
            
            return object;
        }
        
        cout << "Array is empty!!" << endl;
        
        return none;
    }
    
    
    Algorithm get(int index)
    {
        if ( !size && ( index >= size ) )
        {
            return none;
        }
        
        return array[index];
    }
    
    
    int sizeOfArray()
    {
        return size;
    }
    
    
    void print()
    {
        if (!size)
        {
            cout << "Array is empty!!" << endl;
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                cout << array[i] << endl;
            }
        }
    }
};


struct Node
{
    Algorithm data;
    Node *next;
};


struct LinkedList
{
    Node *head;
    Algorithm none;
    
    
    LinkedList()
    {
        head = nullptr;
    }
    
    
    ~LinkedList()
    {
        Node *eraser = head;
        
        while(!eraser)
        {
            eraser = head;
            head = head->next;
            delete eraser;
        }
    }
    
    
    void push_front(Algorithm element)
    {
        Node *newNode = new Node;
        
        newNode->data = element;
        newNode->next = head;
        
        head = newNode;
    }
    
    
    void push_back(Algorithm element)
    {
        Node *newNode = new Node;
        
        if (!head)
        {
            head = newNode;
            newNode->data = element;
            newNode->next = nullptr;
        }
        else
        {
            Node *last = head;
            while (last->next)
            {
                last = last->next;
            }
            
            last->next = newNode;
            newNode->data = element;
            newNode->next = nullptr;
        }
    }
    
    
    Algorithm get(int position)
    {
        if ( !head && ( position < size() ) )
        {
            cout << "List is empty!!!" << endl;
            return none;
        }
        
        int counter = 0;
        Node *currentElement = new Node;
        currentElement = head;
        
        while (counter != position)
        {
            currentElement = currentElement->next;
            counter++;
        }
        
        return currentElement->data;
    }
    
    
    Algorithm pop_front()
    {
        if (!head)
        {
            cout << "List is empty!!!" << endl;
            return none;
        }
        
        Algorithm object = head->data;
        Node *tempNode = head;
        head = head->next;
        delete tempNode;
        return object;
    }
    
    
    Algorithm pop_back()
    {
        Algorithm object = head->data;
        
        if (!head)
        {
            cout << "List is empty!!!" << endl;
            return none;
        }
        else if (head->next != nullptr)
        {
            Node *currentNode = head;
            Node *prevNode = currentNode;
            while (currentNode->next != nullptr)
            {
                prevNode = currentNode;
                currentNode = currentNode->next;
            }
            prevNode->next = nullptr;
            object = currentNode->data;
            delete currentNode;
            return object;
        }
        
        head = nullptr;
        delete head;
        return object;
    }
    
    
    int size()
    {
        int counter = 0;
        
        Node *tempNode = head;
        while (tempNode != nullptr)
        {
            tempNode = tempNode->next;
            counter++;
        }
        
        return counter;
    }
    
    
    void print()
    {
        if (!head)
        {
            cout << "List is empty!!!" << endl;
        }
        else
        {
            Node *currentNode = head;
            while (currentNode != nullptr)
            {
                cout << currentNode->data << endl;
                currentNode = currentNode->next;
            }
        }
    }
};


Algorithm createAlgorithm()
{
    Algorithm a;
    return a;
}


ostream& operator<< (ostream &out, Algorithm &algorithm)
{
    out << "Name: " << algorithm.getName() << endl
        << "Complexity: " << algorithm.getComplexity() << endl
        << "Benefit: " << algorithm.getBenefit() << endl;
    
    return out;
}


int main()
{
    srand( (unsigned int)time(NULL) );
    
    clock_t startDynamicArray = clock();
    cout << "-------DYNAMIC-ARRAY--------" << endl;
    DynamicArray array;
    
    
    clock_t start1 = clock();
    for (int i = 0; i < 50000; i++)
    {
        array.push_back( createAlgorithm() );
    }
    clock_t end1 = clock();
    double seconds1 = (double(end1 - start1)) / CLOCKS_PER_SEC;
    cout << "Time1: " << seconds1 << endl;
    
    
    clock_t start2 = clock();
    for (int i = 0; i < 10000; i++)
    {
        array.push_front( createAlgorithm() );
    }
    clock_t end2 = clock();
    double seconds2 = (double(end2 - start2)) / CLOCKS_PER_SEC;
    cout << "Time2: " << seconds2 << endl;
    
    
    clock_t start3 = clock();
    for (int i = 0; i < 20000; i++)
    {
        array.get( rand() % (array.sizeOfArray() - 1) );
    }
    clock_t end3 = clock();
    double seconds3 = (double(end3 - start3)) / CLOCKS_PER_SEC;
    cout << "Time3: " << seconds3 << endl;
 
    
    clock_t start4 = clock();
    for (int i = 0; i < 5000; i++)
    {
        array.pop_front();
    }
    clock_t end4 = clock();
    double seconds4 = (double(end4 - start4)) / CLOCKS_PER_SEC;
    cout << "Time4: " << seconds4 << endl;
    
    
    clock_t start5 = clock();
    for (int i = 0; i < 5000; i++)
    {
        array.pop_back();
    }
    clock_t end5 = clock();
    double seconds5 = (double(end5 - start5)) / CLOCKS_PER_SEC;
    cout << "Time5: " << seconds5 << endl;
    
    
    clock_t endDynamicArray = clock();
    double secondsDynamicArray = (double(endDynamicArray - startDynamicArray)) / CLOCKS_PER_SEC;
    cout << "TimeDynamicArray: " << secondsDynamicArray << endl;
    
    
    clock_t startLinkedList = clock();
    cout << "\n\n--------LINKED-LIST---------" << endl;
    LinkedList list;
    
    
    clock_t start6 = clock();
    for (int i = 0; i < 50000; i++)
    {
        list.push_back( createAlgorithm() );
    }
    clock_t end6 = clock();
    double seconds6 = (double(end6 - start6)) / CLOCKS_PER_SEC;
    cout << "Time6: " << seconds6 << endl;
    
    
    clock_t start7 = clock();
    for (int i = 0; i < 10000; i++)
    {
        list.push_front( createAlgorithm() );
    }
    clock_t end7 = clock();
    double seconds7 = (double(end7 - start7)) / CLOCKS_PER_SEC;
    cout << "Time7: " << seconds7 << endl;
    
    
    clock_t start8 = clock();
    for (int i = 0; i < 20000; i++)
    {
        list.get( rand() % (array.sizeOfArray() - 1) );
    }
    clock_t end8 = clock();
    double seconds8 = (double(end8 - start8)) / CLOCKS_PER_SEC;
    cout << "Time8: " << seconds8 << endl;
    
    
    clock_t start9 = clock();
    for (int i = 0; i < 5000; i++)
    {
        list.pop_front();
    }
    clock_t end9 = clock();
    double seconds9 = (double(end9 - start9)) / CLOCKS_PER_SEC;
    cout << "Time9: " << seconds9 << endl;
    
    
    clock_t start10 = clock();
    for (int i = 0; i < 5000; i++)
    {
        list.pop_back();
    }
    clock_t end10 = clock();
    double seconds10 = (double(end10 - start10)) / CLOCKS_PER_SEC;
    cout << "Time10: " << seconds10 << endl;
    
    
    clock_t endLinkedList = clock();
    double secondsLinkedList = (double(endLinkedList - startLinkedList)) / CLOCKS_PER_SEC;
    cout << "TimeLinkedList: " << secondsLinkedList << endl;
}

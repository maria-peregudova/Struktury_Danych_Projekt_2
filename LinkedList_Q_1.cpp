#include <iostream>

template <typename T, typename Prio = int>
class LinkedList_Q{
    struct List_Node{
        T element;
        Prio priority;
        List_Node* next = nullptr;

        List_Node(T el, Prio p) : element(el), priority(p){}
    };

    List_Node* head = nullptr;
    size_t count = 0;

public:
    LinkedList_Q() = default;

    ~LinkedList_Q(){
        while(head){
            List_Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(T element, Prio priority){
        List_Node* newList_Node = new List_Node(element, priority);

        if(!head || priority > head->priority){
            newList_Node->next = head;
            head = newList_Node;
        }
        else{
            List_Node* curr = head;

            while(curr->next && curr->next->priority >= priority){
                curr = curr->next;
            }

            newList_Node->next = curr->next;
            curr->next = newList_Node;
        }

        count++;
    }

    void remove(){
        if(!head){
            return;
        }
        List_Node* temp = head;
        head = head->next;

        delete temp;
        count--;
    }

    size_t size() const{
        return count;
    }

    T peek() const{
        if(!head){
            std::cout<<"ERROR: Pusta kolejka"<<std::endl;
        }
        return head->element;
    }

    void modify(const T& element, Prio newPriority){

        List_Node* curr = head;
        List_Node* prev = nullptr;

        while(curr){
            if(curr->element == element){
                break;
            }
            prev = curr;
            curr = curr->next;
        }

        if(!curr){
            return;
        }
        if(prev){
            prev->next = curr->next;
        }
        else{
            head = curr->next;
        }
        count--;
        T el = curr->element;
        delete curr;
        add(el, newPriority);
    }
};

int main(){
    LinkedList_Q<std::string, int> pq;

    pq.add("Zmywanie", 2);
    pq.add("Praca", 10);
    pq.add("Drzemka", 8);
    pq.add("Zmywanie", 5);

    std::cout<<"Następne zadanie: "<<pq.peek()<<std::endl;
    pq.remove();
    std::cout<<"Następne po usunięciu: "<<pq.peek()<<std::endl;
    pq.modify("Zmywanie", 15);
    std::cout<<"Po zmianie priorytetu: "<<pq.peek()<<std::endl;

    return 0;
}

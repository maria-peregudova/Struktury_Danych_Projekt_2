#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T, typename Prio = int>
class Treap_Q{
    struct Treap_Node{
        T element;
        Prio priority;
        int weight;
        Treap_Node *l = nullptr, *r = nullptr;

        Treap_Node(T el, Prio p) : element(el), priority(p), weight(rand()){}
    };

    Treap_Node* root = nullptr;
    size_t count = 0;

    void split(Treap_Node* t, Prio key, Treap_Node*& l, Treap_Node*& r){
        if(!t){
            l = r = nullptr;
            return;
        }
        if(t->priority <= key){
            split(t->r, key, t->r, r);
            l = t;
        }
        else{
            split(t->l, key, l, t->l);
            r = t;
        }
    }

    void merge(Treap_Node*& t, Treap_Node* l, Treap_Node* r){
        if((!l) || (!r)){
            t = l ? l : r;
            return;
        }
        if(l->weight > r->weight){
            merge(l->r, l->r, r);
            t = l;
        }
        else{
            merge(r->l, l, r->l);
            t = r;
        }
    }

    void erase(Treap_Node*& t, Prio key, const T& el, bool& removed){
        if(!t || removed){
            return; 
        }
        if(t->priority == key && t->element == el){
            Treap_Node* temp = t;
            merge(t, t->l, t->r);
            delete temp;
            removed = true;
            return;
        }

        erase(t->l, key, el, removed);
        erase(t->r, key, el, removed);
    }

    bool findFirst(Treap_Node* t, const T& element, Prio& foundPriority){
        if(!t){
            return false;
        }
        if(t->element == element){
            foundPriority = t->priority;
            return true;
        }

        return findFirst(t->l, element, foundPriority) ||
               findFirst(t->r, element, foundPriority);
    }

    void clear(Treap_Node* t){
        if(!t){
            return;
        }
        clear(t->l);
        clear(t->r);
        delete t;
    }

public:
    Treap_Q(){
        srand(time(0));
    }

    ~Treap_Q(){
        clear(root);
    }

    void add(T element, Prio priority){
        Treap_Node *l, *r;
        Treap_Node* newNode = new Treap_Node(element, priority);
        split(root, priority, l, r);
        merge(l, l, newNode);
        merge(root, l, r);
        count++;
    }

    void remove(){
        if(!root){
            return;
        }
        Treap_Node* curr = root;

        while(curr->r){
            curr = curr->r;
        }
        bool removed = false;

        erase(root, curr->priority, curr->element, removed);

        if(removed){
            count--;
        }
    }

    size_t size() const{
        return count;
    }

    T peek() const{
        if(!root){
            std::cout<<"ERROR: Pusta kolejka"<<std::endl;
        }
        Treap_Node* curr = root;

        while(curr->r)
            curr = curr->r;

        return curr->element;
    }

    void modify(const T& element, Prio newPriority){
        Prio oldPriority;

        if(!findFirst(root, element, oldPriority)){
            return;
        }

        bool removed = false;

        erase(root, oldPriority, element, removed);

        if(removed){
            count--;
            add(element, newPriority);
        }
    }
};

int main(){
    Treap_Q<std::string, int> pq;

    pq.add("zmywanie", 2);
    pq.add("praca", 10);
    pq.add("drzemka", 8);
    pq.add("zmywanie", 5);

    std::cout<<"Następne zadanie: "<<pq.peek()<<std::endl;
    pq.remove();
    std::cout<<"Następne po usunięciu: "<<pq.peek()<<std::endl;
    pq.modify("zmywanie", 15);

    std::cout<<"Po zmianie priorytetu: "<<pq.peek()<<std::endl;

    return 0;
}

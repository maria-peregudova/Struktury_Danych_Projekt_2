#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "Heap_Q.hpp" 
#include "LinkedList_Q.hpp"
#include "Treap_Q.hpp"

using namespace std;
using namespace std::chrono;

// Przypadek Average Case
void createHeapCopies(BinaryHeap<int>** arr, int numCopies, int size) {
    for (int i = 0; i < numCopies; ++i) {
        arr[i] = new BinaryHeap<int>(size + 1);
        for (int j = 0; j < size; ++j) arr[i]->add(j, rand() % 1000); 
    }
}

void createLLCopies(LinkedList_Q<int, int>** arr, int numCopies, int size) {
    for (int i = 0; i < numCopies; ++i) {
        arr[i] = new LinkedList_Q<int, int>();
        for (int j = 0; j < size; ++j) arr[i]->add(j, rand() % 1000); 
    }
}

void createTreapCopies(Treap_Q<int, int>** arr, int numCopies, int size) {
    for (int i = 0; i < numCopies; ++i) {
        arr[i] = new Treap_Q<int, int>();
        for (int j = 0; j < size; ++j) arr[i]->add(j, rand() % 1000);
    }
}

// Przypadek Best Case
// void createHeapCopies(BinaryHeap<int>** arr, int numCopies, int size) {
//     for (int i = 0; i < numCopies; ++i) {
//         arr[i] = new BinaryHeap<int>(size + 1);
//         for (int j = 0; j < size; ++j) arr[i]->add(j, j); // Rosnące priorytety
//     }
// }

// void createLLCopies(LinkedList_Q<int, int>** arr, int numCopies, int size) {
//     for (int i = 0; i < numCopies; ++i) {
//         arr[i] = new LinkedList_Q<int, int>();
//         for (int j = 0; j < size; ++j) arr[i]->add(j, j); // Rosnące priorytety
//     }
// }

// void createTreapCopies(Treap_Q<int, int>** arr, int numCopies, int size) {
//     for (int i = 0; i < numCopies; ++i) {
//         arr[i] = new Treap_Q<int, int>();
//         for (int j = 0; j < size; ++j) arr[i]->add(j, j); // Rosnące priorytety
//     }
// }

// Przypadek Worst Case
// void createHeapCopies(BinaryHeap<int>** arr, int numCopies, int size) {
//     for (int i = 0; i < numCopies; ++i) {
//         arr[i] = new BinaryHeap<int>(size + 1);
//         for (int j = 0; j < size; ++j) arr[i]->add(j, size - j); // Malejące priorytety
//     }
// }

// void createLLCopies(LinkedList_Q<int, int>** arr, int numCopies, int size) {
//     for (int i = 0; i < numCopies; ++i) {
//         arr[i] = new LinkedList_Q<int, int>();
//         for (int j = 0; j < size; ++j) arr[i]->add(j, size - j); // Malejące priorytety
//     }
// }

// void createTreapCopies(Treap_Q<int, int>** arr, int numCopies, int size) {
//     for (int i = 0; i < numCopies; ++i) {
//         arr[i] = new Treap_Q<int, int>();
//         for (int j = 0; j < size; ++j) arr[i]->add(j, size - j); // Malejące priorytety
//     }
// }

template <typename T>
void deleteCopies(T** copiesArr, int numCopies) {
    for (int i = 0; i < numCopies; ++i) delete copiesArr[i];
}

int main() {
    srand(time(NULL)); 
    int numCopies = 50; 

    ofstream file("results_priority_queue_worst_case.csv");
    file << "Size;Heap_Add;LL_Add;Treap_Add;"
         << "Heap_Remove;LL_Remove;Treap_Remove;"
         << "Heap_Size;LL_Size;Treap_Size;"
         << "Heap_Peek;LL_Peek;Treap_Peek;"
         << "Heap_Modify;LL_Modify;Treap_Modify\n";

    vector<int> tableSize = {1000, 2000, 5000, 10000, 20000, 50000};
    
    BinaryHeap<int>** heap_copies = new BinaryHeap<int>*[numCopies]; 
    LinkedList_Q<int, int>** ll_copies = new LinkedList_Q<int, int>*[numCopies];
    Treap_Q<int, int>** treap_copies = new Treap_Q<int, int>*[numCopies];

    size_t operationSum = 0; 
    
    for (int size : tableSize) {
        long long h_add, l_add, t_add;
        long long h_rem, l_rem, t_rem;
        long long h_sz, l_sz, t_sz;
        long long h_pk, l_pk, t_pk;
        long long h_mod, l_mod, t_mod;
        
        auto start = high_resolution_clock::now();
        auto end = high_resolution_clock::now();
        int randPrio, targetData, optPrio, pesPrio;

        // 1. ADD
        createHeapCopies(heap_copies, numCopies, size);
        randPrio = rand() % 1000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            heap_copies[i]->add(-1, randPrio);
        }
        end = high_resolution_clock::now();
        h_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(heap_copies, numCopies);

        createLLCopies(ll_copies, numCopies, size);
        randPrio = rand() % 1000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            ll_copies[i]->add(-1, randPrio);
        }
        end = high_resolution_clock::now();
        l_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(ll_copies, numCopies);

        createTreapCopies(treap_copies, numCopies, size);
        randPrio = rand() % 1000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            treap_copies[i]->add(-1, randPrio);
        }
        end = high_resolution_clock::now();
        t_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(treap_copies, numCopies);

        // 1. ADD - Przypadek Best Case
        // createHeapCopies(heap_copies, numCopies, size);
        // optPrio = size + 10;
        // start = high_resolution_clock::now();
        // for (int i = 0; i < numCopies; ++i) {
        //     heap_copies[i]->add(-1, optPrio);
        // }
        // end = high_resolution_clock::now();
        // h_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        // deleteCopies(heap_copies, numCopies);

        // createLLCopies(ll_copies, numCopies, size);
        // optPrio = size + 10;
        // start = high_resolution_clock::now();
        // for (int i = 0; i < numCopies; ++i) {
        //     ll_copies[i]->add(-1, optPrio);
        // }
        // end = high_resolution_clock::now();
        // l_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        // deleteCopies(ll_copies, numCopies);

        // createTreapCopies(treap_copies, numCopies, size);
        // optPrio = size + 10;
        // start = high_resolution_clock::now();
        // for (int i = 0; i < numCopies; ++i) {
        //     treap_copies[i]->add(-1, optPrio);
        // }
        // end = high_resolution_clock::now();
        // t_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        // deleteCopies(treap_copies, numCopies);


        // 1. ADD - Przypadek Worst Case
        // createHeapCopies(heap_copies, numCopies, size);
        // pesPrio = -1;
        // start = high_resolution_clock::now();
        // for (int i = 0; i < numCopies; ++i) {
        //     heap_copies[i]->add(-1, pesPrio);
        // }
        // end = high_resolution_clock::now();
        // h_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        // deleteCopies(heap_copies, numCopies);

        // createLLCopies(ll_copies, numCopies, size);
        // pesPrio = -1;
        // start = high_resolution_clock::now();
        // for (int i = 0; i < numCopies; ++i) {
        //     ll_copies[i]->add(-1, pesPrio);
        // }
        // end = high_resolution_clock::now();
        // l_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        // deleteCopies(ll_copies, numCopies);

        // createTreapCopies(treap_copies, numCopies, size);
        // pesPrio = -1;
        // start = high_resolution_clock::now();
        // for (int i = 0; i < numCopies; ++i) {
        //     treap_copies[i]->add(-1, pesPrio);
        // }
        // end = high_resolution_clock::now();
        // t_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
        // deleteCopies(treap_copies, numCopies);

        // 2. REMOVE
        createHeapCopies(heap_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            heap_copies[i]->remove();
        }
        end = high_resolution_clock::now();
        h_rem = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(heap_copies, numCopies);

        createLLCopies(ll_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            ll_copies[i]->remove();
        }
        end = high_resolution_clock::now();
        l_rem = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(ll_copies, numCopies);

        createTreapCopies(treap_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            treap_copies[i]->remove();
        }
        end = high_resolution_clock::now();
        t_rem = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(treap_copies, numCopies);

        // 3. SIZE
        createHeapCopies(heap_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            operationSum += heap_copies[i]->getSize();
        }
        end = high_resolution_clock::now();
        h_sz = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(heap_copies, numCopies);

        createLLCopies(ll_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            operationSum += ll_copies[i]->size();
        }
        end = high_resolution_clock::now();
        l_sz = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(ll_copies, numCopies);

        createTreapCopies(treap_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            operationSum += treap_copies[i]->size();
        }
        end = high_resolution_clock::now();
        t_sz = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(treap_copies, numCopies);

        // 4. PEEK
        createHeapCopies(heap_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
          operationSum += heap_copies[i]->peek(); 
        }
        end = high_resolution_clock::now();
        h_pk = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(heap_copies, numCopies);

        createLLCopies(ll_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
          operationSum += ll_copies[i]->peek();
        }
        end = high_resolution_clock::now();
        l_pk = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(ll_copies, numCopies);

        createTreapCopies(treap_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
          operationSum += treap_copies[i]->peek();
        }
        end = high_resolution_clock::now();
        t_pk = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(treap_copies, numCopies);

        // 5. MODIFY
        createHeapCopies(heap_copies, numCopies, size);
        targetData = size / 2;
        randPrio = rand() % 1000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            heap_copies[i]->modifyPriority(targetData, randPrio);
        }
        end = high_resolution_clock::now();
        h_mod = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(heap_copies, numCopies);

        createLLCopies(ll_copies, numCopies, size);
        randPrio = rand() % 1000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            ll_copies[i]->modify(targetData, randPrio);
        }
        end = high_resolution_clock::now();
        l_mod = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(ll_copies, numCopies);

        createTreapCopies(treap_copies, numCopies, size);
        randPrio = rand() % 1000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            treap_copies[i]->modify(targetData, randPrio);
        }
        end = high_resolution_clock::now();
        t_mod = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(treap_copies, numCopies);

        file << size << ";" 
             << h_add << ";" << l_add << ";" << t_add << ";"
             << h_rem << ";" << l_rem << ";" << t_rem << ";"
             << h_sz << ";" << l_sz << ";" << t_sz << ";"
             << h_pk << ";" << l_pk << ";" << t_pk << ";"
             << h_mod << ";" << l_mod << ";" << t_mod << "\n";

        cout << "\nOperacje dla N = " << size << "\n";
        cout << string(68, '-') << "\n";
        cout << left << setw(20) << "Operacja" << setw(16) << "Kopiec [ns]" << setw(16) << "Lista [ns]" << setw(16) << "Treap [ns]" << "\n";
        cout << string(68, '-') << "\n";
        cout << left << setw(20) << "1. add"      << setw(16) << h_add << setw(16) << l_add << setw(16) << t_add << "\n";
        cout << left << setw(20) << "2. remove"   << setw(16) << h_rem << setw(16) << l_rem << setw(16) << t_rem << "\n";
        cout << left << setw(20) << "3. getSize"  << setw(16) << h_sz  << setw(16) << l_sz  << setw(16) << t_sz  << "\n";
        cout << left << setw(20) << "4. peek"     << setw(16) << h_pk  << setw(16) << l_pk  << setw(16) << t_pk  << "\n";
        cout << left << setw(20) << "5. modify"   << setw(16) << h_mod << setw(16) << l_mod << setw(16) << t_mod << "\n";
    }

    delete[] heap_copies;
    delete[] ll_copies;
    delete[] treap_copies;
    
    file.close(); 

    if (operationSum == 0) {
        cout << "Suma operacji: " << operationSum << "\n"; 
    }
    return 0;
}
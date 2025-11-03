#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Page Faults in LRU Implementation
 GeeksForGeeks Link: https://www.geeksforgeeks.org/operating-systems/page-faults-in-lru-implementation/

 Problem Statement:
 -----------------
 Given a sequence of pages in an array pages[] of length N and memory capacity C, 
 find the number of page faults using Least Recently Used (LRU) Algorithm.

 A page fault occurs when:
 - The requested page is not present in memory (cache miss)
 - We need to load the page from secondary storage to main memory

 LRU Policy:
 - When memory is full and a new page is needed, remove the Least Recently Used page
 - When a page is accessed, it becomes the Most Recently Used page

 Example 1:
 Input: pages = [1, 2, 1, 4, 2, 3, 5], capacity = 3
 Output: 5
 Explanation:
 - Page 1: Not in memory → Page Fault (1st) → Memory: [1]
 - Page 2: Not in memory → Page Fault (2nd) → Memory: [1, 2]  
 - Page 1: In memory → Hit → Memory: [2, 1] (1 moved to end)
 - Page 4: Not in memory → Page Fault (3rd) → Memory: [2, 1, 4]
 - Page 2: In memory → Hit → Memory: [1, 4, 2] (2 moved to end)
 - Page 3: Not in memory, memory full → Page Fault (4th) → Remove 1 (LRU) → Memory: [4, 2, 3]
 - Page 5: Not in memory, memory full → Page Fault (5th) → Remove 4 (LRU) → Memory: [2, 3, 5]

 Example 2:
 Input: pages = [2, 0, 1, 2, 4, 0, 5, 1, 4, 6, 4, 2, 1, 3, 0], capacity = 4
 Output: 10

 Constraints:
 - 1 <= N <= 1000
 - 1 <= C <= 100
 - 1 <= pages[i] <= 1000
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Array with Linear Search
 -----------------------------------------
 💡 Idea:
 Use a vector to simulate memory frames. For each page request, search linearly
 to check if page exists. Maintain LRU order by moving accessed pages to end.

 🧩 Algorithm:
 1. For each page in the sequence:
    - Search if page exists in memory (linear search)
    - If NOT found: Page Fault
      → If memory full, remove first element (LRU)
      → Add new page at end (MRU position)
    - If found: Page Hit
      → Remove page from current position
      → Add it at end (make it MRU)
 2. Count total page faults.

 ⏱ Time Complexity: O(N * C) - for each page, O(C) search and shift
 📦 Space Complexity: O(C) - memory frames vector
*/
int pageFaultsBruteForce(vector<int>& pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;
    
    cout << "=== Brute Force LRU Simulation ===\n";
    cout << "Format: Page X → [Status] → Memory State\n\n";
    
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        
        // Search for page in memory
        auto it = find(memory.begin(), memory.end(), page);
        
        if (it == memory.end()) {
            // Page Fault - page not in memory
            pageFaults++;
            cout << "Page " << page << " → PAGE FAULT ";
            
            if (memory.size() == capacity) {
                cout << "(remove " << memory[0] << " - LRU) ";
                memory.erase(memory.begin()); // Remove LRU (first element)
            }
            
            memory.push_back(page); // Add to end (MRU position)
            cout << "→ Memory: [";
        } else {
            // Page Hit - page found in memory
            cout << "Page " << page << " → HIT ";
            memory.erase(it); // Remove from current position
            memory.push_back(page); // Move to end (make it MRU)
            cout << "→ Memory: [";
        }
        
        // Print current memory state
        for (int j = 0; j < memory.size(); j++) {
            cout << memory[j];
            if (j < memory.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    
    return pageFaults;
}


/* 
==========================================
 Approach 2: Better - Hash Map + Deque
 -----------------------------------------
 💡 Idea:
 Use deque for O(1) front/back operations and hash set for O(1) lookup.
 Maintain order with deque, use hash set to check existence.

 🧩 Algorithm:
 1. Use deque to maintain page order (front = LRU, back = MRU)
 2. Use unordered_set for O(1) page existence check
 3. For each page:
    - If not in set: Page Fault
      → Remove front (LRU) if full, add to back and set
    - If in set: Page Hit
      → Remove from current position, add to back
 4. Count page faults.

 ⏱ Time Complexity: O(N * C) - deque removal in middle is O(C)
 📦 Space Complexity: O(C) - deque + hash set
*/
int pageFaultsBetter(vector<int>& pages, int capacity) {
    deque<int> memory;
    unordered_set<int> pageSet;
    int pageFaults = 0;
    
    cout << "=== Better Approach (Deque + HashSet) ===\n";
    
    for (int page : pages) {
        if (pageSet.find(page) == pageSet.end()) {
            // Page Fault
            pageFaults++;
            cout << "Page " << page << " → PAGE FAULT ";
            
            if (memory.size() == capacity) {
                int lruPage = memory.front();
                memory.pop_front();
                pageSet.erase(lruPage);
                cout << "(remove " << lruPage << ") ";
            }
            
            memory.push_back(page);
            pageSet.insert(page);
        } else {
            // Page Hit - move to back
            cout << "Page " << page << " → HIT ";
            memory.erase(find(memory.begin(), memory.end(), page));
            memory.push_back(page);
        }
        
        cout << "→ Memory: [";
        for (int i = 0; i < memory.size(); i++) {
            cout << memory[i];
            if (i < memory.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    
    return pageFaults;
}


/* 
==========================================
 Approach 3: Optimal - Hash Map + Doubly Linked List
 -----------------------------------------
 💡 Idea:
 Use hash map for O(1) lookup and custom doubly linked list for O(1) 
 insertion/deletion at any position. This gives true O(N) performance.

 🧩 Algorithm:
 1. Custom doubly linked list with dummy head/tail
 2. Hash map: page → node pointer for O(1) access
 3. For each page:
    - If not in map: Page Fault
      → Remove tail->prev (LRU) if full
      → Add new node after head (MRU)
    - If in map: Page Hit
      → Remove node from current position
      → Add at head (make MRU)

 ⏱ Time Complexity: O(N) - all operations are O(1)
 📦 Space Complexity: O(C) - hash map + linked list nodes
*/
class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int x) : data(x), next(nullptr), prev(nullptr) {}
};

class LRUCache {
private:
    Node* head;
    Node* tail;
    unordered_map<int, Node*> pageMap;
    int capacity;
    int size;
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }
    
    Node* removeTail() {
        Node* last = tail->prev;
        removeNode(last);
        return last;
    }
    
public:
    LRUCache(int cap) : capacity(cap), size(0) {
        head = new Node(-1);
        tail = new Node(-1);
        head->next = tail;
        tail->prev = head;
    }
    
    int pageFaultsOptimal(vector<int>& pages) {
        int pageFaults = 0;
        
        cout << "=== Optimal Approach (Custom Doubly Linked List) ===\n";
        
        for (int page : pages) {
            if (pageMap.find(page) == pageMap.end()) {
                // Page Fault
                pageFaults++;
                cout << "Page " << page << " → PAGE FAULT ";
                
                if (size == capacity) {
                    Node* lru = removeTail();
                    pageMap.erase(lru->data);
                    cout << "(remove " << lru->data << ") ";
                    delete lru;
                    size--;
                }
                
                Node* newNode = new Node(page);
                addToHead(newNode);
                pageMap[page] = newNode;
                size++;
            } else {
                // Page Hit
                cout << "Page " << page << " → HIT ";
                Node* node = pageMap[page];
                moveToHead(node);
            }
            
            // Print memory state (head->next to tail->prev)
            cout << "→ Memory: [";
            Node* curr = head->next;
            bool first = true;
            while (curr != tail) {
                if (!first) cout << ", ";
                cout << curr->data;
                curr = curr->next;
                first = false;
            }
            cout << "]\n";
        }
        
        return pageFaults;
    }
    
    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};


/* Helper function to calculate page faults with step-by-step explanation */
void explainPageFaults(vector<int>& pages, int capacity) {
    cout << "\n=== Detailed Page Fault Analysis ===\n";
    cout << "Pages: [";
    for (int i = 0; i < pages.size(); i++) {
        cout << pages[i];
        if (i < pages.size() - 1) cout << ", ";
    }
    cout << "], Capacity: " << capacity << "\n\n";
    
    vector<int> memory;
    int pageFaults = 0, pageHits = 0;
    
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto it = find(memory.begin(), memory.end(), page);
        
        cout << "Step " << (i+1) << ": Request page " << page << "\n";
        
        if (it == memory.end()) {
            // Page Fault
            pageFaults++;
            cout << "  → PAGE FAULT (page not in memory)\n";
            
            if (memory.size() == capacity) {
                cout << "  → Memory full, remove LRU page " << memory[0] << "\n";
                memory.erase(memory.begin());
            }
            
            memory.push_back(page);
            cout << "  → Add page " << page << " to memory\n";
        } else {
            // Page Hit
            pageHits++;
            cout << "  → PAGE HIT (page found in memory)\n";
            memory.erase(it);
            memory.push_back(page);
            cout << "  → Move page " << page << " to MRU position\n";
        }
        
        cout << "  → Current memory: [";
        for (int j = 0; j < memory.size(); j++) {
            cout << memory[j];
            if (j < memory.size() - 1) cout << ", ";
        }
        cout << "]\n\n";
    }
    
    cout << "Final Results:\n";
    cout << "Total Page Faults: " << pageFaults << "\n";
    cout << "Total Page Hits: " << pageHits << "\n";
    cout << "Hit Rate: " << (double)pageHits / pages.size() * 100 << "%\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{1, 2, 1, 4, 2, 3, 5}, 3},
        {{2, 0, 1, 2, 4, 0, 5, 1, 4, 6, 4, 2, 1, 3, 0}, 4},
        {{1, 2, 3, 1, 4, 5}, 3},
        {{5, 0, 1, 3, 2, 4, 1, 0, 5}, 4},
        {{1, 2, 3, 2, 1}, 3}
    };

    cout << "=== Testing LRU Page Replacement Algorithm ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> pages = testCases[t].first;
        int capacity = testCases[t].second;
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Pages: [";
        for (int i = 0; i < pages.size(); i++) {
            cout << pages[i];
            if (i < pages.size() - 1) cout << ", ";
        }
        cout << "], Capacity: " << capacity << "\n\n";
        
        // Test all three approaches
        vector<int> pages1 = pages, pages2 = pages, pages3 = pages;
        
        int ans1 = pageFaultsBruteForce(pages1, capacity);
        cout << "\nResult: " << ans1 << " page faults\n\n";
        
        int ans2 = pageFaultsBetter(pages2, capacity);  
        cout << "\nResult: " << ans2 << " page faults\n\n";
        
        LRUCache lru(capacity);
        int ans3 = lru.pageFaultsOptimal(pages3);
        cout << "\nResult: " << ans3 << " page faults\n\n";
        
        // Detailed explanation for first test case
        if (t == 0) {
            explainPageFaults(pages, capacity);
        }
        
        cout << "=== Summary ===\n";
        cout << "Brute Force: " << ans1 << " page faults\n";
        cout << "Better Approach: " << ans2 << " page faults\n";  
        cout << "Optimal Approach: " << ans3 << " page faults\n";
        cout << "========================\n\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ LRU Page Replacement Overview:\n";
    cout << "Key Concepts:\n";
    cout << "• Page Fault: Requested page not in memory (cache miss)\n";
    cout << "• Page Hit: Requested page found in memory (cache hit)\n";
    cout << "• LRU Policy: Replace Least Recently Used page when memory is full\n";
    cout << "• MRU: Most Recently Used page (last accessed)\n\n";
    
    cout << "Algorithm Approaches:\n";
    cout << "1. Brute Force → O(N*C) time, uses vector with linear search\n";
    cout << "2. Better → O(N*C) time, uses deque + hash set for faster lookup\n";
    cout << "3. Optimal → O(N) time, uses hash map + doubly linked list\n\n";
    
    cout << "Real-world Applications:\n";
    cout << "• Operating System page replacement\n";
    cout << "• CPU cache management\n";
    cout << "• Database buffer management\n";
    cout << "• Web browser cache\n";
    cout << "• Application-level caching (Redis, Memcached)\n\n";
    
    cout << "The LRU algorithm balances temporal locality principle:\n";
    cout << "Recently accessed pages are more likely to be accessed again soon! 🎯\n";

    return 0;
}

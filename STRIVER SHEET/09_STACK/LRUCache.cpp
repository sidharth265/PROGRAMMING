#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: LRU Cache (Least Recently Used Cache)
 Problem Link: (LeetCode 146 or similar)
====================================================

📝 Problem Statement:
Design and implement a data structure for Least Recently Used (LRU) cache.
It should support:
- get(key): Return the value of the key if it exists, else -1.
- put(key, value): Update or insert the value. When capacity is reached, evict the least recently used key.

Use a data structure that supports O(1) for both get and put.

📌 Input:
- Fixed capacity
- Sequence of get and put operations

📌 Output:
- Results from get operations

----------------------------------------------------
🔹 Example:
Operations:
put(1,1), put(2,2), get(1), put(3,3), get(2), put(4,4), get(1), get(3), get(4)
Output:
1
-1
-1
3
4

Explanation:
When capacity is reached, evicts the least recently used key.

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Doubly Linked List + Hash Map
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use a doubly linked list to track usage order (head = most recent, tail = least).
- Use a hash map to get nodes in O(1).
- On get or put, move accessed/added nodes to front.
- On capacity full, remove least recently used node from tail.

🧩 Algorithm:
1. Maintain dummy head and tail nodes for easy list operations.
2. get(key):
   - If not found, return -1.
   - Else remove node and add to head (most recent), return value.
3. put(key,value):
   - If key exists, remove old node.
   - If capacity reached, remove node before tail.
   - Add new node at head.
4. Removal and addition are O(1) operations on doubly linked list.

⏱ Time Complexity: O(1) for get and put operations  
📦 Space Complexity: O(capacity)
*/

class Node {
public:
    int key, value;
    Node* next;
    Node* prev;

    Node(int k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
};

class LRUCache {
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head; // dummy head (most recent after head)
    Node* tail; // dummy tail (least recent before tail)

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        cache.erase(node->key);
        delete node;
    }

    void addNodeToFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
        cache[node->key] = node;
    }

    void moveToFront(Node* node) {
        // remove current position
        node->prev->next = node->next;
        node->next->prev = node->prev;
        // insert at front
        addNodeToFront(node);
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        // Clean up nodes to avoid memory leak
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;
        Node* node = cache[key];
        moveToFront(node);
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // Update value and move to front
            Node* node = cache[key];
            node->value = value;

            // Remove node from current position
            node->prev->next = node->next;
            node->next->prev = node->prev;

            // Add updated node at front
            addNodeToFront(node);
        } else {
            if ((int)cache.size() == capacity) {
                // Evict LRU (node before tail)
                removeNode(tail->prev);
            }
            Node* newNode = new Node(key, value);
            addNodeToFront(newNode);
        }
    }
};

//////////////////////////////////////////////////////
// Main function with example usage
//////////////////////////////////////////////////////
int main() {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // returns 1

    cache.put(3, 3);              // evicts key 2
    cout << cache.get(2) << endl; // returns -1 (not found)

    cache.put(4, 4);              // evicts key 1
    cout << cache.get(1) << endl; // returns -1 (not found)
    cout << cache.get(3) << endl; // returns 3
    cout << cache.get(4) << endl; // returns 4

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Efficient LRU cache implementation using doubly linked list
// for usage order, and hashmap for O(1) access to nodes.
// Both get and put complete in O(1) time on average.

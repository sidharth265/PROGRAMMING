#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: LFU Cache (Least Frequently Used Cache)
 Problem Link: (LeetCode 460 or similar)
====================================================

📝 Problem Statement:
Design and implement a data structure for a Least Frequently Used (LFU) cache.
Implement the functions:
- `get(key)`: Return the value of the key if it exists, otherwise -1.
- `put(key, value)`: Update or insert the value. When capacity is reached, evict the least frequently used key.
If multiple keys have the same frequency, evict the least recently used one.

📌 Input:
- A fixed capacity for the cache.
- A series of get and put operations.

📌 Output:
- Values retrieved by get operations.

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
Evictions happen by LFU policy; ties broken by LRU.

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: LFU Cache with frequency lists and hashmap
//////////////////////////////////////////////////////
/*
💡 Idea:
- Maintain:
  - A map from key to its Entry (value, freq, iterator to list).
  - A map from frequency to list of keys ordered by recency.
  - Track minimum frequency `minFreq`.

- On get(key), increase frequency ranking and update data structures.
- On put:
   - If cache full, evict least frequently used key:
       - Find key in freqList[minFreq] back (oldest).
       - Remove from all maps.
   - Insert new key with frequency 1.
- This gives O(1) amortized operations.

🧩 Algorithm:
1. On touch(key):
   - Remove key from freqList of old frequency.
   - If empty and freq is minFreq, increment minFreq.
   - Insert key into freqList of new frequency at front.
   - Update kv[key].freq and iterator.
2. On get(key), if not found return -1, else touch and return value.
3. On put(key, value):
   - If key exists, update value and touch.
   - Else if capacity reached, evict key with minFreq from back.
   - Insert new key at freq=1, update minFreq=1.

⏱ Time Complexity: O(1) amortized for get and put  
📦 Space Complexity: O(capacity)
*/

class LFUCache {
    int capacity;
    int minFreq;
    unordered_map<int, list<int>> freqList; // freq -> keys list
    struct Entry {
        int value;
        int freq;
        list<int>::iterator it;
    };
    unordered_map<int, Entry> kv; // key -> Entry

    void touch(int key) {
        auto &e = kv[key];
        int f = e.freq;

        freqList[f].erase(e.it);
        if (freqList[f].empty()) {
            freqList.erase(f);
            if (minFreq == f) minFreq++;
        }

        int nf = f + 1;
        freqList[nf].push_front(key);
        e.freq = nf;
        e.it = freqList[nf].begin();
    }

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    int get(int key) {
        if (capacity == 0) return -1;
        if (kv.find(key) == kv.end()) return -1;
        touch(key);
        return kv[key].value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (kv.count(key)) {
            kv[key].value = value;
            touch(key);
            return;
        }

        if ((int)kv.size() == capacity) {
            int evictKey = freqList[minFreq].back();
            freqList[minFreq].pop_back();
            if (freqList[minFreq].empty()) freqList.erase(minFreq);
            kv.erase(evictKey);
        }

        minFreq = 1;
        freqList[1].push_front(key);
        kv[key] = {value, 1, freqList[1].begin()};
    }
};

//////////////////////////////////////////////////////
// Main function with example usage
//////////////////////////////////////////////////////
int main() {
    LFUCache cache(2);

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
// This LFU Cache uses a frequency map with key lists for efficient eviction of 
// least frequently used keys, and internal order for tie-breaking by recency.
// All operations (get/put) run in O(1) amortized time.

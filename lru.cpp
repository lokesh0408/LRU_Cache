// Least Recently Used (LRU) is a cache replacement algorithm that replaces cache when the space is full.
// It allows us to access the values faster by removing the least recently used values.
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string key;
    int val;
    Node(string k, int v)
    {
        key = k;
        val = v;
    }
};

// LRU Cache data structure   --> uses doubly linked list and hashmap.
class LRUCache
{
public:
    int maxSize;
    list<Node> l;
    unordered_map<string, list<Node>::iterator> m; // list<Node>::iterator --> is an address ---> as map stores (key , address)..

    LRUCache(int maxSize)
    {
        this->maxSize = maxSize > 1 ? maxSize : 1;
    }

    void insertKeyValue(string key, int val) // O(1).
    {
        // 2 cases
        // 1 -> if key is present in cache i.e. list, then it must be present in the map also

        if (m.count(key) != 0) // so key exists
        {
            // so now, replace the old value and update
            auto it = m[key]; // it will give the address
            it->val = val;    // update the old value
        }
        else
        {
            // if cache is full------->
            // then, remove least recently used key(item) i.e. (last key) from the list(cache) and map both.... and add new key at the top of the list, and, update the entry in hashmap
            if (l.size() == maxSize) // means cache is full
            {
                Node last = l.back(); // it will give the last node
                l.pop_back();         // remove from the linked list
                m.erase(last.key);    // remove from the map
            }

            Node n(key, val);   // create new node
            l.push_front(n);    // and, insert(add) into the top of linked list
            m[key] = l.begin(); // and, update the entry in hashmap
        }
    }

    int *getValue(string key) // O(1).
    {
        // if key is present, only then return the value
        if (m.count(key) != 0)
        {
            auto it = m[key];    // gives address
            int value = it->val; // now, this is the most recently used key.... so it should comes to the top of the list.
            l.push_front(*it);   // *it -> will give the node of that address and that node has (key,value) pair.

            // so, *it will store the copy of that pair.
            l.erase(it); // and, original will get deleted from the list.

            m[key] = l.begin(); // and, update the entry of first node of list in hashmap.

            // as, cache(list) may not have every key, so return the address of the node.
            return &l.begin()->val; // finally, return the address of that (MRU  = most recently used) i.e. first node now.
        }

        return NULL; // if key is not present
    }

    string mostRecentKey() // O(1).
    {
        return l.front().key + " " + to_string(l.front().val); // i.e. the head(or, first) node of the list.
    }
};

int main()
{
    cout << "                              ########################################  LRU Cache  ########################################" << endl;
    LRUCache lru(3);
    lru.insertKeyValue("mango", 10);
    lru.insertKeyValue("banana", 20);
    lru.insertKeyValue("apple", 30);
    cout << lru.mostRecentKey() << endl; // apple

    lru.insertKeyValue("mango", 40);     // here, it will simply update 10 to 40.
    cout << lru.mostRecentKey() << endl; // apple

    cout << "Enter a key : ";
    string name;
    cin >> name;
    int *orders = lru.getValue(name); // name (e.g. -> mango) will come to the head of the list now and has become mru.
    if (orders != NULL)
    {
        cout << "Order of " << name << " is : " << *orders << endl;
    }

    lru.insertKeyValue("guava", 20); // guava will come to the head of the list now and banana(LRU key) will be deleted.

    if (lru.getValue("apple") == NULL)
    {
        cout << "apple doesn't exist";
    }

    if (lru.getValue("banana") == NULL)
    {
        cout << "banana doesn't exist";
    }

    if (lru.getValue("guava") == NULL)
    {
        cout << "guava doesn't exist";
    }

    if (lru.getValue("mango") == NULL)
    {
        cout << "mango doesn't exist";
    }
}
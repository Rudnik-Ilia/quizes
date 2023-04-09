#include <iostream>
#include <list>

using namespace std;

template<typename K, typename V>
class HashTable {
private:
    int size;
    list<pair<K, V>> *table;
public:
    HashTable(int size) {
        this->size = size;
        table = new list<pair<K, V>>[size];
    }

    ~HashTable() {
        delete [] table;
    }

    int hashFunction(K key) {
        return key % size;
    }

    void insert(K key, V value) {
        int index = hashFunction(key);
        table[index].push_back(make_pair(key, value));
    }

    void remove(K key) {
        int index = hashFunction(key);
        typename list<pair<K, V>>::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                break;
            }
        }
    }

    V find(K key) {
        int index = hashFunction(key);
        typename list<pair<K, V>>::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                return it->second;
            }
        }
        return -1;
    }
};

int main() {
    HashTable<int, string> hashTable(5);
    hashTable.insert(1, "One");
    hashTable.insert(2, "Two");
    hashTable.insert(3, "Three");

    cout << "Finding key 2: " << hashTable.find(2) << endl;
    hashTable.remove(2);
    cout << "Finding key 2 after remove: " << hashTable.find(2) << endl;

    return 0;
}
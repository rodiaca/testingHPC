#include <unordered_map>
#include <list>
#include <iostream>

// Conditions:
// We want remain the last values that we use and delete the old
// When the cache is full and a new element must be inserted, the cache must automatically remove the Least Recently Used (LRU) element.
// An element is considered "used" when:
// it is inserted
// it is accessed through get()
// The most recently used element should remain in the cache.

class LRUCacheWRONG //WRONG VERSION - it doesn’t implement an LRU cache; it always deletes the last element instead of retaining the most recently used element
{
public:
    explicit LRUCacheWRONG(size_t capacity) : capacity_(capacity) {
        lastKeyUsed = 0;
    };

    int get(int key) {
        if(buffer.empty()){ return 0; }

        auto value = buffer.find(key);
        if(value == buffer.end()){
            //Don't have the value
            return -1;
        }
        lastKeyUsed = value->first;

        return value->second;
    }

    void put(int key, int value){
        std::pair<int, int> aux = {key, value};
        auto aux1 = buffer.find(key);

        if(capacity_ == buffer.size() && aux1 == buffer.end()){
            //delete the last and add the new
            buffer.erase(lastKeyUsed);
            buffer.insert(aux);
        } else { 
            if(aux1 == buffer.end()){
                //Don't have the value
                buffer.insert(aux);
            } else {
                //update the value
                buffer[key] = value;
            }
        }
        lastKeyUsed = key;
    }

private:
    size_t capacity_;
    //we can't use vector if we want cost O(1) to acces the data. 
    // std::vector<std::pair<int, int>> buffer;

    //we need this. It makes sense
    std::unordered_map<int, int> buffer;

    int lastKeyUsed;
    // Add your data structures here
};

class LRUCache
{
public:
    explicit LRUCache(size_t capacity) : capacity_(capacity) {}

    int get(int key)
    {
        auto it = cache.find(key);
        if (it == cache.end())
            return -1;

        // Move accessed element to the front (most recently used)
        usage.splice(usage.begin(), usage, it->second);

        return it->second->second;
    }

    void put(int key, int value)
    {
        auto it = cache.find(key);

        if (it != cache.end())
        {
            // Key exists → update value + move to front
            it->second->second = value;
            //ponemos el valor al principio -> ultimo usado
            usage.splice(usage.begin(), usage, it->second);
            return;
        }

        // If full → remove least recently used (back of list)
        if (cache.size() == capacity_)
        {
            auto lru = usage.back();
            cache.erase(lru.first);
            usage.pop_back();
        }

        // Insert new element at front
        usage.emplace_front(key, value);
        cache[key] = usage.begin();
    }

private:
    size_t capacity_;

    // Doubly linked list: most recent at front, least recent at back
    std::list<std::pair<int, int>> usage;

    // key -> iterator pointing into list
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache;
};

int main() {
    LRUCache cache(3);

    std::cout << "Insert 1,2,3\n";
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    std::cout << "\nGet existing key:\n";
    std::cout << "get(1) = " << cache.get(1) << '\n'; // 10

    std::cout << "\nInsert 4 (should evict 2)\n";
    cache.put(4, 40);

    std::cout << "get(2) = " << cache.get(2) << '\n'; // -1
    std::cout << "get(3) = " << cache.get(3) << '\n'; // 30
    std::cout << "get(4) = " << cache.get(4) << '\n'; // 40

    std::cout << "\nUpdate existing key:\n";
    cache.put(3, 300);

    std::cout << "get(3) = " << cache.get(3) << '\n'; // 300

    std::cout << "\nInsert 5 (should evict 1)\n";
    cache.put(5, 50);

    std::cout << "get(1) = " << cache.get(1) << '\n'; // -1
    std::cout << "get(5) = " << cache.get(5) << '\n'; // 50

    return 0;
}
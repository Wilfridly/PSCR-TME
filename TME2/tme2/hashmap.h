#pragma once
#include <cstddef>
#include <forward_list>
#include <vector>

namespace pr{

template <typename K, typename V>

class Hashmap{
    public:
    class Entry{
        public:
        const K key;
        V value;
        Entry(const K &key, const V &value):key(key), value(value){}
    };
    private: 
       typedef std::vector<std::forward_list<Entry>>buckets_t;
       buckets_t buckets;
       size_t size;

    public:
        Hashmap(size_t size = 21000):buckets(size),size(1){}

        V * get(const K &key) {
            size_t h = std::hash<K>()(key);
            size_t target = h % buckets.size();
            for (Entry &ent:buckets[target]) {
                if (ent.key == key) {
                    return &ent.value;
                }
            }
            return nullptr;
        }



        bool put(const K & key, const V & value) {
            size_t h = std::hash<K>()(key);
            size_t target = h % buckets.size();

            for(Entry &ent:buckets[target]) {
                if(ent.key==key){
                    ent.value =ent.value + 1;
                    // std::cout << "debug" << ent.value << std::endl;
                    return true;
                }
            }
            buckets[target].emplace_front(key,value);
            ++size;
            return false;
        }

        size_t getsize() const{
            return size;
        }

        buckets_t getbuckets() const{
            return buckets;
        }
        
    };
}
#pragma once
#include <cstddef>
#include <forward_list>
#include <vector>

namespace pr{
template < typename K, typename V>
class Hashmap{
    public:
    class Entry{
        public:
        const K key;
        V value;
        Entry(const *K key, const &V value):key(key), value(value){}
        }   
    private: 
        typedef std::vector<forward_list<Entry>>Buckets_t;
        buckets_t buckets;
        size_t size;
    
    }
}
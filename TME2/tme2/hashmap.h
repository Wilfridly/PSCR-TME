#pragma once
#include <cstddef>
#include <forward_list>
#include <vector>
#include <iterator>



namespace pr{

template <typename K, typename V>

class Hashmap{
    public:
    //ENTRY CLASS
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
        // ITERATOR CLASS
        class iterator{
            public:
            //Ajouter pour que les iterators fonctionnent
            using iterator_category = std::forward_iterator_tag;
            using difference_traits = std::ptrdiff_t;
            using value_type = Entry;
            using pointer_type = Entry*;
            using reference_type = Entry&;
            
            private:
            // typedef std::vector<std::forward_list<Entry>>buckets_t;
            typename buckets_t::iterator iterend;
            typename buckets_t::iterator vit;
            typename std::forward_list<Entry>::iterator lit;

            public:
            //ctor
            iterator(typename buckets_t::iterator vit,typename buckets_t::iterator iterend): vit(vit), iterend(iterend){
                lit = vit.begin();
            }
            //ctor par defaut
            iterator(): vit(), iterend(), lit(){}
            
            iterator & operator++(){
                lit++;
                while(vit != iterend && lit ){

                    if(lit == nullptr ){
                        if(vit != nullptr){
                            lit = vit;
                            return *this;
                        }
                    }
                    
                }
                return *this;
            }
        };
    };
}
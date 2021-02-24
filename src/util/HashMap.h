// #pragma once

// #include <util/Vector.h>

// /*
// This is a niave implementation, later versions should use hash buckets
// */

// template <typename Key, typename Value>
// class HashMap{
// public:

//     struct MapEntry{
//         Key key;
//         Value value;
//     };


//     void put(Key key, Value value){
//         m_keys.push_back(key);
//         m_values.push_back(value);
//         m_size++;
//     }

//     Value& at(unsigned int index){
//         return m_values.at(index);
//     }

//     Value& get(Key key){
//         for(int i=0;i<m_size;i++){
//             if(m_entries[i].key==key){
//                 return m_entries[i].value;
//             }
//         }
//     }

//     Value& operator[](Key key){
//         return get(key);
//     }

// private:
//     unsigned int m_size=0;
//     Vector<MapEntry<Key, Value>> m_entries;
// };
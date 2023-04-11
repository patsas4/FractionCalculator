#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <cstdint>
#include <stdexcept>

using namespace std;

const uint32_t
        TABLE_SIZE = 127;


template<typename KeyType, typename ValueType>
class Dictionary {
public:
    explicit Dictionary() {
        count =0;
    }

    ~Dictionary() {count = 0;}

    uint32_t size() { return count; }

    void insert(KeyType key, ValueType val) {
        for (uint32_t i = 0; i<key.size(); i++) {
            if (keys[i] == key) {
                values[i] = val;
                return;
            }
        }
        keys[count] = key;
        values[count++] = val;
    }

    ValueType search(KeyType a) {
        for (uint32_t i = 0; i<a.size(); i++) {
            if (keys[i] == a)
                return values[i];
        }
        throw domain_error("Does not exist");
    }

private:
    uint32_t
        count = 0;
    KeyType
        keys[TABLE_SIZE];
    ValueType
        values[TABLE_SIZE];
};

#endif //_DICTIONARY_H

#include "hash.h"

int prime_Numbers[] = {100003, 200003, 400009, 800011, 1600033, 3200003};

hashTable::hashTable(int size){
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
}


unsigned int hashTable::getPrime(int size){
    unsigned int hash_Size = 0;
    for (int i = 0; i < sizeof(prime_Numbers); i++){
        if(prime_Numbers[i] > size*2){
            hash_Size = prime_Numbers[i];
            return hash_Size;
        }
    }
    return 0;
}

int hashTable::hash(const std::string & key){
    unsigned int hash_val = 0;
    for(char ch: key){
        hash_val = 37*hash_val + ch;
    }

    return hash_val % capacity;
}

int hashTable::insert(const std::string &key, void *pv){
    int index = hash(key);
    if(contains(key)){
        return 1;
    }
    if(2*filled >= capacity){
        if(rehash() == false){
            return 2;
        }
    }

    //linear probing
    while(data[index].isOccupied){
        index++;
        index %= capacity;
    }

    data[index].key = key;
    data[index].isOccupied = true;
    data[index].pv = pv;
    filled++;
    return 0;
 }

 bool hashTable::contains(const std::string &key){
     if(findPos(key) < 0){
         return false;
     }else{
         return true;
     }
 }

 int hashTable::findPos(const std::string &key){
     int pos = hash(key);
     int i = 0;

    for(int i = 0; i < capacity; i++){
        if(data[pos].key == key){
            return pos;
        }else if(data[pos].isOccupied){
            pos++;
            pos %= capacity;
        }else{
            return -1;
        }  
    }
    return -1;
 }

bool hashTable::rehash(){
    std::vector<hashItem> temp = data;
    int new_size = getPrime(capacity);
    try{
        data.resize(new_size);
    }catch(std::bad_alloc){
        return false;
    }

    capacity = new_size;
    filled = 0;
    
    //reinitialize
    for(int i = 0; i < data.size(); i++){
        data[i].key = "";
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }
    
    //copy the data
    for(int i = 0; i < temp.size(); i++){
        if(temp[i].isOccupied && (!temp[i].isDeleted)){
            insert(temp[i].key, temp[i].pv);
        }
    }
    return true;
}
#include "heap.h"

// Constructor
heap::heap(int capacity){
    // since the zero index is ignored
    data.resize(capacity + 1);

    mapping = hashTable(capacity + 1);
    this->capacity = capacity;
    size = 0;
}

int heap::insert(const std::string &id, int key, void *pv){

    if (size < capacity) {
        if (mapping.contains(id)) {
            // if id already exist
            return 2; 
        }
        else {
            size++;
            data[size].id = id;
            data[size].key = key;
            data[size].pData = pv;
            
            mapping.insert(id, &data[size]);
            
            percolateUp(size); 
            return 0;
        }
    }else {
        // Heap is at max capacity
        return 1;
    }
}

int heap::setKey(const std::string &id, int key){
    
    int old_key;
    int pos;

    if (!(mapping.contains(id))){
        // id does not exist
        return 1;
    }

    node *ptr = static_cast<node *>(mapping.getPointer(id));

    old_key = ptr->key;
    ptr->key = key;

    pos = int(ptr - &data[0]);

    if (key > old_key) {
        percolateDown(pos);
    }else if (key < old_key) {
        percolateUp(pos);
    }
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if (size == 0){
        return 1;
    }

    if (pId != NULL){
        *pId = data[1].id;
    }

    if (pKey != NULL){
        *pKey = data[1].key;
    }

    if (ppData != NULL){
        *(static_cast<void **>(ppData)) = data[1].pData;
    }

    mapping.remove(data[1].id);
    data[1] = data[size];
    size--;
    percolateDown(1);
    return 0;
}


int heap::remove(const std::string &id, int *pKey, void *ppData){
    if (mapping.contains(id)) {

        node *ptr = static_cast<node *> (mapping.getPointer(id));
        
        if (pKey != NULL){
            *pKey = ptr -> key;
        }
    
        if (ppData != NULL){
            *(static_cast<void **> (ppData)) = ptr->pData;
        }
        
        mapping.remove(id);
        int pos = int(ptr - &data[0]);
        // fill the position with the last node of the heap temporally
        *ptr = data[size];
        size--;
        
        percolateDown(pos);
        percolateUp(pos);
        
        return 0;
    }else {
        // id is not contained in the heap
        return 1;
    }
}

void heap::percolateUp(int pos){
    
    node temp = data[pos];  

    for (; pos > 1 && temp.key < data[pos>>1].key; pos = pos>>1) {
        data[pos] = data[pos>>1];
        mapping.setPointer(data[pos].id, &data[pos]);
    }
    
    data[pos] = temp;
    mapping.setPointer(data[pos].id, &data[pos]);
}

void heap::percolateDown(int pos){
    node temp = data[pos];
    
    int child, leftIndex, rightIndex;
    
    while((pos<<1) <= size) {
        leftIndex = pos<<1;
        rightIndex = leftIndex + 1;
        // to prevent rightIndex is not valid and choose the smaller one of child to move up
        if (rightIndex <= size) {
            if(data[rightIndex].key < data[leftIndex].key){
                child = rightIndex;
            }else{
                child = leftIndex;
            }
        }else {
            child = leftIndex;
        }

        if (data[child].key < temp.key) {
            data[pos] = data[child];
            mapping.setPointer(data[pos].id, &data[pos]);
            pos = child;
        }else {
            break;
        }
    }
    
    data[pos] = temp;
    mapping.setPointer(data[pos].id, &data[pos]);
}

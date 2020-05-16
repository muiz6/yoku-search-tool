#include "yoku/InvertedIndex.hpp"
#include <cmath>
#include <iostream>
using namespace yoku;

int InvertedIndex::_hashFunc(std::string key) {
    size_t sum;

    // replacing int i with size_t is producing unexpected result
    for (int i = 0; i < key.length(); i++) {
        int ascii = key.at(i);

        // modulus distibution over addition to avoid overflow
        // i.e. (A + B) % C = (A % C + B % C) % C
        int segment = (ascii * (int)pow(_A, i)) % _TABLE_SIZE;
        sum += segment;
    }
    int hash = sum % _TABLE_SIZE;
    return hash;
}

InvertedIndex::InvertedIndex()
    : _htable(NULL) {
    _htable = new IndexNode*[_TABLE_SIZE];
    for (int i = 0; i < _TABLE_SIZE; i++) {
        _htable[i] = NULL;
    }
}

InvertedIndex::~InvertedIndex() {
    for (int i = 0; i < _TABLE_SIZE; i++) {
        IndexNode *temp = _htable[i];
        while (temp != NULL) {
            IndexNode *toDel = temp;
            temp = temp->getNext();
            delete toDel;
        }
    }
    delete[] _htable;
}

void InvertedIndex::insert(std::string key, size_t position) {
    IndexNode *newNode = new IndexNode(key);
    newNode->insertPosition(position);
    int index = _hashFunc(key);
    IndexNode *temp = _htable[index];
    if (temp == NULL) {
        _htable[index] = newNode;
    }
    else {
        bool flagExists = false;
        IndexNode *pre = temp;
        do {
            pre = temp;
            if (temp->getKey() == key) {
                flagExists = true;
                break;
            }
            temp = temp->getNext();
        } while (temp != NULL);

        if (flagExists) {
            pre->insertPosition(position);
        }
        else {
            pre->setNext(newNode);
        }
    }
}

IndexNode* InvertedIndex::find(std::string key) {
    int index = _hashFunc(key);
    IndexNode* temp = _htable[index];
    while (temp != NULL && temp->getKey() != key) {
        temp = temp->getNext();
    }
    return temp;
}

void InvertedIndex::display() {
    std::cout << "[Display Hash Table]\n";
    for (int i = 0; i < _TABLE_SIZE; i++) {
        IndexNode* temp = _htable[i];
        if (temp != NULL) {
            std::string key = temp->getKey();
            int hash = _hashFunc(key);
            // int hash = _hashFunc(temp->getKey()); // producing unexpected result
            std::cout << "Hash: " << hash << "\tKeys: ";
            do {
                std::cout << temp->getKey() << " | ";
                temp = temp->getNext();
            } while(temp != NULL);
            std::cout << "\n";
        }
    }
}

void InvertedIndex::clear() {
    for (int i = 0; i < _TABLE_SIZE; i++) {
        IndexNode *temp = _htable[i];
        while (temp != NULL) {
            IndexNode *toDel = temp;
            temp = temp->getNext();
            delete toDel;
        }
        _htable[i] = NULL;
    }
}
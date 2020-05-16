#include "yoku/Trie.hpp"
#include <iostream>
using namespace yoku;

// recurscively create trie of given string under given node
void Trie::_insertChildNodes(TrieNode *parent, std::string &word) {
    if (word != "") {
        const char key = word.at(0);
        TrieNode *const node = new TrieNode(key);
        std::vector<TrieNode*> &children = parent->getChildren();
        _insertChild(node, children);

        // find node bcz it may already exist and incoming node may have been
        // ignored so next operations are guaranteed to be performed on the
        // already present node
        TrieNode *const node2 = _findNode(key, children, 0, children.size() - 1);
        if (word.size() == 1) {
            node2->setEndOfWord(true);
        }
        word.erase(0, 1); // remove leading character
        _insertChildNodes(node2, word);
    }
}

// inserts node alphabetically to given children vector
// deletes incoming node if already present
void Trie::_insertChild(TrieNode* node, std::vector<TrieNode*> &children) {
    int position = 0;
    char key = node->getKey();
    bool flagExists = false;
    for (std::size_t i = 0; i < children.size(); i++) {
        const char compare = children.at(i)->getKey();
        if (key > compare) {
            position++;
        }
        else if (key == compare) {
            flagExists = true;
        }
        else {
            break;
        }
    }
    if (!flagExists) {
        children.insert(children.begin() + position, node);
    }
    else {
        delete node;
    }
}

// binary search
TrieNode* Trie::_findNode(char key, const std::vector<TrieNode*> &children,
        int low , int up) {

    if (up >= low) {
        int mid = low + (up - low) / 2;
        TrieNode* node = children.at(mid);

        if (node->getKey() == key) {
            return node;
        }
        if (node->getKey() > key) {
            return _findNode(key, children, low, mid - 1);
        }
        // else <
        return _findNode(key, children, mid + 1, up);
    }
    // else not found
    return NULL;
}

// find last node in given string inside trie
TrieNode* Trie::_findNode(std::string word) {
    char key = word.at(0);
    TrieNode *node = _findNode(key, _root, 0, _root.size() - 1);
    TrieNode *result = NULL;
    if (node !=NULL) {
        word.erase(0, 1);
        if (word != "") {
            result = _findNodeHelper(word, node);
        }
    }
    return result;
}

TrieNode* Trie::_findNodeHelper(std::string word, TrieNode *node) {
    char key;
    if (!word.empty()) {
        key = word.at(0);
    }
    std::vector<TrieNode*> &children = node->getChildren();
    TrieNode *childNode = _findNode(key, children, 0, children.size() - 1);
    if (childNode != NULL) {
        word.erase(0, 1);
        if (word.empty()) {
            return childNode;
        }
        // else
        return _findNodeHelper(word, childNode);
    }
    // else
    return NULL;
}

void Trie::_displayHelper(TrieNode *node, int depth) const {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    std::cout << node->getKey() << "\n";
    int size = node->getChildren().size();
    depth++;
    for (int i = 0; i < size; i++) {
        TrieNode *child = node->getChildren().at(i);
        _displayHelper(child, depth);
    }
}

// depth traverse every child till endOfWordNodes
void Trie::_suggestionHelper(TrieNode *node, std::vector<std::string> &result,
        std::string suggestion) const {

    suggestion += node->getKey();
    std::vector<TrieNode*> &children = node->getChildren();
    for (std::size_t i = 0; i < children.size(); i++) {
        TrieNode *child = children.at(i);
        if (child->isEndOfWord()) {
            suggestion += child->getKey();
            result.push_back(suggestion);
        }
        else {
            _suggestionHelper(children.at(i), result, suggestion);
        }
    }
}

void Trie::_clearHelper(TrieNode *parent) {
    std::vector<TrieNode*> &children = parent->getChildren();
    for (std::size_t i = 0; i < children.size(); i++) {
        _clearHelper(children.at(i));
    }
    delete parent;
}

Trie::Trie() {}

Trie::~Trie() {
    for (std::size_t i = 0; i < _root.size(); i++) {
        _clearHelper(_root.at(i));
    }
}

void Trie::insert(std::string word) {
    char key = word.at(0);
    TrieNode* node = _findNode(key, _root, 0, _root.size() - 1);
    if (node != NULL) {
        word.erase(0, 1); // remove first character
        // make trie of remaining string under node
        _insertChildNodes(node, word);
    }
    else {
        int position = 0;
        for (std::size_t i = 0; i < _root.size(); i++) {
            const char compare = _root.at(i)->getKey();
            if (key > compare) {
                position++;
            }
            else {
                break;
            }
        }
        _root.insert(_root.begin() + position, new TrieNode(key));
        insert(word);
    }
}

void Trie::display() const {
    for (std::size_t i = 0; i <_root.size(); i++){
        _displayHelper(_root.at(i), 0);
    }
}

std::vector<std::string> Trie::getSuggestions(std::string prefix) {
    std::vector<std::string> result;
    TrieNode* node = _findNode(prefix);
    if (node != NULL) {
        std::vector<TrieNode*> &children = node->getChildren();
        for (std::size_t i = 0; i < children.size(); i++) {
            _suggestionHelper(children.at(i), result, prefix);
        }
    }
    return result;
}
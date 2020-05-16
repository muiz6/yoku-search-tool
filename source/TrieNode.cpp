#include "yoku/TrieNode.hpp"
using namespace yoku;

TrieNode::TrieNode(char key, bool isEndOfWord)
    : _key(key),
    _isEndOfWord(isEndOfWord) {}

TrieNode::~TrieNode() {}

char TrieNode::getKey() const {
    return _key;
}

std::vector<TrieNode*>& TrieNode::getChildren() {
    return _children;
}

void TrieNode::setEndOfWord(bool value) {
    _isEndOfWord = value;
}

bool TrieNode::isEndOfWord() {
    return _isEndOfWord;
}
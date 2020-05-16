#include "yoku/IndexNode.hpp"
using namespace yoku;

IndexNode::IndexNode(std::string key)
    : _key(key),
    _next(NULL) {}

IndexNode::~IndexNode() {}

void IndexNode::setKey(std::string key) {
    _key = key;
}

std::string IndexNode::getKey() {
    return _key;
}

void IndexNode::setNext(IndexNode *node) {
    _next = node;
}

IndexNode* IndexNode::getNext() {
    return _next;
}

std::size_t IndexNode::getFrequency() {
    return _posVec.size();
}

void IndexNode::insertPosition(std::size_t position) {
    _posVec.push_back(position);
}

std::vector<std::size_t> IndexNode::getPositionVector() {
    return _posVec;
}
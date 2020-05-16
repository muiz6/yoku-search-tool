#ifndef YOKU_INDEX_NODE_H
#define YOKU_INDEX_NODE_H

#include <string>
#include <stddef.h>
#include <vector>

namespace yoku {
    class IndexNode {
        private:
            std::string _key;
            IndexNode* _next;
            std::vector<std::size_t> _posVec;

        public:
            IndexNode(std::string key = "");
            virtual ~IndexNode();
            void setKey(std::string key);
            std::string getKey();
            void setNext(IndexNode *node);
            IndexNode* getNext();
            std::size_t getFrequency();
            void insertPosition(std::size_t postion);
            std::vector<std::size_t> getPositionVector();
    };
}

#endif // YOKU_HASHNODE_H
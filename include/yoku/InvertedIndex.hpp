#ifndef YOKU_INVERTED_INDEX_H
#define YOKU_INVERTED_INDEX_H

#include "yoku/IndexNode.hpp"
#include <string.h>
#include <stddef.h>

namespace yoku {
    class InvertedIndex {
        private:
            static const int _TABLE_SIZE = 4001;
            static const int _A = 37;
            IndexNode **_htable;
            int _hashFunc(std::string key);

        public:
            InvertedIndex();
            virtual ~InvertedIndex();
            void insert(std::string key, std::size_t position);
            IndexNode* find(std::string key);
            void display();
            void clear();
    };
}

#endif // HASHMAP_H
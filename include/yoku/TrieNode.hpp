#ifndef YOKU_TRIE_NODE_H
#define YOKU_TRIE_NODE_H

#include <vector>
#include <string>

namespace yoku {
    class TrieNode {
        private:
            char _key;
            bool _isEndOfWord;
            std::vector<TrieNode*> _children;

        public:
            TrieNode(char key, bool isEndOfWord = false);
            static TrieNode* sCreateTree(std::string word);
            virtual ~TrieNode();
            char getKey() const;
            std::vector<TrieNode*>& getChildren();
            void setEndOfWord(bool value);
            bool isEndOfWord();
    };
}

#endif // YOKU_TRIE__NODE_H
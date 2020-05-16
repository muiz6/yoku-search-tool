#ifndef YOKU_TRIE_H
#define YOKU_TRIE_H

#include "yoku/TrieNode.hpp"
#include <string>
#include <vector>

namespace yoku {
    class Trie {
        private:
            std::vector<yoku::TrieNode*> _root;

            void _insertChildNodes(TrieNode *parent, std::string &word);
            void _insertChild(TrieNode* node, std::vector<TrieNode*> &children);
            TrieNode* _findNode(char key,
                    const std::vector<TrieNode*> &children, int low, int up);
            TrieNode* _findNode(std::string word);
            TrieNode* _findNodeHelper(std::string word, TrieNode* node);
            void _displayHelper(TrieNode* node, int depth) const;
            void _suggestionHelper(TrieNode *node,
                    std::vector<std::string> &result,
                    std::string suggestion) const;
            void _clearHelper(TrieNode* parent);

        public:
            Trie();
            virtual ~Trie();
            void insert(std::string word);
            std::vector<std::string> getSuggestions(std::string prefix);
            void display() const;
    };
}

#endif // YOKU_TRIE_H
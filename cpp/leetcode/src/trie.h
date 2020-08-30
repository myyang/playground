#ifndef LEETCODE_TRIE_H
#define LEETCODE_TRIE_H

#include<memory>
#include<string>
#include<vector>
#include<unordered_map>

// #208
class TrieArray {
private:
    struct TrieNode {
        TrieNode(): is_end(false), children(26, nullptr){}

        ~TrieNode() {
            for (TrieNode* child: children)
                if (child) delete child;
        }

        bool is_end;
        std::vector<TrieNode*> children;
    };

    // note that use class/template name rather than pointer as pointers type
    std::unique_ptr<TrieNode> root_;

    TrieNode* find(std::string& word)
    {
        TrieNode* p = root_.get();
        for (char c: word)
        {
            p = p->children[c-'a'];
            if (!p) break;
        }
        return p;
    }

public:
    TrieArray(): root_(std::make_unique<TrieNode>()) {}

    void insert(std::string& word)
    {
        TrieNode* p = root_.get();
        for (char c: word)
        {
            if (!p->children[c-'a'])
                p->children[c-'a'] = new TrieNode();
            p = p->children[c-'a'];
        }
        p->is_end = true;
    }

    bool search(std::string& word)
    {
        const TrieNode* p = find(word);
        return p && p->is_end;
    }
};

class TrieMap {
private:
    struct TrieNode {
        TrieNode(): is_end(false) {};
        ~TrieNode() {
            for (auto& kv: children)
                if (kv.second) delete kv.second;
        }

        bool is_end;
        std::unordered_map<char, TrieNode*> children;
    };

    std::unique_ptr<TrieNode> root_;

    TrieNode* find(std::string& word)
    {
        TrieNode* p = root_.get();
        for (char c: word)
        {
            p = p->children[c];
            if (!p) break;
        }
        return p;
    }

public:
    TrieMap(): root_(std::make_unique<TrieNode>()) {}

    void insert(std::string& word)
    {
        TrieNode *p = root_.get();
        for (char c: word)
        {
            if (!p->children.count(c))
                p->children[c] = new TrieNode();
            p = p->children[c];
        }
        p->is_end = true;
    }

    bool search(std::string& word)
    {
        TrieNode *p = find(word);
        return p && p->is_end;
    }
};

#endif

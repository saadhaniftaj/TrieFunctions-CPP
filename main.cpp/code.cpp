#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;

// TrieNode class definition
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool is_end_of_word;
    TrieNode() {
        is_end_of_word = false;
    }
};

// Trie class definition
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->is_end_of_word = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->is_end_of_word;
    }

    vector<string> words_with_prefix(string prefix) {
        vector<string> results;
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return results;
            }
            node = node->children[c];
        }

        // Perform a depth-first search to collect all words under the node
        stack<pair<TrieNode*, string>> dfs_stack;
        dfs_stack.push({node, prefix});
        while (!dfs_stack.empty()) {
            pair<TrieNode*, string> top = dfs_stack.top();
            dfs_stack.pop();
            if (top.first->is_end_of_word) {
                results.push_back(top.second);
            }
            for (auto it : top.first->children) {
                dfs_stack.push({it.second, top.second + it.first});
            }
        }
        return results;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("bat");
    trie.insert("batman");
    string prefix = "app";
    vector<string> results = trie.words_with_prefix(prefix);
    for (string word : results) {
        cout << word << endl;
    }
    return 0;
}

#include <unordered_map>
#include <memory>
#include <cassert>
#include <vector>

class TrieNode {
    std::unordered_map<char, std::unique_ptr<TrieNode>> go;
    int terminal;
    bool used = false;

    TrieNode () : terminal (0) {}
    void dump (FILE* logs);
    friend class Trie;
    friend class DTrie;
};

class Trie {
protected:
    std::unique_ptr<TrieNode> root;
    FILE* logs;

    void dfs (TrieNode* cur, std::vector<std::string>& words, std::string& word);
    void printNodes (TrieNode* node);
public:
    Trie (FILE* _logs = stdout) : root (new TrieNode (NULL)), logs (_logs) {}
    TrieNode* get_root () const;
    bool has (const char* string) const;
    void add (const char* string);
    void remove (const char* string);
    std::vector<std::string> getWords ();
    void dump ();
};


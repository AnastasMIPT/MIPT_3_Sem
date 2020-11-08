#include <unordered_map>
#include <memory>
#include <cassert>

class TrieNode {
    std::unordered_map<char, std::unique_ptr<TrieNode>> go;
    bool terminal;

    TrieNode () = default;
    TrieNode (bool _terminal) :terminal (_terminal) {}
    void dump (FILE* logs);
    friend class Trie;
};

class Trie {
    std::unique_ptr<TrieNode> root;
    FILE* logs;

    void printNodes (TrieNode* node);
public:
    Trie (FILE* _logs = stdout) : root (new TrieNode ()), logs (_logs) {}
    bool has (const char* string) const;
    void add (const char* string);
    void remove (const char* string);
    void dump ();
};



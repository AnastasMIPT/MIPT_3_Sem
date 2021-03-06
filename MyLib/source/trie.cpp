#include "trie.h"


void Trie::add (const char* string) {
    TrieNode* ptr = root.get ();

    for (char* str_p = const_cast<char*> (string); *str_p != '\0'; ++str_p) {
        auto next_node_it = ptr->go.find (*str_p);
        if (next_node_it != ptr->go.end ()) {
            ptr = (*next_node_it).second.get ();
        } else {
            ptr->go[*str_p] = 
            std::unique_ptr<TrieNode> (new  TrieNode ());

            ptr = ptr->go[*str_p].get ();
        }
    }
    ptr->terminal++;
}

bool Trie::has (const char* string) const {
    TrieNode* ptr = root.get ();

    for (char* str_p = const_cast<char*> (string); *str_p != '\0'; ++str_p) {
        auto next_node_it = ptr->go.find (*str_p);
        if (next_node_it ==  ptr->go.end ()) {
            return false;
        } else {
            ptr = (*next_node_it).second.get ();
        } 
    }
    if (ptr->terminal) {
        return true;
    } else {
        return false;
    }
}


void Trie::remove (const char* string) {
    TrieNode* ptr = root.get ();

    for (char* str_p = const_cast<char*> (string); *str_p != '\0'; ++str_p) {
        auto next_node_it = ptr->go.find (*str_p);
        if (next_node_it ==  ptr->go.end ()) {
            return;
        } else {
            ptr = (*next_node_it).second.get ();
        } 
    }
    ptr->terminal--;
}


TrieNode* Trie::get_root () const {
    return root.get ();
}


void Trie::dump () {
    assert(root);
    assert(logs);
    fprintf (logs, "digraph {\n");
    root->dump (logs);
    printNodes (root.get());
    fprintf(logs, "}\n");
}

void TrieNode::dump (FILE* logs) {
    fprintf (logs, "node%p [ shape=box];\n", this);
}

void Trie::printNodes (TrieNode* node) {
    assert (node);
    for (auto& el : node->go) {
        TrieNode* ptr = el.second.get ();
        ptr->dump (logs);
        fprintf (logs, "node%p -> node%p [color=\"red\", label=\"%c\"];\n", node, ptr, el.first);
        printNodes (ptr);
    }
}


void Trie::dfs (TrieNode* cur, std::vector<std::string>& words, std::string& word) {
    cur->used = true;
    if (cur->terminal) {
        for (int i = 0; i < cur->terminal; ++i)
            words.push_back (word);
        
    }
    for (int i = 0; i < 26; ++i) {
        auto it = cur->go.find ('a'+ i);
        if (it == cur->go.end ()) continue;
        auto elem = it->second.get ();
        if (!elem->used) {
            word.push_back('a' + i);
            dfs (elem, words, word);
        }
    }
    if (word.size ()) word.pop_back ();
}

std::vector<std::string> Trie::getWords () {
    std::vector<std::string> words;
    std::string word ("");

    dfs (root.get (), words, word);
    return words;
}
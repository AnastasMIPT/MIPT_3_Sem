#include "trie.h"


void Trie::add (const char* string) {
    TrieNode* ptr = root.get ();

    for (char* str_p = const_cast<char*> (string); *str_p != '\0'; ++str_p) {
        auto next_node_it = ptr->go.find (*str_p);
        if (next_node_it != ptr->go.end ()) {
            ptr = (*next_node_it).second.get ();
        } else {
            ptr->go[*str_p] = 
            std::unique_ptr<TrieNode> (new  TrieNode (*(str_p + 1) == '\0'));

            ptr = ptr->go[*str_p].get ();
        }
    }
    
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

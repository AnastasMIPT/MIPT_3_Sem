#include "../trie.h"

int main () {
    FILE* f_dot = fopen ("output.dot", "w");
    Trie trie (f_dot);
    trie.add ("hello");
    trie.add ("helko");
    trie.add ("hey");
    printf ("%d, %d, %d, %d\n", trie.has ("heyg"), trie.has ("hey"), trie.has ("hello"), trie.has ("h"));
    //trie.dump ();


    fclose (f_dot);
    return 0;   
}
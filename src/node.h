#ifndef __NODE_H__
#define __NODE_H__

#define NAME_LENGTH 32
#define DICTIONARY_SIZE 256

struct node {
    char name[NAME_LENGTH+1];
    struct node * parent; // the parent of this node
    struct node * head_child; // the first child of this node
    struct node * next_sibling; // the next sibling (next child of the parent) of this node
    int child_count;
    struct node * next_dictionary; // used for linked list in dictionary.
    int depth;
};

typedef struct node node;

struct dictionary
{
    node * nodes[DICTIONARY_SIZE];
};

typedef struct dictionary dictionary;

void add_child (node * parent, node * child);
node * find_node(char * name, dictionary * dictionary);
void add_to_dictionary(node * target_node, dictionary *  dictionary);
void add_node(char * center, char * orbiter, dictionary * dictionary);
void delete_all_nodes(dictionary * dictionary);
void set_depth_recusrive(node * parent);

#endif

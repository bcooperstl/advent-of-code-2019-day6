#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"

void add_child (node * parent, node * child)
{
    if (child->parent != NULL)
    {
        fprintf(stderr, "FATAL ERROR - child %s already has parent %s assigned. Attempting to assign new parent %s\n", child->name, child->parent->name, parent->name);
        exit(1);
    }
    child->parent=parent;

    if (parent->head_child == NULL) // first child for this parent
    {
        parent->head_child = child;
        parent->child_count = 1;
    }
    else
    {
        node * parent_child_iter = parent->head_child;
        while (parent_child_iter->next_sibling != NULL)
        {
            parent_child_iter = parent_child_iter->next_sibling;
        }
        parent_child_iter->next_sibling = child;
        parent->child_count++;    
    }
}

node * find_node(char * name, dictionary * dictionary)
{
    char key = name[0];
    node * list_node = dictionary->nodes[key];

    if (list_node == NULL) // nothing in the dictionary for the first letter of the name.
    {
        return NULL;
    }
    
    while (list_node != NULL)
    {
        if (strncmp(list_node->name, name, NAME_LENGTH) == 0) // name matches
        {
            return list_node;
        }
        else
        {
            list_node = list_node->next_dictionary;
        }
    }

    return NULL; // not found in dictionary
}

void add_to_dictionary(node * target, dictionary * dictionary)
{
    char key = target->name[0];
    node * list_node = dictionary->nodes[key];
    if (list_node == NULL)
    {
        dictionary->nodes[key]=target;
    }
    else
    {
        // sanity check that this isn't already in the dictionary
        while (list_node != NULL)
        {
            if (strncmp(list_node->name, target->name, NAME_LENGTH) == 0) // node already in dictionary
            {
                fprintf(stderr, "FATAL ERROR - node %s is already in the dictionary!!\n", target->name);
                exit(1);
            }
            list_node = list_node->next_dictionary;
        }
        
        list_node = dictionary->nodes[key];
        while (list_node->next_dictionary != NULL)
        {
            list_node = list_node->next_dictionary;
        }
        // now list_node has the last element for this dictionary entry. Add this element to it.
        list_node->next_dictionary = target;
    }
}

// add a node, so that the orbiter orbits the center.
void add_node(char * center, char * orbiter, dictionary * dictionary)
{
    node * center_node = find_node(center, dictionary);
    node * orbiter_node = find_node(orbiter, dictionary);
    if (center_node == NULL)
    {
        center_node = malloc(sizeof(node));
        memset(center_node, 0, sizeof(node));
        strncpy(center_node->name, center, NAME_LENGTH);
        add_to_dictionary(center_node, dictionary);
    }
    if (orbiter_node == NULL)
    {
        orbiter_node = malloc(sizeof(node));
        memset(orbiter_node, 0, sizeof(node));
        strncpy(orbiter_node->name, orbiter, NAME_LENGTH);
        add_to_dictionary(orbiter_node, dictionary);
    }
    add_child(center_node, orbiter_node);
}

void delete_all_nodes(dictionary * dictionary)
{
    for (int i=0; i<DICTIONARY_SIZE; i++)
    {
        node * curr = dictionary->nodes[i];
        if (curr != NULL)
        {
            node * tmp = curr;
            curr = curr->next_dictionary;
            free(tmp);
        }
        dictionary->nodes[i] = NULL;
    }
}

void set_depth_recusrive(node * parent)
{
    int child_depth = parent->depth+1;
    node * child = parent->head_child;
    while (child != NULL)
    {
        //printf("set %s to depth %d\n", child->name, child_depth);
        child->depth = child_depth;
        set_depth_recusrive(child);
        child = child->next_sibling;
    }
}

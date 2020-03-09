#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

#define DELIMITER ')'
#define CENTER_OF_MASS "COM"

int main (int argc, char * argv[])
{
    FILE * infile=NULL;
    char buffer[256];
    char center[NAME_LENGTH+1], orbiter[NAME_LENGTH+1];
    dictionary lookup_dictionary; // dictionary to speed up lookups of nodes
    node * com_node; // node for the center of mass

    memset(&lookup_dictionary, '\0', sizeof(dictionary));
    
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    
    fprintf(stderr, "Opening file %s\n", argv[1]);
    
    infile=fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        exit(1);
    }
    
    while (fgets(buffer, sizeof(buffer), infile))
    {
        char * eol = strchr(buffer, '\r');
        if (eol)
        {
            *eol='\0';
        }
        eol = strchr(buffer, '\n');
        if (eol)
        {
            *eol='\0';
        }
        
        //fprintf(stderr, "Read [%s]\n", buffer);
        char * split = strchr(buffer, DELIMITER);
        if (split == NULL)
        {
            fprintf(stderr, "Skipping line [%s] due to no delimiter\n", buffer);
            continue;
        }
        int center_length = split-buffer;
        if (center_length > NAME_LENGTH)
        {
            fprintf(stderr, "center from line [%s] longer than max length\n", buffer);
            exit(1);
        }
        strncpy(center, buffer, center_length);
        center[center_length]='\0';
        strncpy(orbiter, split+1, NAME_LENGTH);
        //fprintf(stderr, "Split line [%s] into center [%s] and orbiter [%s]\n", buffer, center, orbiter);
        add_node(center, orbiter, &lookup_dictionary);
    }
    
    fclose(infile);

    com_node = find_node(CENTER_OF_MASS, &lookup_dictionary);
    if (com_node == NULL)
    {
        fprintf(stderr, "No COM node found\n");
        exit(1);
    }
    
    set_depth_recusrive(com_node);
    
    int sum_orbits = 0;
    for (int i=0; i<DICTIONARY_SIZE; i++)
    {
        node * curr = lookup_dictionary.nodes[i];
        while (curr != NULL)
        {
            sum_orbits+=curr->depth;
            curr = curr->next_dictionary;
        }
    }
    
    printf("*****Total sum of orbits is %d\n", sum_orbits);
    
    delete_all_nodes(&lookup_dictionary);
    
    return 0;
}
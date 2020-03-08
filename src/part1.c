int main (int argc, char * argv[])
{
    FILE * infile=NULL;
    char buffer[256];

    dictionary lookup_dictionary; // dictionary to speed up lookups of nodes
    node * com_node; // node for the center of mass

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
    }
    
    fclose(infile);
    
    return 0;
}
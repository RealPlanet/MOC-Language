#include "../include/util.h"

char* read_ascii_file(const char* path){

    // Open file as read only
    FILE* file = fopen(path, "r");

    if(!file){
        printf("Could not open file '%s'\n", path);
        return NULL; // TODO :: This will break things if not handled properly
    }

    //Seek to EOF then save to int
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    // Go back to SOF
    fseek(file, 0, SEEK_SET);

    // Transfer ownership of memory to the caller
    char* buf = (char*) malloc(sizeof(char) * (size + 1));
    if(!buf){
        printf("Could not allocate memory for file!\n");
        return NULL; // TODO :: This will break things if not handled properly
    }

    fread(buf, 1, size, file);
    buf[size] = '\0'; // For safety I add a null char to EOS
    fclose(file);

    // Return contents
    return buf;
}
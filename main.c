/* 
 * File:   main.c
 * Author: Matthias Drummer <s0542834>
 *
 * Created on 8. November 2013, 10:59
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "archiver.h" // import my header.

// define globals
Archive_Index indexes[16];

/**
 * Method prints out a simple help for the user.
 */
void printHelp();

/**
 * Lists the content of the given archive.
 * 
 * @param fileName the filename of the given archive
 */
void listContentOfArchive(char *fileName);

/*
 * 
 */
int main(int argc, char** argv) {

    if (argc == 1) {
        printf("No archive name was given. See following help for informations\n\n");

        printHelp();
    } else {
        // open archive by given name
        int fileDescriptor = open(argv[1], O_RDONLY, S_IRUSR | S_IRGRP);
        if (fileDescriptor == -1) {
            return EXIT_FAILURE;
        }
        // read magic number
        int magicNumber;
        int numberOfBytesRead = read(fileDescriptor, &magicNumber, 2);
        
        printf("FileDescriptor: %i\n", fileDescriptor);
        printf("NumberOfBytesRead: %i\n", numberOfBytesRead);
        printf("MagicNumber: %x\n", magicNumber);
        // read structs
//        numberOfBytesRead = read(fileDescriptor, indexes, sizeof(indexes) * sizeof(Archive_Index));
        numberOfBytesRead = read(fileDescriptor, indexes, sizeof(indexes));
        printf("NumberOfBytesRead: %i\n", numberOfBytesRead);
//        printf("MagicNumber: %x\n", indexes);
        
        // output structs
    }

    return (EXIT_SUCCESS);
}

void listContentOfArchive(char* fileName) {

}

void printHelp() {
    printf("The syntax for the program is: <program> <archive name> [<parameter>]");
    printf("\nFor example: ./ardir anArchive ");
}


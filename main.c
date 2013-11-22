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
#include <time.h>

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
 */
void listContentOfArchive();

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
        short magicNumber;
        int numberOfBytesRead = read(fileDescriptor, &magicNumber, 2);

        // check for correct archive
        if (magicNumber != 0x4242) {
            printf("Falsches Archiv\n");
            return EXIT_FAILURE;
        }
        // read structs
        numberOfBytesRead = read(fileDescriptor, indexes, sizeof (indexes));

        if (numberOfBytesRead == -1) {
            // something went wrong reading the indexes
            printf("Error when reading the indexes.");
            return EXIT_FAILURE;
        }

        listContentOfArchive();
        close(fileDescriptor);
    }
    
    return (EXIT_SUCCESS);
}

void listContentOfArchive() {

    // TODO: das funktioniert erstmal nur für ein Inhaltsverzeichnis. Index State Continue auswerten, wenn die aradd Funktionalität fertig ist.

    // output structs
    int i;
    //        for (i = 0; i < sizeof (indexes) / sizeof (Archive_Index); i++) {
    for (i = 0; i < 16; i++) {
        Archive_Index index = indexes[i];
        printf("Index Position: %i\n", i);
        printf("State: %s\n", mapIndexStateToString(index.state));
        printf("Last access time: %s", ctime(&index.lastAccessTime));
        printf("UID: %i\n", index.uid);
        printf("GID: %i\n", index.gid);
        printf("File type: %s\n", mapFileTypeToString(index.fileType));
        printf("File name: %s\n", index.fileName);
        printf("Size in bytes: %i\n", (int) index.sizeInBytes);
        printf("Byte position in archive: %i\n\n", (int) index.bytePositionInArchive);
    }
}

void printHelp() {
    printf("The syntax for the program is: <program> <archive name> [<parameter>]");
    printf("\nFor example: ./ardir anArchive ");
}


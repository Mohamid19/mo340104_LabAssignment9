#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 15

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Node for linked list
struct Node
{
    struct RecordType data;
    struct Node *next;
};

// HashType with array and its size
struct HashType
{
    struct Node *array[HASH_SIZE];
};

// Compute the hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Function to insert a record into the hash table
// Function to insert a record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType record)
{
    int index = hash(record.id);
    
    // Create a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = record;
    newNode->next = NULL;

    // Insert the node into the linked list at the specified index
    if (hashTable->array[index] == NULL)
    {
        // If the index is empty, set the new node as the first element
        hashTable->array[index] = newNode;
    }
    else
    {
        // If the index is not empty, append the new node at the end of the linked list
        struct Node *current = hashTable->array[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType *hashTable)
{
    printf("Hash Table:\n");
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        struct Node *current = hashTable->array[i];
        if (current == NULL)
        {
            continue;
        }

        printf("Index %d -> ", i);
        while (current != NULL)
        {
            printf("ID: %d Name: %c Order: %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("\n");
    }
}

// Function to free the memory used by the hash table and its linked lists
void freeHashTable(struct HashType *hashTable)
{
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        struct Node *current = hashTable->array[i];
        while (current != NULL)
        {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("Records:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Your hash implementation
    struct HashType hashTable;

    // Initialize the hash table array with NULL
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        hashTable.array[i] = NULL;
    }

    // Insert each record into the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(&hashTable, pRecords[i]);
    }

    // Display the records in the hash table
    displayRecordsInHash(&hashTable);

    // Free memory used by the hash table
    freeHashTable(&hashTable);

    // Free the memory used by the record array
    free(pRecords);

    return 0;
}
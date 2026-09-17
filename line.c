#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

char *lines[MAX_LINES];
int lineCount = 0;

/* Function declarations */
void insertLine();
void deleteLine();
void displayDocument();
void freeMemory();

/* Insert a new line */
void insertLine()
{
    int lineNumber;
    char text[MAX_LENGTH];
    int i;

    if (lineCount >= MAX_LINES)
    {
        printf("\nError: Document is full.\n");
        return;
    }

    printf("\nEnter line number to insert (1-%d): ", lineCount + 1);
    scanf("%d", &lineNumber);

    if (lineNumber < 1 || lineNumber > lineCount + 1)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    /* Remove newline left by scanf */
    getchar();

    printf("Enter text: ");
    fgets(text, MAX_LENGTH, stdin);

    /* Remove newline from fgets */
    text[strcspn(text, "\n")] = '\0';

    /* Shift lines downward */
    for (i = lineCount; i >= lineNumber; i--)
    {
        lines[i] = lines[i - 1];
    }

    /* Allocate memory for new line */
    lines[lineNumber - 1] = malloc(strlen(text) + 1);

    if (lines[lineNumber - 1] == NULL)
    {
        printf("Error: Memory allocation failed.\n");

        /* Undo the shift */
        for (i = lineNumber - 1; i < lineCount; i++)
        {
            lines[i] = lines[i + 1];
        }

        return;
    }

    strcpy(lines[lineNumber - 1], text);

    lineCount++;

    printf("Line inserted successfully.\n");
}

/* Delete a line */
void deleteLine()
{
    int lineNumber;
    int i;

    if (lineCount == 0)
    {
        printf("\nDocument is empty. Nothing to delete.\n");
        return;
    }

    printf("\nEnter line number to delete (1-%d): ", lineCount);
    scanf("%d", &lineNumber);

    if (lineNumber < 1 || lineNumber > lineCount)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    /* Free memory of the selected line */
    free(lines[lineNumber - 1]);

    /* Shift lines upward */
    for (i = lineNumber - 1; i < lineCount - 1; i++)
    {
        lines[i] = lines[i + 1];
    }

    /* Remove duplicate pointer at the end */
    lines[lineCount - 1] = NULL;

    lineCount--;

    printf("Line deleted successfully.\n");
}

/* Display the document */
void displayDocument()
{
    int i;

    if (lineCount == 0)
    {
        printf("\nDocument is empty.\n");
        return;
    }

    printf("\n========== DOCUMENT ==========\n");

    for (i = 0; i < lineCount; i++)
    {
        printf("%d: %s\n", i + 1, lines[i]);
    }

    printf("===============================\n");
}

/* Free all allocated memory */
void freeMemory()
{
    int i;

    for (i = 0; i < lineCount; i++)
    {
        free(lines[i]);
        lines[i] = NULL;
    }

    lineCount = 0;
}

/* Main function */
int main()
{
    char command;

    printf("========================================\n");
    printf("          SIMPLE LINE EDITOR\n");
    printf("========================================\n");

    while (1)
    {
        printf("\nCommands:\n");
        printf("i - Insert line\n");
        printf("d - Delete line\n");
        printf("p - Display document\n");
        printf("q - Quit\n");

        printf("\nEnter command: ");
        scanf(" %c", &command);

        switch (command)
        {
            case 'i':
            case 'I':
                insertLine();
                break;

            case 'd':
            case 'D':
                deleteLine();
                break;

            case 'p':
            case 'P':
                displayDocument();
                break;

            case 'q':
            case 'Q':
                freeMemory();
                printf("\nExiting editor...\n");
                return 0;

            default:
                printf("Error: Invalid command.\n");
        }
    }

    return 0;
}
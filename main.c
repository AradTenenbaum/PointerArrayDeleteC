// Arad Tenenbaum 212293799
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DIF_CHAR '^'

// Build the string array with input
char ** getStrArrayInput(int * size) {
    
    char ** strArr;
    scanf("%d", size);
    
    strArr = (char**)malloc((*size) * sizeof(char*));
    if(strArr == NULL) exit(1);
    for(int i = 0; i < *size; i++) {
        strArr[i] = (char*)malloc(100*sizeof(char*));
        if(strArr[i] == NULL) exit(1);
        scanf("%s", strArr[i]);
    }
    
    return strArr;
}

char** setPtrToCharsArray(char** str_array)
{

	char** res;

	int size, i;

	int str_array_row, str_array_col;



	scanf("%d", &size); // Get number of ptrs

	res = (char**)malloc(sizeof(char*)*(size+1)); // Add 1 for NULL at the end

	if(res == NULL) {

		exit(1);

	}

	for (i = 0; i < size; i++)

	{

		scanf("%d", &str_array_row);

		scanf("%d", &str_array_col);

		res[i] = str_array[str_array_row] + str_array_col;

	}

	res[size] = NULL; // Set the last one to NULL

	return res;

}

// print the array
void printStringArr(char ** arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

// Paste the part of string on dest
// Assuming part is smaller than dest
int overrideString(char * dest, char * part) {
    // The new size of the array
    int decSize = 1;
    // Check if the part contains a streak of the char we need to remove
    while((*part == DIF_CHAR) && (*part != '\0')) {
        part++;
        decSize++;
    }
    // if the part ends the dest should too
    if(strlen(part) == 0) *dest = '\0';
    // Paste part on dest
    for(int i = 0; ((i < strlen(part)) && (*(dest + i) != '\0')); i++) {
        *(dest + i) = *(part + i);
    }
    return decSize;
}

// Release the unused memory for each string
void shortenString(char ** str, int newSize) {
    char * newStr;
    newStr = (char*)malloc(newSize * sizeof(char));
    if(newStr == NULL) exit(1);
    for(int i = 0; i < newSize; i++) {
        newStr[i] = (*str)[i];
    }
    free(*str);
    *str = newStr;
}

// The function
unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array) {
    // the temp size of each string
    int tempSize = 0;
    char ** strTemp = *str_array;
    int i = 0;
    // Change the char we need to delete to a special char
    while(ptr_to_chars_array[i] != NULL) {
        *ptr_to_chars_array[i] = DIF_CHAR;
        i++;
    }
    // Delete all the special chars and release unused memory
    for(int i = 0; i < str_array_size; i++) {
        tempSize = strlen(strTemp[i]);
        for(int j = 0; j < strlen(strTemp[i]); j++) {
            if(strTemp[i][j] == DIF_CHAR) {
                
                tempSize = tempSize - overrideString(strTemp[i] + j, strTemp[i] + j + 1);
                shortenString(&(strTemp[i]), tempSize);
            }
        }
    }
    char ** newStr = (char**)malloc(sizeof(char*));
    if(newStr == NULL) exit(1);
    int newSize = 0;
    // set the size of the string array
    for(int i = 0; i < str_array_size; i++) {
        if(strlen(strTemp[i]) != 0) {
            newSize++;
            newStr = (char**)realloc(newStr, newSize * sizeof(char*));
            newStr[newSize-1] =  (char*)malloc(strlen(strTemp[i]) * sizeof(char));
            if(newStr[newSize-1] == NULL) exit(1);
            strcpy(newStr[newSize-1], strTemp[i]);
        }
    }
    // release old array
    free(strTemp);
    *str_array = newStr;
    return (str_array_size-newSize);
}

void freeArray(char ** str_array, unsigned int str_array_size) {
    for(int i = 0; i < str_array_size; i++) {
        free(str_array[i]);
    }
    free(str_array);
}



int main()
{
    
    char** str_array;

       unsigned int str_array_size;

       char** ptr_to_chars_array;

       unsigned int res;

 

       str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)

       ptr_to_chars_array = setPtrToCharsArray(str_array);

       res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);

      printStringArr(str_array, str_array_size - res);

 

       // Free memory

      freeArray(str_array, str_array_size - res);

       free(ptr_to_chars_array);
    
    return 0;
}

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

struct line
{
    //! char* str - pointer on line
    char* str = nullptr;
    //! int len - length of line
    int len = 0;
};

int CountString(char* buffer);

//! Function that compare symbols from left sight
//! @param [in] a - string
//! @param [in] b - string
int CompareLeft(line* p, line* q);

//! Function that compare symbols from right sight
//! @param [in] a - string
//! @param [in] b - string
int CompareRight(line* p, line* q);

//! Function that count size of the file
//! @param [in] file - file wich size we want to count
int CountSize(FILE* file);

//! Function that gain strings from buffer
//! @param [in] buffer - array of symbols from file
//! @param [in] cur_str - strings that now in array
//! @param [in] next_str - strings that will be in array
//! @param [out] line* strings - array of pointers on strings
void GainString(char* buffer, line* strings);

//! Function that open and close file inside,
//! call function CountSize and
//! call function Copy
//! @param [in] file - file wich we open
//! @param [in] buffer - array of symbols from file
//! @param [out] size - size of file
void CreateBuffer(char** buffer);

//! Function that copy symbols from file to array
//! @param [in] file - file wich we want to copy
//! @param [out] storage - array with symbols from file
void Copy(char* storage, FILE* file);

//! Function that print symbols in file
//! @param [out] file - file that contains all symbols from temp
//! @param [in] line* temp - array of pointers that contains symbols
void PrintInFile(const line* temp, FILE* file);

//! Function that sort file
//! @param [in] line* n_core - array of pointers on strings
//! @param [in] int left - number of the first string (0)
//! @param [in] int right - number of the last string (n_str - 1)
//! @param [in] int(*compare)(line* a, line* b)
//! compare - will chose type of comparation
//! line* a and line* b will be compared

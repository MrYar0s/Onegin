#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line;

int nString(char* buffer);

//! Function that compare symbols from left sight
//! @param [in] a - string
//! @param [in] b - string
int CompareLeft(const void* p, const void* q);

//! Function that compare symbols from right sight
//! @param [in] a - string
//! @param [in] b - string
int CompareRight(const void* p, const void* q);

//! Function that count size of the file
//! @param [in] file - file wich size we want to count
int CountSize(FILE* file);

//! Function that gain strings from buffer
//! @param [in] buffer - array of symbols from file
//! @param [in] cur_str - strings that now in array
//! @param [in] next_str - strings that will be in array
//! @param [out] line* strings - array of pointers on strings
void GainString(char* buffer, line* strings);

//! Function that swap two arrays of pointers
//! @param [in] line* a - first array on start
//! @param [in] line* b - second array on start
//! They will swap and
//!					  line* a will be line* b
//!                   line* b will be line* a
void Swap(line* a, line* b);

//! Function that open and close file inside,
//! call function CountSize and
//! call function Copy
//! @param [in] file - file wich we open
//! @param [in] buffer - array of symbols from file
//! @param [out] size - size of file
void CreateBuffer(int* size, char** buffer);

//! Function that copy symbols from file to array
//! @param [in] file - file wich we want to copy
//! @param [out] storage - array with symbols from file
void Copy(char* storage, FILE* file);

//! Function that print symbols in file
//! @param [out] file - file that contains all symbols from temp
//! @param [in] line* temp - array of pointers that contains symbols
void PrintInFile(const line* temp);

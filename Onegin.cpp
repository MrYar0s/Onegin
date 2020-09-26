#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct line 
{
    //! char* str - pointer on line
    char* str = nullptr;
    //! int len - length of line
    int   len = 0;
};

void CreateBuffer(int* size, char** buffer);
void QuickSort(line* n_core, int left, int right, int(*compare)(line* a, line* b));
void PrintFile(FILE* file, const line* temp);
void GainString(char* buffer, line* mem);
void Copy(char* storage, FILE* file);
void Swap(line* a, line* b);
int  CompareLeft(line* a, line* b);
int  CompareRight(line* a, line* b);
int  CountSize(FILE* file);
int  nString(char* buffer);
int  LetterCheck(const char c);

int main()
{
    int   size   = 0;
    char* buffer = nullptr;

    FILE* sorted = fopen("sorted.txt", "w");

    assert(sorted);

    CreateBuffer(&size, &buffer);

    assert(buffer);

    size_t n_str = nString(buffer);

    line* strings = (line*)calloc(n_str + 1, sizeof(line));

    GainString(buffer, strings);

    QuickSort(strings, 0, n_str - 1, CompareLeft);

    QuickSort(strings, 0, n_str - 1, CompareRight);
    
    PrintFile(sorted, strings);
    
    fclose(sorted);
    return 0;
}
//create buffer
void CreateBuffer(int* size, char** array)
{
    FILE* hamlet = fopen("hamlet.txt", "r");

    assert(hamlet);

    *size = CountSize(hamlet);
    *array = (char*)calloc(*size, sizeof(char));
    Copy(*array, hamlet);

    fclose(hamlet);
}
//quick sort
void QuickSort(line* n_core, int left, int right, int(*compare)(line* a, line* b))
{
    line core = n_core[(left + right) / 2];

    int i = left;
    int j = right;

    while (i <= j)
    {

        while (compare(&n_core[j], &core) > 0)
            --j;

        while (compare(&n_core[i], &core) < 0)
            ++i;

        if (i <= j)
        {
            Swap(&n_core[i], &n_core[j]);
            ++i;
            --j;
        }
    }
    if (left < j)
        QuickSort(n_core, left, j, compare);

    if (right > i)
        QuickSort(n_core, i, right, compare);

}
//print txt in file
void PrintFile(FILE* file, const line* temp)
{
    while (temp->str != nullptr)
    {
        fprintf(file, "%s\n", temp->str);
        ++temp;
    }
}
//gain strings
void GainString(char* buffer, line* strings)
{
    strings->str = buffer;
    char* cur_str = buffer;
    char* next_str = strchr(buffer, '\n');
    while (next_str != nullptr) {
        *next_str = '\0';

        next_str++;
        strings->len = next_str - cur_str - 1;

        strings++;
        strings->str = next_str;

        cur_str = next_str;
        next_str = strchr(next_str, '\n');
    }
}
//copy file in array
void Copy(char* storage, FILE* file)
{

    fseek(file, 0, SEEK_END);
    int param = ftell(file);
    rewind(file);
    fread(storage, sizeof(char), param, file);

}
//swap
void Swap(line* a, line* b)
{
    line temp = *a;
    *a = *b;
    *b = temp;
}
//right check
int CompareRight(line* a, line* b)
{

    int count_a = a->len,
        count_b = b->len;

    while (count_a >= 0 && count_b >= 0)
    {
        if (LetterCheck(a->str[count_a]) && LetterCheck(b->str[count_b]))
        {
            if (a->str[count_a] > b->str[count_b])
            {
                return 1;
            }
            if (a->str[count_a] < b->str[count_b])
            {
                return -1;
            }
            --(count_a);
            --(count_b);
        }
        else
        {
            while (!LetterCheck(a->str[count_a]))
            {
                --(count_a);
            }
            while (!LetterCheck(b->str[count_b]))
            {
                --(count_b);
            }
        }
    }
    if (count_a == -1 && count_b == -1)
        return 0;
    if (count_a == -1)
        return -1;
    if (count_b == -1)
        return 1;
    return 0;
}
//left check
int CompareLeft(line* a, line* b)
{

    int count_a = a->len,
        count_b = b->len;

    int i = 0,
        j = 0;

    while (i < count_a && j < count_b) 
    {
        if (a->str[i] > b->str[j])
            return 1;
        if (a->str[i] < b->str[j])
            return -1;
        ++i;
        ++j;
    }
    return 0;
}
//num of symbols in file
int CountSize(FILE* file)
{
    int symbols = 0;
    fseek(file, 0, SEEK_END);
    symbols = ftell(file);
    return symbols;
}
//count of strings
int nString(char* buffer)
{
    int count = 1;

    char* tmp_buffer = strchr(buffer, '\n');

    while (tmp_buffer != NULL) {
        tmp_buffer = strchr(tmp_buffer + 1, '\n');
        ++count;
    }

    return count;
}
//letter check
int LetterCheck(const char c)
{
    if (('A' <= c <= 'Z') || ('a' <= c <= 'z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

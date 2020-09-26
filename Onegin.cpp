#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "Onegin.h"

struct line 
{
    //! char* str - pointer on line
    char* str = nullptr;
    //! int len - length of line
    int len = 0;
};

int main()
{
    int size = 0;
    char* buffer = nullptr;
    
    CreateBuffer(&size, &buffer);

    assert(buffer);

    size_t n_str = nString(buffer);

    line* strings = (line*)calloc(n_str + 1, sizeof(line));

    GainString(buffer, strings);

    QuickSort(strings, 0, n_str - 1, CompareRight);
    QuickSort(strings, 0, n_str - 1, CompareLeft);
    
    PrintInFile(strings);
    
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
void PrintInFile(const line* temp)
{
    FILE* sorted = fopen("sorted.txt", "w");
    
    while (temp->str != nullptr)
    {
        fprintf(sorted, "%s\n", temp->str);
        ++temp;
    }
    
    fclose(sorted);
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
        if (isalpha(a->str[count_a]) && isalpha(b->str[count_b]))
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
            while (isalpha(a->str[count_a]))
            {
                --(count_a);
            }
            while (isalpha(b->str[count_b]))
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
int CompareLeft(line* a, line* b)
{

    int count_a = 0,
        count_b = 0;

    while (count_a < a->len && count_b < b->len)
    {
        if (isalpha(a->str[count_a]) && isalpha(b->str[count_b])) 
        {
            if (a->str[count_a] > b->str[count_b])
                return 1;

            if (a->str[count_a] < b->str[count_b])
                return -1;

            ++count_a;
            ++count_b;
        }
        else
        {
            while (!isalpha(a->str[count_a]))
                count_a++;

            while (!isalpha(b->str[count_b]))
                count_b++;
        }

        if (count_a > a->len && count_b > b->len)
            return 0;
        if (count_a > a->len)
            return -1;
        if (count_b > b->len)
            return 1;

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

#include "strcmp.h"

void CreateText(Text* file, char* filename)
{
    CreateBuffer(&file->buffer, filename, &file->size);
    file->lines = CountString(file->buffer);
    file->strings = (line*)calloc(file->lines + 1, sizeof(line));
    GainString(file->buffer, file->strings);
}

void CreateBuffer(char** buffer, char* filename, int* size)
{
    FILE* hamlet = fopen(filename, "r");
    assert(hamlet);

    *size = CountSize(hamlet);
    *buffer = (char*)calloc(*size, sizeof(char));
    
    Copy(*buffer, hamlet);
    fclose(hamlet);
}

void PrintInFile(const line* temp, FILE* file)
{
    while (temp->str != nullptr)
    {
        fprintf(file, "%s\n", temp->str);
        ++temp;
    }

}

void GainString(char* buffer, line* strings)
{
    strings->str = buffer;
    char* cur_str = buffer;
    char* next_str = strchr(buffer, '\n');
    while (next_str != nullptr)
    {
        *next_str = '\0';

        next_str++;
        strings->len = next_str - cur_str - 1;

        strings++;
        strings->str = next_str;

        cur_str = next_str;
        next_str = strchr(next_str, '\n');
    }
}

void Copy(char* storage, FILE* file)
{
    assert(storage);
    assert(file);

    int param = CountSize(file);
    fread(storage, sizeof(char), param, file);
}

int CompareRight(const line* a, const line* b)
{

    int count_a = a->len - 1,
        count_b = b->len - 1;

    while(((lang)a->str[count_a] == (lang)b->str[count_b]) && (0 < count_a) && (0 < count_b)){
        
        --count_a;
        --count_b;

        while((!isalpha((lang)a->str[count_a])) && ((lang)a->str[count_a] != ' ') && (0 < count_a))
            --count_a;
        while((!isalpha((lang)b->str[count_b])) && ((lang)b->str[count_b] != ' ') && (0 < count_b))
            --count_b;
    }

    return ((lang)a->str[count_a] - (lang)b->str[count_b]);
}

int CompareLeft(const line* a, const line* b)
{
    int count_a = 0,
        count_b = 0;

    while(((lang)a->str[count_a] == (lang)b->str[count_b]) && (count_a < a->len) && (count_b < b->len)){
        
        ++count_a;
        ++count_b;

        while((!isalpha((lang)a->str[count_a])) && ((lang)a->str[count_a] != ' ') && ((lang)a->str[count_a] < a->len))
            ++count_a;
        while((!isalpha((lang)b->str[count_b])) && ((lang)b->str[count_b] != ' ') && ((lang)b->str[count_b] < b->len))
            ++count_b;
    }

    return ((lang)a->str[count_a] - (lang)b->str[count_b]);
}

int CountSize(FILE* file)
{
    assert(file);

    int symbols = 0;
    fseek(file, 0, SEEK_END);
    symbols = ftell(file);
    rewind(file);
    return symbols;
}

int CountString(char* buffer)
{
    int count = 1;

    char* tmp_buffer = strchr(buffer, '\n');

    while (tmp_buffer != NULL)
    {
        tmp_buffer = strchr(tmp_buffer + 1, '\n');
        ++count;
    }

    return count;
}

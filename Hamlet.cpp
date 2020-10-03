#include "Onegin.h"

//create buffer
void CreateBuffer(char** buffer, char* argv[1])
{
    FILE* hamlet = fopen(argv[1], "r");
    assert(hamlet);
    
    int size = 0;
    size = CountSize(hamlet);
    *buffer = (char*)calloc(size, sizeof(char));
    
    Copy(*buffer, hamlet);
    fclose(hamlet);
}
//print txt in file
void PrintInFile(const line* temp, FILE* file)
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
    assert(storage);
    assert(file);

    int param = CountSize(file);
    fread(storage, sizeof(char), param, file);
}
//right check
int CompareRight(const line* a, const line* b)
{

    int count_a = a->len,
        count_b = b->len;

    while (count_a >= 0 && count_b >= 0)
    {
        if (isalpha(a->str[count_a]) && isalpha(b->str[count_b]))
        {
            if (a->str[count_a] > b->str[count_b])
                return 1;

            if (a->str[count_a] < b->str[count_b])
                return -1;
            
            --(count_a);
            --(count_b);
        }
        else
        {
            while (!isalpha(a->str[count_a]))
                --(count_a);
            
            while (!isalpha(b->str[count_b]))
                --(count_b);
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
int CompareLeft(const line* a, const line* b)
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
    }

    if (count_a > a->len && count_b > b->len)
        return 0;
    if (count_a > a->len)
        return -1;
    if (count_b > b->len)
        return 1;

    return 0;
}
//num of symbols in file
int CountSize(FILE* file)
{
    assert(file);

    int symbols = 0;
    fseek(file, 0, SEEK_END);
    symbols = ftell(file);
    rewind(file);
    return symbols;
}
//count of strings
int CountString(char* buffer)
{
    int count = 1;

    char* tmp_buffer = strchr(buffer, '\n');

    while (tmp_buffer != NULL) {
        tmp_buffer = strchr(tmp_buffer + 1, '\n');
        ++count;
    }

    return count;
}

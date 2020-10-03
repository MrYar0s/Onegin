#include "Hamlet.h"

int main(int argc, char** argv)
{
    char* buffer = nullptr;
    CreateBuffer(&buffer, argv);
    assert(buffer);

    size_t n_str = CountString(buffer);
    
    line* strings = (line*)calloc(n_str + 1, sizeof(line));

    GainString(buffer, strings);

    assert(strings);
    
    qsort(strings, n_str, sizeof(line), (int(*) (const void*, const void*))CompareRight);

    FILE* sorted1 = fopen("sorted1.txt", "w");
    PrintInFile(strings, sorted1);
    fclose(sorted1);

    qsort(strings, n_str, sizeof(line), (int(*) (const void*, const void*))CompareLeft);
    
    FILE* sorted2 = fopen("sorted2.txt", "w");
    PrintInFile(strings, sorted2);
    fclose(sorted2);

    return 0;
}

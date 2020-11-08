#include "strcmp.h"

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru_RU.cp1251");

    Text file = {0};

    CreateText(&file, argv[1]);

    qsort(file.strings, file.lines, sizeof(line), (int(*) (const void*, const void*))CompareRight);

    FILE* rsort = fopen("sortr.txt", "w");
    PrintInFile(file.strings, rsort);
    fclose(rsort);

    qsort(file.strings, file.lines, sizeof(line), (int(*) (const void*, const void*))CompareLeft);
    
    FILE* lsort = fopen("sortl.txt", "w");
    PrintInFile(file.strings, lsort);
    fclose(lsort);

    return 0;
}
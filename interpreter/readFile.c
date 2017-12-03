#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "readFile.h"

size_t readFile(byte *buf, size_t size, char *pathname) {
    FILE *file;

    file = fopen(pathname, "r");
    if (!file) {
        return 0;
    }

    size = fread(buf, 1, size, file);
    if (ferror(file)) {
        fclose(file);
        return 0;
    }

    fclose(file);

    return size;
}

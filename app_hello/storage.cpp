#include "mbed.h"
#include "storage.h"

SDIOBlockDevice bd;
FATFileSystem fs("sda", &bd);

void print_dir(FileSystem *fs, const char* dirname) {
    Dir dir(fs, dirname);
    struct dirent ent;

    // dir.open(fs, dirname);
    printf("contents of //%s/%s\n", fs->getName(), dirname);
    printf("----------------------------------------------------\n");

    while (1) {
        size_t res = dir.read(&ent);
        if (0 == res) {
            break;
        }
        printf(ent.d_name);
        printf("\n");
    }
    dir.close();
}


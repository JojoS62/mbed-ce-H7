#include "mbed.h"
#include "storage.h"

SDIOBlockDevice bd;
FATFileSystem fs("sda");
USBMSD msd(&bd);
Thread USBThread(osPriorityBelowNormal, 2048, NULL, "USBThread");

void USBTask() {
    while (1) {
        msd.process();
        // ThisThread::sleep_for(10ms);
    }
}

int init_storage() {
    int err = 0;
    fs.unmount();
    err = fs.mount(&bd);

    USBThread.start(USBTask);

    return err;
}

void print_dir(FileSystem *fs, const char* dirname) {
    Dir dir(fs, dirname);
    struct dirent ent;

    dir.open(fs, dirname);
    printf("contents of //%s%s\n", fs->getName(), dirname);
    printf("----------------------------------------------------\n");
    fflush(stdout);

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


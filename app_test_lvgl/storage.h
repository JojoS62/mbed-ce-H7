#pragma once

#include "SDIOBlockDevice.h"
#include "FATFileSystem.h"
#include "USBMSD.h"

extern SDIOBlockDevice bd;
extern FATFileSystem fs;

int init_storage();
void print_dir(FileSystem *fs, const char* dirname);

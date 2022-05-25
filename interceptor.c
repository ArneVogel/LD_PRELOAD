#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

ssize_t (*_write)(int fildes, const void *buf, size_t nbyte);

ssize_t write(int fildes, const void *buf, size_t nbyte) {
    printf("intercepted [write] to %d, %d bytes\n", fildes, nbyte);

    if(!_write) _write = dlsym(RTLD_NEXT, "write");
    return _write(fildes, buf, nbyte);
}


ssize_t (*_read)(int fildes, void *buf, size_t nbyte);

ssize_t read(int fildes, void *buf, size_t nbyte) {
    printf("intercepted [read] from %d, %d bytes\n", fildes, nbyte);

    if(!_read) _read = dlsym(RTLD_NEXT, "read");
    return _read(fildes, buf, nbyte);

}

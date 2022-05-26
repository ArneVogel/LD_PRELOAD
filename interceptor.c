#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <sys/socket.h>
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


int (*_connect)(int socket, const struct sockaddr *address,
           socklen_t address_len);


int connect(int socket, const struct sockaddr *address,
           socklen_t address_len) {
    printf("intercepted [connect] to %d\n", socket);

    if(!_connect) {
        _connect = dlsym(RTLD_NEXT, "connect");
    }
    return _connect(socket, address, address_len);
}


int (*_sentto)(int socket, const struct sockaddr *address,
           socklen_t address_len);


int sentto(int socket, const struct sockaddr *address,
           socklen_t address_len) {
    printf("intercepted [sentto] to %d\n", socket);

    if(!_sentto) {
        _sentto = dlsym(RTLD_NEXT, "sentto");
    }
    return _sentto(socket, address, address_len);
}



// https://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html
// gcc -o dl1 dl1.c -ldl
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
    void *handle;
    void* (*pmalloc)(int);
    char *error;

    // handle = dlopen ("/lib/libm.so.6", RTLD_LAZY);
    handle = dlopen (0, RTLD_LAZY);
    printf("handle=%p\n", handle);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }

    pmalloc = dlsym(handle, "malloc");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }

    char *m=(*pmalloc)(100);
    printf("m=%p\n", m);
    dlclose(handle);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#define SHAREDNAME "/shared"
int main(){
    int shm_fd;
    void * ptr;
    shm_fd=shm_open(SHAREDNAME,O_CREAT|O_RDWR,0666);
    ftruncate(shm_fd,4096);
    ptr=mmap(0,4096,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
    fgets((char*)ptr,1000,stdin);
    printf("%s",(char*) ptr);
    close(shm_fd);
    return 0;
}
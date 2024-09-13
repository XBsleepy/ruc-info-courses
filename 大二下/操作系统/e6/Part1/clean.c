#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#define SHM_NAME "/shared"
#define WRITER_SEM "/writer_sem"
#define READER_SEM "/rd"
#define READER_COUNT "/c"
#define TEXT_SIZE 256
typedef struct {
    char text[TEXT_SIZE];
} SharedData;
int main(){
    sem_t *writer_sem = sem_open(WRITER_SEM, O_CREAT, 0666, 1);
    sem_close(writer_sem);
    sem_unlink(WRITER_SEM);
    sem_t *reader_sem = sem_open(READER_SEM, O_CREAT, 0666, 1);
    sem_close(reader_sem);
    sem_unlink(READER_SEM);
    sem_t *reader_count_sem = sem_open(READER_COUNT, O_CREAT, 0666, 0);
    sem_close(reader_count_sem);
    sem_unlink(READER_COUNT);
    shm_unlink(SHM_NAME);
    return 0;
}
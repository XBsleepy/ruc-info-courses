#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#define SHM_NAME "/shared"
#define WRITER_SEM "/writer_sem"
#define READER_COUNT "/c"
#define READER_SEM "/rd"
#define TEXT_SIZE 256

typedef struct {
    char text[TEXT_SIZE];
} SharedData;

int main() {
    // 打开读者互斥信号量
    sem_t *reader_sem = sem_open(READER_SEM, O_CREAT, 0666, 1);


    sem_wait(reader_sem);
    // 打开读者计数信号量
    sem_t *reader_count_sem = sem_open(READER_COUNT,O_CREAT|O_RDWR, 0666, 0);
    if (reader_count_sem == SEM_FAILED) {
        perror("sem_open (reader_count)");
        exit(EXIT_FAILURE);
    }

    // 读者计数加1
    int *reader_count_ptr;
    int reader_count = 0;
    reader_count_ptr = &reader_count;
    if (sem_getvalue(reader_count_sem, reader_count_ptr) == -1) {
        perror("sem_getvalue (reader_count)");
        exit(EXIT_FAILURE);
    }        
    // 如果是第一个读者，就阻塞写者
    if (reader_count == 0) {
        sem_t *writer_sem = sem_open(WRITER_SEM, O_CREAT, 0666, 1);
    if (writer_sem == SEM_FAILED) {
        perror("sem_open (writer)");
        exit(EXIT_FAILURE);
    }
        // printf("1\n");
        if (sem_wait(writer_sem) == -1) {
            perror("sem_wait (writer)");
            exit(EXIT_FAILURE);
        }
    }
    // 读者计数信号量加1
    if (sem_post(reader_count_sem) == -1) {
        perror("sem_post (reader_count)");
        exit(EXIT_FAILURE);
    }
    sem_post(reader_sem);
    // 打开共享内存对象
    int shm_fd = shm_open(SHM_NAME, O_RDONLY|O_CREAT, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    // printf("!\n");
    // 映射共享内存到进程地址空间
    SharedData *shared_data = (SharedData *)mmap(NULL, sizeof(SharedData), PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }


    // 打印共享内存中的数据
    printf("Reader%d : %s\n",getpid(), shared_data->text);
    sem_wait(reader_sem);
    // 读者计数减1
    if (sem_wait(reader_count_sem) == -1) {
        perror("sem_wait (reader_count)");
        exit(EXIT_FAILURE);
    }

    // 释放读者计数互斥信号量
    sem_getvalue(reader_count_sem,reader_count_ptr);
    // 检查是否还有其他读者，如果没有则释放写者信号量
    if (*reader_count_ptr == 0) {
        sem_t *writer_sem = sem_open(WRITER_SEM, O_CREAT, 0666, 1);
    if (writer_sem == SEM_FAILED) {
        perror("sem_open (writer)");
        exit(EXIT_FAILURE);
    }
        if (sem_post(writer_sem) == -1) {
            perror("sem_post (writer)");
            exit(EXIT_FAILURE);
        }
    }

    if (sem_post(reader_sem) == -1) {
        perror("sem_post (reader_count)");
        exit(EXIT_FAILURE);
    }
    return 0;
}

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
#define TEXT_SIZE 256

typedef struct {
    char text[TEXT_SIZE];
} SharedData;
void generate_random_string(char *str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int charset_size = strlen(charset);
    srand((unsigned int)getpid());
    // 生成随机字符串
    for (int i = 0; i < length - 1; ++i) {
        int index = rand() % charset_size;
        str[i] = charset[index];
    }
    str[length - 1] = '\0'; // 字符串结尾

    // 添加 PID 到字符串末尾
    pid_t pid = getpid();
    char pid_str[20];
    sprintf(pid_str, " by writer: %d", pid);
    strcat(str, pid_str);
}

int main() {
    sem_t *writer_sem = sem_open(WRITER_SEM, O_CREAT, 0666, 1);
    if (writer_sem == SEM_FAILED) {
        perror("sem_open (writer)");
        exit(EXIT_FAILURE);
    }
     if (sem_wait(writer_sem) == -1) {
        perror("sem_wait (writer)");
        exit(EXIT_FAILURE);
    }
    // 创建共享内存对象
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, sizeof(SharedData));
    // 映射共享内存到进程地址空间
    SharedData *shared_data = (SharedData *)mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    generate_random_string(shared_data->text,10);
    if (sem_post(writer_sem) == -1) {
    perror("sem_post (writer)");
    exit(EXIT_FAILURE);
    }
    return 0;
}

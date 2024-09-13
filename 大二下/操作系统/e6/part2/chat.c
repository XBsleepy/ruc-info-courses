#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define MSG_SIZE 1235
#define MSG_KEY 1234

// 定义消息结构体
struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

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
     pid_t pid = getpid();
    char pid_str[20];
    sprintf(pid_str, " by writer: %d", pid);
    strcat(str, pid_str);
}

int main() {
    int msg_id;
    struct msg_buffer message;
    pid_t pid = getpid();

    // 创建或获取消息队列
    msg_id = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msg_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // 生成随机消息
    generate_random_string(message.msg_text, 10);
    // 设置消息类型为 1
    message.msg_type = 1;
    // 发送消息到队列
    if (msgsnd(msg_id, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    sleep(1);
    // printf("Process (PID %d) sent message: %s\n", pid, message.msg_text);
    struct msg_buffer rmessage;
    if (msgrcv(msg_id, &rmessage, sizeof(rmessage), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    } else {
        printf("PID %d received message : %s\n", getpid(), rmessage.msg_text);
    }
    return 0;
}

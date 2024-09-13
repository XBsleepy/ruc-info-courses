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
int main(){
    key_t msgid=msgget(MSG_KEY,0666);
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}
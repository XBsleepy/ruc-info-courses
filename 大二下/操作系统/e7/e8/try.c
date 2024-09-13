#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<stdbool.h>

#define MAX_USER 100         // 最大用户数
#define MAX_DISK 512*1024    // 最大磁盘大小
#define BLOCK_SIZE 512       // 块大小

char disk[MAX_DISK];         // 磁盘数组

// 磁盘块结构体
typedef struct disk_block {
    int startpos;            // 起始位置
    int useFlag;             // 使用标志
    struct disk_block *next; // 指向下一个块的指针
} diskNode;

diskNode *diskHead;          // 磁盘头指针

// 文件表结构体
typedef struct fileTable {
    char filename[10];       // 文件名
    int startpos;            // 起始位置
    int length;              // 文件长度
    int maxlength;           // 文件最大长度
    char fileKind[4];        // 文件权限
    struct tm *timeinfo;     // 文件创建时间
    struct fileTable *next;  // 指向下一个文件的指针
    bool openFlag;           // 文件是否打开标志
} fileTable;

// 用户目录结构体
typedef struct userDirectory {
    struct fileTable *file;     // 指向文件的指针
    struct userDirectory *next; // 指向下一个用户目录的指针
} UFD;

// 主目录结构体
typedef struct masterDirectory {
    char username[10];     // 用户名
    char password[10];     // 密码
    UFD *user;             // 用户目录指针
} MFD;

MFD userTable[MAX_USER];   // 用户表
MFD *currentUser;          // 当前用户指针
int userNum = 0;           // 用户数量
int posTable[1024];        // 磁盘位置表

// 函数声明
void fileCreate(char fileName[], int length, char fileKind[]);
void fileWrite(char fileName[]);
void fileCat(char fileName[]);
void fileRename(char fileName[], char newFileName[]);
void fileDir();
void fileClose(char fileName[]);
void fileDelete(char fileName[]);
void initDisk();
void chomd(char fileName[], char mode[]);
int requestDisk(int length);
void freeDisk(int startPos, int length);
void userCreate(char username[], char password[]);
void userDelete(char username[]);
void userLogin(char username[], char password[]);
void userlogout();
void initDisk();
void showDisk();
void showUser();
int commandAnalysis(char command[]);

int main(){
    initDisk();
    printf("Welcome to the file system!input 'help' to get help,'exit' to quit.\n");
    char command[20];
    while(1){
        printf(">>");
        scanf("%s",command);
        if(strcmp(command,"exit")==0){
            break;
        }
        commandAnalysis(command);
    }
    printf("Bye!\n");
    return 0;
}

int  commandAnalysis(char command[]){
    if(strcmp(command,"help")==0){
        printf("fcrt:Create a file\n");
        printf("write:Write a file\n");
        printf("cat:Read a file\n");
        printf("rename:Rename a file\n");
        printf("dir:Show the file list\n");
        printf("close:Close a file\n");
        printf("delete:Delete a file\n");
        printf("chomd:Change the authority of a file\n");
        printf("showDisk:Show the disk status\n");
        printf("showUser:Show the user list\n");
        printf("ucrt:Create a user\n");
        printf("userDelete:Delete a user\n");
        printf("login:Login\n");
        printf("logout:Logout\n");
    }
    else if(strcmp(command,"fcrt")==0){
        if(currentUser==NULL){
            printf("Please login first!\n");
            return -1;
        }
        printf("Please input the filename:");
        char fileName[10];
        scanf("%s",fileName);
        printf("Please input the length:");
        int length;
        scanf("%d",&length);

        char fileKind[4];

        while(1){
        printf("Please input the authority(rwx):");
        scanf("%s",fileKind);
        int flag=0;
        for(int i=0;i<3;i++){
            if(fileKind[i]!='0'&&fileKind[i]!='1'){
                printf("Invalid authority!\n");
                flag=1;
                break;
            }
        }
        if(flag==0)
        break;
        }
        fileCreate(fileName,length,fileKind);  
}
    else if(strcmp(command,"write")==0){
        printf("Please input the filename:");
        char fileName[10];
        scanf("%s",fileName);
        fileWrite(fileName);
    }
    else if(strcmp(command,"cat")==0){
        printf("Please input the filename:");
        char fileName[10];
        scanf("%s",fileName);
        fileCat(fileName);
    }
    else if(strcmp(command,"rename")==0){
        printf("Please input the filename:");
        char fileName[10];
        scanf("%s",fileName);
        printf("Please input the new filename:");
        char newFileName[10];
        scanf("%s",newFileName);
        fileRename(fileName,newFileName);
    }
    else if(strcmp(command,"dir")==0){
        fileDir();
    }
    else if(strcmp(command,"close")==0){
        printf("Please input the filename:");
        char fileName[10];
        scanf("%s",fileName);
        fileClose(fileName);
    }
    else if(strcmp(command,"delete")==0){
        printf("Please input the filename:");
        char fileName[10];
        scanf("%s",fileName);
        fileDelete(fileName);}
    else if(strcmp(command,"chomd")==0){
        printf("Please input the filename:");
        char fileName[10];
        scanf("%s",fileName);
        char mode[4];
        while(1){
            printf("Please input the authority(rwx):");
            scanf("%s",mode);
            int flag=0;
            for(int i=0;i<3;i++){
                if(mode[i]!='0'&&mode[i]!='1'){
                    printf("Invalid authority!\n");
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            break;
        }
        chomd(fileName,mode);
    }
    else if(strcmp(command,"showDisk")==0){
        showDisk();
    }
    else if(strcmp(command,"showUser")==0){
        showUser();
    }
    else if(strcmp(command,"ucrt")==0){
        printf("Please input the username:");
        char username[10];
        scanf("%s",username);
        printf("Please input the password:");
        char password[10];
        scanf("%s",password);
        userCreate(username,password);
    }
    else if(strcmp(command,"userDelete")==0){
        printf("Please input the username:");
        char username[10];
        scanf("%s",username);
        userDelete(username);
    }
    else if(strcmp(command,"login")==0){
        printf("Please input the username:");
        char username[10];
        scanf("%s",username);
        printf("Please input the password:");
        char password[10];
        scanf("%s",password);
        userLogin(username,password);
    }
    else if(strcmp(command,"logout")==0){
        userlogout();
    }
    else{
        printf("Invalid command!\n");
    }
    return -1;
}
void initDisk(){
    diskHead=(diskNode*)malloc(sizeof(diskNode));
    diskHead->startpos=0;
    diskHead->useFlag=0;
    diskHead->next=NULL;
    for(int i=0;i<MAX_DISK;i++){
        disk[i]='0';
    }
    for(int i=0;i<MAX_USER;i++){
        userTable[i].user=NULL;
    }
}
void userCreate(char username[],char password[]){
    if(userNum>=MAX_USER){
        printf("The user table is full!\n");
        return;
    }
    for(int i=0;i<MAX_USER;i++){
        if(userTable[i].user!=NULL){
            if(strcmp(userTable[i].username,username)==0){
                printf("The user already exists!\n");
                return;
            }
        }
    }
    for(int i=0;i<MAX_USER;i++){
        if(userTable[i].user==NULL){
            userTable[i].user=(UFD*)malloc(sizeof(UFD));
            userTable[i].user->file=NULL;
            userTable[i].user->next=NULL;
            strcpy(userTable[i].username,username);
            strcpy(userTable[i].password,password);
            userNum++;
            printf("User %s created successfully!\n",username);
            return;
        }
    }
}
void userDelete(char username[]){
    if(currentUser!=NULL){
        printf("Please logout first!\n");
        return;
    }
    for(int i=0;i<MAX_USER;i++){
        if(strcmp(userTable[i].username,username)==0){
            free(userTable[i].user);//tocheck
            userTable[i].user=NULL; 
            userNum--;
            printf("User %s deleted successfully!\n",username);
            currentUser=NULL;
            return;
        }
    }
    printf("User %s not found!\n",username);
}
void userLogin(char username[],char password[]){
    for(int i=0;i<MAX_USER;i++){
        if(strcmp(userTable[i].username,username)==0){
            if(strcmp(userTable[i].password,password)==0){
                printf("Login successfully!\n");
                currentUser=&userTable[i];
                return;
            }
            else{
                printf("Password error!\n");
                return;
            }
        }
    }
    printf("User not found!\n");
}
void userlogout(){
    currentUser=NULL;
}
void fileCreate(char fileName[],int length,char fileKind[]){
    if(currentUser==NULL){
        printf("Please login first!\n");
        return;
    }
    UFD *user=currentUser->user;
    fileTable *file=user->file;
    while(file!=NULL){
        if(strcmp(file->filename,fileName)==0){
            printf("The file already exists!\n");
            return;
        }
        file=file->next;}

    int startPos=requestDisk(length);
    if(startPos==-1){
        printf("No enough space!\n");
        return;
    }

    fileTable *newFile=(fileTable*)malloc(sizeof(fileTable));
    strcpy(newFile->filename,fileName);
    newFile->startpos=startPos;
    newFile->maxlength=length;
    time_t t;
    time(&t);
    char tempauthority[4]="111";
    strcpy(newFile->fileKind,tempauthority);
    newFile->timeinfo=localtime(&t);
    newFile->next=NULL;
    newFile->openFlag=false;
    file=user->file;
    if(user->file==NULL){
        user->file=newFile;
    }
    else{
        file=user->file;
        while(file->next!=NULL){
            file=file->next;
        }
        file->next=newFile;
    }
    printf("File %s created successfully!\n",fileName);
    fileWrite(fileName);
    strcpy(newFile->fileKind,fileKind);
}
void fileWrite(char fileName[]){
    if(currentUser==NULL){
        printf("Please login first!\n");
        return;
    }
    UFD *user=currentUser->user;
    fileTable *file=user->file;
    while(file!=NULL){
        if(strcmp(file->filename,fileName)==0){
            if(file->openFlag==true){
                printf("The file is already open!\n");
                return;
            }
            if(file->fileKind[1]!='1'){
                printf("You don't have the write authority!\n");
                return;
            }
            file->openFlag=true;
            printf("Please input the content:");
            char content[1000];
            scanf("%s",content);
            int length=strlen(content);
            if(length>file->maxlength){
                printf("The content is too long!\n");
                file->openFlag=false;
                return;
            }
            for(int i=0;i<length;i++){
                disk[file->startpos+i]=content[i];
            }
            file->length=length;
            printf("Write successfully!\n");
            file->openFlag=false;
            return;
        }

        file=file->next;
    }
    printf("File not found!\n");
}
void fileCat(char fileName[]){
    if(currentUser==NULL){
        printf("Please login first!\n");
        return;
    }
    UFD *user=currentUser->user;
    fileTable *file=user->file;
    while(file!=NULL){
        if(strcmp(file->filename,fileName)==0){
            if(file->openFlag==true){
                printf("The file is already open!\n");
                return;
            }
            if(file->fileKind[0]!='1'){
                printf("You don't have the read authority!\n");
                return;
            }
            file->openFlag=true;
            for(int i=0;i<file->length;i++){
                printf("%c",disk[file->startpos+i]);
            }
            printf("\n");
            file->openFlag=false;
            return;
        }
        file=file->next;
    }
    printf("File not found!\n");
}
void fileRename(char fileName[],char newFileName[]){
    if(currentUser==NULL){
        printf("Please login first!\n");
        return;
    }
    UFD *user=currentUser->user;
    fileTable *file=user->file;
    while(file!=NULL){
        if(strcmp(file->filename,fileName)==0){
            strcpy(file->filename,newFileName);
            printf("Rename successfully!\n");
            return;
        }
        file=file->next;
    }
    printf("File not found!\n");
}
void fileClose(char fileName[]){
    if(currentUser==NULL){
        printf("Please login first!\n");
        return;
    }
    UFD *user=currentUser->user;
    fileTable *file=user->file;
    while(file!=NULL){
        if(strcmp(file->filename,fileName)==0){
            if(file->openFlag==false){
                printf("The file is not open!\n");
                return;
            }
            file->openFlag=false;
            printf("Close successfully!\n");
            return;
        }
        file=file->next;
    }
    printf("File not found!\n");
}
void fileDelete(char fileName[]){
    if(currentUser==NULL){
        printf("Please login first!\n");
        return;
    }
    UFD *user=currentUser->user;
    fileTable *file=user->file;
    fileTable *preFile=NULL;
    while(file!=NULL){
        if(strcmp(file->filename,fileName)==0){
            if(file->openFlag==true){
                printf("The file is open!\n");
                return;
            }
            file->openFlag=true;
            if(preFile==NULL){
                user->file=file->next;
            }
            else{
                preFile->next=file->next;
            }
            freeDisk(file->startpos,file->maxlength);
            printf("Delete successfully!\n");
            file->openFlag=false;
            return;
        }
        preFile=file;
        file=file->next;
    }
    printf("File not found!\n");
}
int requestDisk(int length){
    int blockNum=length/BLOCK_SIZE+(!!(length%BLOCK_SIZE));
    for(int i=0;i<1024;i++){
        int pos=i;
        if(posTable[i]==0){
            int j=0;
            for(j=0;j<blockNum;j++){
                if(posTable[i+j]==1){
                    break;
                }
            }
            if(j==blockNum){
                for(int k=0;k<blockNum;k++){
                    posTable[i+k]=1;
                }
                return i*BLOCK_SIZE;
            }
            i+=j;
        }
    }
    return -1;
    }
void freeDisk(int startPos,int length){
    int blockNum=length/BLOCK_SIZE+(!!(length%BLOCK_SIZE));
    for(int i=0;i<blockNum;i++){
        i+=startPos/BLOCK_SIZE;
        posTable[i]=0;
    }
}
void showDisk(){
    for(int i=0;i<1024;i++){
        printf("%d",posTable[i]);
    }
    printf("\n");
}
void showUser(){
    for(int i=0;i<MAX_USER;i++){
        if(userTable[i].user!=NULL){
            printf("Username:%s\n",userTable[i].username);
        }
    }
}
void chomd(char fileName[],char mode[]){
    if(currentUser==NULL){
        printf("Please login first!\n");
        return;
    }
    UFD *user=currentUser->user;
    fileTable *file=user->file;
    while(file!=NULL){
        if(strcmp(file->filename,fileName)==0){
            strcpy(file->fileKind,mode);
            printf("Change mode successfully!\n");
            return;
        }
        file=file->next;
    }
    printf("File not found!\n");
}
void fileDir(){
    if(currentUser==NULL){
        printf("Please login first!\n");
        return;
    }
    UFD *user=currentUser->user;
    fileTable *file=user->file;
    while(file!=NULL){
        printf("Filename:%s ",file->filename);
        printf("Startpos:%d ",file->startpos);
        printf("Maxlength:%d ",file->maxlength);
        printf("Length:%d ",file->length);
        printf("Mode:%s ",file->fileKind);
        printf("Time:%s\n",asctime(file->timeinfo));
        file=file->next;
    }
}

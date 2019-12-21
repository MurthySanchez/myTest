#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "sys/shm.h"

#include "shm_com.h"

int main(){
     /*create shared memory*/
    int running=1;
    void *shared_memory=(void *)0;
    struct shared_use_st *shared_stuff;
    char buffer[BUFSIZ];
    int shmid;

    srand((unsigned int)getgid());

    shmid=shmget((key_t)1234,sizeof(struct shared_use_st),0666 | IPC_CREAT);

    if(shmid == -1){
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    /*visit shared memory*/
    shared_memory=shmat(shmid, (void *)0, 0);
    if(shared_memory == (void *)-1){
        fprintf(stderr,"shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n",(int)shared_memory);

    /*put shared_memory to shared_stuff, output written_by_you*/
    shared_stuff=(struct shared_use_st *)shared_memory;
    while (running)
    {
        while(shared_stuff->written_by_you == 1){
            sleep(1);
            printf("Waiting for client...\n");
        }
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);

        strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
        shared_stuff->written_by_you=1;
       
        if (strncmp(shared_stuff->some_text, "end", 3)==0)
        {
            running=0;
        }
            
    }

    /*dis and del*/
    if(shmdt(shared_memory)==-1){
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    if(shmctl(shmid, IPC_RMID, 0)==-1){
        fprintf(stderr, "shmctl (IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <auo/busx.h>
#include <iostream>

// 2017/12/20 Kevin

#include <stdlib.h>

#include "manager.h"
#include "home.h"


using namespace std;


#define DISABLE_BUSX    0

#define UNUSED(x) (void)x
#define STRNCMP(a,b)    strncmp(a, b, strlen(b))

typedef struct {
    pthread_t thread_id;
    BUSX_ATTR_t *attr;
    char name[16];
    char nickname[16];
    char to[16];
    bool write;
    bool deamon;
    bool alive;
} SDATA;

static SDATA sdata;


static void f_sdata_init()
{
    sdata.thread_id = -1;
    sdata.attr = NULL;
    sdata.name[0] = 0;
    sdata.nickname[0] = 0;
    strcpy(sdata.to, "BASE00");
    sdata.write = false;
    sdata.deamon = false;
    sdata.alive = true;


    if (manager_init() == -1)
    {
        printf("%s > error!\n", __func__);
        exit(0);
    }
}

static void f_usage()
{
    printf("example: qsid_busx -b bus -n nickname -t target -w -d\n>");
}

static void f_arg_proc(int argc, char *argv[])
{
    int c;

    while((c=getopt(argc, argv, "b:n:t:x:whd?")) != -1)
    {
        //printf("opt:%c\n", c);
        switch(c)
        {
        case 'b':
            strncpy(sdata.name, (char*)optarg, sizeof(sdata.name));
            break;
        case 'n':
            strncpy(sdata.nickname, (char*)optarg, sizeof(sdata.nickname));
            break;
        case 't':
            strncpy(sdata.to, (char*)optarg, sizeof(sdata.to));
            break;
        case 'w':
            sdata.write = true;
            break;
        case 'd':
            sdata.deamon = true;
            break;
        case 'h':
        case '?':
            f_usage();
            exit(0);
            break;
        }
    }
}








static void f_callback_recv(void *obj, char *from, char* data, size_t len)
{
    UNUSED(obj);

    if (STRNCMP(from , "gui0") == 0)
    {

    }
    else if (STRNCMP(from , "soc") == 0)
    {


        home_handle_ipc(from, data, len);



    }
    else if (STRNCMP(from , "abc") == 0)
    {
        refresh(NULL,NULL,data,len);
    }
    printf("%s < %s (%d): ", sdata.name, from, len);

    for (size_t i = 0; i < len; i++) printf("%02x ", data[i]); printf("\n> ");
}

static void loop()
{
    while(sdata.alive)
    {
        manager_loop();
    }
}


uint hex2int(unsigned char hex_ch)
{
    if (hex_ch >= '0' && hex_ch <= '9')
    {
        return hex_ch - '0';
    }

    if (hex_ch >= 'a' && hex_ch <= 'f')
    {
        return hex_ch - 'a' + 10;
    }

    if (hex_ch >= 'A' && hex_ch <= 'F')
    {
        return hex_ch - 'A' + 10;
    }

    return 0x00;
}


void input_parser(char *line)
{
    char * pch;
    char to[32];

    char buf[4096];
    unsigned short len;

    pch = strchr(line,',');

    if (pch == NULL) {
        printf("invalid format!!!\n");
        return;
    }
    else {
        pch++;
    }

    memset(to, 0x00, sizeof(to));
    strncpy(to, line, pch-line-1);

    memset(buf, 0x00, sizeof(buf));

    if ((!STRNCMP(pch, "0x")) || (!STRNCMP(pch, "0X")))
    {
        pch+=2;
        len = strlen(pch)/2;

        for (size_t i= 0; i < strlen(pch); )
        {
            buf[i/2] = hex2int(pch[i]) << 4 | hex2int(pch[i+1]);
            i+=2;
        }
    }
    else
    {
        len = strlen(pch);
        strncpy((char*)buf, pch, len);
    }

    int ret;

    ret = busx_write(sdata.attr, to, buf, len);

    if (ret != -1)
    {
        printf("%s > %s (%d): ", sdata.name, to, len);
        for (int i = 0; i < len; i++) printf("%02x ", buf[i]); printf("\n");
    }
    else
    {
        printf("%s > %s (%d): fail\n", sdata.name, to, len);
    }
}


static void *keyboard(void *argu)
{
    UNUSED(argu);

    char *l;

    rl_bind_key('\t',rl_abort); //disable auto-complete

    while(((l = readline("> "))!=NULL) && (sdata.alive == true))
    {
        if (STRNCMP(l , "quit") == 0)
        {
            sdata.alive = false;
            break;
        }
        else if (STRNCMP(l , "help") == 0)
        {
            f_usage();
        }
        else if (STRNCMP(l , "test") == 0)
        {
            char buf[256];
            for (size_t i = 0;  i< sizeof(buf); i++) buf[i] = i;
            int ret = busx_write(sdata.attr, (char*)"aaa", buf, sizeof(buf));

            printf("ret:%d\n", ret);
        }
        else
        {
            input_parser(l);
        }


        if (l[0] != 0)
        {
            add_history(l);
        }
    }

    free(l);

    sdata.thread_id = -1;

    return NULL;
}



static void f_SIGINT(int dunno)
{
    UNUSED(dunno);

    printf("f_SIGINT(%d)...\n", dunno);
    sdata.alive = false;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, f_SIGINT);
    signal(SIGTERM, f_SIGINT);
    signal(SIGKILL, f_SIGINT);

    f_sdata_init();
    f_arg_proc(argc, argv);

    printf("a:1\n");


#if (DISABLE_BUSX==0)
    sdata.attr = busx_create(sdata.name, NULL, f_callback_recv);

    if (sdata.attr == NULL)
    {
        printf("busx_create fail!\n");
        return -1;
    }
#endif

    if (sdata.deamon == false)
    {
        pthread_create(&sdata.thread_id, NULL, &keyboard, NULL);
        //        pthread_create(&sdata.thread_id, NULL, &handle_input, NULL);
    }

    printf("a:2\n");


    loop();

    printf("a:1\n");

    if (sdata.thread_id != (pthread_t)-1)
    {
        pthread_join(sdata.thread_id, NULL);
    }

#if (DISABLE_BUSX==0)
    busx_destory(sdata.attr);
#endif

    manager_deinit();
}

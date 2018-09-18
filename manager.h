#ifndef MANAGER_H
#define MANAGER_H

#define SCREEN_HEIGHT       480
#define SCREEN_WIDTH        800
#define SCREEN_BPP          32


typedef enum {
    e_page_home   = 0,
    e_page_sport  = 1,
    e_page_max


} e_page;

int  manager_init();
void manager_deinit();

void manager_loop();

e_page manager_current_page();
bool manager_is_demo();


//kevin 2018/01/23
void refresh(void* obj, char *from, char* data, unsigned long len);
#endif // MANAGER_H

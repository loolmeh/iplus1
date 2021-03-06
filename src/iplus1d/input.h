#ifndef _INPUT_H_
#define _INPUT_H_

typedef enum command_type_t  {
    CMD_SENTENCE,
    CMD_LINK,
    CMD_ANKIBEGIN,
    CMD_ANKICARD,
    CMD_ANKIEND,
    CMD_QUIT,
} command_type_t;


typedef struct command_t {
    command_type_t type;
    int fd;
    union {
        struct {
            int id;
            char lang[4];
            char* sen;
        } sen;
        struct {
            int64_t id;
            int64_t tid;
            char lang[4];
            char tlang[4];
        } link;
        struct {
            char nlang[4];
            char tlang[4];
        } ankibegin;
        struct {
            char* text;
        } anki;
    };
    
} command_t;







typedef struct input_t {
    int running;
    int epoll_fd;
    int listen_fd;
    
    int (*callback)(command_t*, void*);
    void* callback_param;
    
} input_t;




int input_init(input_t*);
int input_destroy(input_t*);
int input_set_callback(input_t*, int (*func)(command_t*, void*), void*);
int input_loop(input_t*);


int command_destroy(command_t*);


























#endif /* _INPUT_H_ */

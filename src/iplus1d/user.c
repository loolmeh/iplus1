#include <stdlib.h>
#include <string.h>
#include "user.h"





int user_init(user_t* user, int fd, char* nl, char* tl)
{
    user->fd = fd;
    user->nlang = iplus1_get_lang(nl);
    user->tlang = iplus1_get_lang(tl);
    if (user->tlang == NULL || user->tlang == NULL) {
        return -1;
    }
    
    iplus1_tree_init(&user->words, iplus1_tree_compare_str);
    return 0;
}

int user_destroy(user_t* user)
{
    iplus1_tree_foreach_postorder(&user->words, iplus1_tree_free_key, NULL);
    iplus1_tree_destroy(&user->words);
    return 0;
}

int user_add_word(user_t* user, char* word)
{
    if (iplus1_tree_get(&user->words, word)) {
        return 1;
    }
    
    char* w = strdup(word);
    iplus1_tree_insert(&user->words, w, w);
    return 0;
}

int user_has_word(user_t* user, char* word)
{
    return !(iplus1_tree_get(&user->words, word) == NULL);
}

int user_tree_free(void* key, void* user, void* param)
{
    user_destroy((user_t*)user);
    free(user);
    return 0;
}

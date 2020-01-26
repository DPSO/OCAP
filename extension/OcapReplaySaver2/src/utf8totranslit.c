
#include <string.h>
#include <stdlib.h>
#include "utf8totranslit.h"

static int utf8toTranslit_checkAllowed(const char* in_buff) {
    static const char* allowed = "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm1234567890-_";
    int allowed_symbols = 0;

    while (*in_buff) {
        const char* a = allowed;
        while (*a) {
            if (*a == *in_buff) {
                goto next;
            }
            a++;
        }
        return allowed_symbols;
    next:
        allowed_symbols++;
        ++in_buff;
    }
    return allowed_symbols;
}


int utf8to_translit(const char* in_buff, char* out_buff) {
    static const char* symbols[][2] = {
        {"\xd0\x99","Y"}, /* � */
        {"\xd0\xb9","y"}, /* � */
        {"\xd0\xa6","Ts"}, /* � */
        {"\xd1\x86","ts"}, /* � */
        {"\xd0\xa3","U"}, /* � */
        {"\xd1\x83","u"}, /* � */
        {"\xd0\x9a","K"}, /* � */
        {"\xd0\xba","k"}, /* � */
        {"\xd0\x95","E"}, /* � */
        {"\xd0\xb5","e"}, /* � */
        {"\xd0\x9d","N"}, /* � */
        {"\xd0\xbd","n"}, /* � */
        {"\xd0\x93","G"}, /* � */
        {"\xd0\xb3","g"}, /* � */
        {"\xd0\xa8","Sh"}, /* � */
        {"\xd1\x88","sh"}, /* � */
        {"\xd0\xa9","Shch"}, /* � */
        {"\xd1\x89","shch"}, /* � */
        {"\xd0\x97","Z"}, /* � */
        {"\xd0\xb7","z"}, /* � */
        {"\xd0\xa5","Kh"}, /* � */
        {"\xd1\x85","kh"}, /* � */
        {"\xd0\xaa",""}, /* � */
        {"\xd1\x8a",""}, /* � */
        {"\xd0\x81","E"}, /* � */
        {"\xd1\x91","e"}, /* � */
        {"\xd0\xa4","F"}, /* � */
        {"\xd1\x84","f"}, /* � */
        {"\xd0\xab","Y"}, /* � */
        {"\xd1\x8b","y"}, /* � */
        {"\xd0\x92","V"}, /* � */
        {"\xd0\xb2","v"}, /* � */
        {"\xd0\x90","A"}, /* � */
        {"\xd0\xb0","a"}, /* � */
        {"\xd0\x9f","P"}, /* � */
        {"\xd0\xbf","p"}, /* � */
        {"\xd0\xa0","R"}, /* � */
        {"\xd1\x80","r"}, /* � */
        {"\xd0\x9e","O"}, /* � */
        {"\xd0\xbe","o"}, /* � */
        {"\xd0\x9b","L"}, /* � */
        {"\xd0\xbb","l"}, /* � */
        {"\xd0\x94","D"}, /* � */
        {"\xd0\xb4","d"}, /* � */
        {"\xd0\x96","Zh"}, /* � */
        {"\xd0\xb6","zh"}, /* � */
        {"\xd0\xad","E"}, /* � */
        {"\xd1\x8d","e"}, /* � */
        {"\xd0\xaf","Ya"}, /* � */
        {"\xd1\x8f","ya"}, /* � */
        {"\xd0\xa7","Ch"}, /* � */
        {"\xd1\x87","ch"}, /* � */
        {"\xd0\xa1","S"}, /* � */
        {"\xd1\x81","s"}, /* � */
        {"\xd0\x9c","M"}, /* � */
        {"\xd0\xbc","m"}, /* � */
        {"\xd0\x98","I"}, /* � */
        {"\xd0\xb8","i"}, /* � */
        {"\xd0\xa2","T"}, /* � */
        {"\xd1\x82","t"}, /* � */
        {"\xd0\xac",""}, /* � */
        {"\xd1\x8c",""}, /* � */
        {"\xd0\x91","B"}, /* � */
        {"\xd0\xb1","b"}, /* � */
        {"\xd0\xae","Yu"}, /* � */
        {"\xd1\x8e","yu"} /* � */
    };

    if (!out_buff) {
        return strlen(in_buff) * 4L;
    }

    const size_t symb_size = sizeof(symbols) / sizeof(symbols[0]);

    while (*in_buff) {
        int allowed = utf8toTranslit_checkAllowed(in_buff);
        memcpy(out_buff, in_buff, allowed); out_buff += allowed; in_buff += allowed;
        if (*in_buff == '\x20') {
            *out_buff++ = '_';
            goto next;
        }

        if (!*(in_buff + 1)) {
            goto next;
        }
        for (int i = 0; i < symb_size; ++i) {
            if (*in_buff == symbols[i][0][0] && *(in_buff + 1) == symbols[i][0][1]) {
                size_t repl_len = strlen(symbols[i][1]);
                memcpy(out_buff, symbols[i][1], repl_len);
                out_buff += repl_len;

                ++in_buff; goto next;
            }
        }
    next:
        ++in_buff;
    }
    *out_buff = '\0';
    return 0;
}

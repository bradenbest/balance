#include <stdio.h>

#include "input.h"

#define IF_STRCMP(CMD)\
    if(compare_substrs(cmd, CMD, get_strlen(CMD)))

static int compare_substrs(char *s1, char *s2, int sz);
static int get_strlen(const char *s);

static int compare_substrs(char *s1, char *s2, int sz){/*{{{*/
    int i;
    for(i = 0; i < sz; i++){
        if(s1[i] != s2[i]){
            return 0;
        }
    }
    return 1;
}/*}}}*/
static int get_strlen(const char *s){/*{{{*/
    int i = 0;
    while(s[++i]);
    return i;
}/*}}}*/

command input_get_command(char *prompt){/*{{{*/
    char cmd[100];

    if(prompt){
        fputs(prompt, stdout);
    }
    if(fgets(cmd, 100, stdin) == 0) // EOF
        return cmd_quit;

    IF_STRCMP("quit")       return cmd_quit;
    IF_STRCMP("q")          return cmd_quit;
    IF_STRCMP("add")        return cmd_add;
    IF_STRCMP("ad")         return cmd_add;
    IF_STRCMP("config")     return cmd_config;
    IF_STRCMP("cfg")        return cmd_config;
    IF_STRCMP("edit")       return cmd_edit;
    IF_STRCMP("ed")         return cmd_edit;
    IF_STRCMP("get_time")   return cmd_get_time;
    IF_STRCMP("gt")         return cmd_get_time;
    IF_STRCMP("help")       return cmd_help;
    IF_STRCMP("?")          return cmd_help;
    IF_STRCMP("history")    return cmd_history;
    IF_STRCMP("hs")         return cmd_history;
    IF_STRCMP("save")       return cmd_save;
    IF_STRCMP("w")          return cmd_save;
    IF_STRCMP("show")       return cmd_show;
    IF_STRCMP("sh")         return cmd_show;
    IF_STRCMP("time_shift") return cmd_time_shift;
    IF_STRCMP("ts")         return cmd_time_shift;
    return cmd_none;
}/*}}}*/
double input_get_double(char *prompt){/*{{{*/
    double ret = 0;
    if(prompt){
        fputs(prompt, stdout);
    }
    while(!ret){
        scanf("%lf", &ret);
    }
    return ret;
}/*}}}*/
boolean input_yes_or_no(char *prompt, boolean _default){/*{{{*/
    char c = 0;
    while(!c){
        if(prompt){
            fputs(prompt, stdout);
            fputs(_default == yes ? "[Y/n] " : "[y/N] ", stdout);
        }
        c = getchar();
    }
    switch(c){
        case 'y':
        case 'Y':
            return yes;
        case 'n':
        case 'N':
            return no;
        default:
            return _default;
    }
}/*}}}*/

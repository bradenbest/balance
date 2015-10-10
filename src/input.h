typedef enum {
    cmd_none,
    cmd_quit,
    cmd_add,
    cmd_config,
    cmd_edit,
    cmd_get_time,
    cmd_help,
    cmd_history,
    cmd_save,
    cmd_show,
    cmd_time_shift,
} command;

typedef enum {
    no,
    yes
} boolean;

command input_get_command(char *prompt);
double input_get_double(char *prompt);
boolean input_yes_or_no(char *prompt, boolean _default);

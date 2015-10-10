typedef enum {
    col_none,
    col_red,
    col_yellow,
    col_blue,
    col_white,
} color;

typedef enum {
    edit_add,
    edit_modify,
    edit_config,
    edit_time_shift,
} edit_mode;

void color_begin(color c);
void color_print(color c, char *msg);
void color_end();
char *edit_string(edit_mode mode);
void show_data(data *d);
void ui_loop(data *d);

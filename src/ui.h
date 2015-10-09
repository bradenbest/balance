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
} edit_mode;

typedef struct edit_node{
    edit_mode mode;
    char *fieldname;
    long_double value;  // value applied during edit
    long_double before; // value before edit
    long_double after;  // value after edit
    // Print: 
    //   [mode (add/modify/config)]: [fieldname] ([value])
    //       before: [before]
    //       after:  [after]
} edit_node;

void color_print(color c, char *msg);
void show_data(data *d);
void ui_loop(data *d);

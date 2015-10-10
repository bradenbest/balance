typedef struct edit_node edit_node;

void history_destroy(edit_node **h);
edit_node **history_new(int sz);
void history_push(edit_node **history, edit_node *node);
void history_report(edit_node **history);
edit_node *node_new(edit_mode mode, char *fieldname, long_double value, long_double before, long_double after);

struct edit_node {
    edit_mode    mode;
    char         *fieldname;
    long_double  value;
    long_double  before;
    long_double  after;
};

typedef struct version{
  unsigned int major : 32;
  unsigned int minor : 32;
  unsigned int patch : 32;
} version;

void print_version(version *v);
void set_version(version *v);

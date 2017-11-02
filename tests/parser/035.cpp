struct strct;
struct {int a;};
struct {int a, b;};
struct {int a, b; float c;};
struct {int a:10, b; float c : 12.01;};
struct s  {char a;};
struct s1 {int a, *b;};
struct s2 {int a, b; float c;};
struct s3 {int a:10, b; float c : 12.01;} b = {.a .b = 12, .c = 3.0};


└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── main
        │   └── Function returning
        │       ├── Qualified 0
        │       │   └── INT32
        │       └── Params
        │           └── #0
        │               └── Qualified 0
        │                   └── VOID
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   ├── A
                │       │   └── Qualified 0
                │       │       └── FLOAT
                │       ├── InitDeclarator
                │       │   ├── B
                │       │   └── Qualified 0
                │       │       └── FLOAT
                │       ├── InitDeclarator
                │       │   ├── C
                │       │   └── Qualified 0
                │       │       └── FLOAT
                │       └── InitDeclarator
                │           ├── k
                │           └── Qualified 0
                │               └── FLOAT
                ├── ;
                │   └── *
                │       ├── /
                │       │   ├── C
                │       │   └── /
                │       │       ├── +
                │       │       │   ├── A
                │       │       │   └── B
                │       │       └── +
                │       │           ├── typcast
                │       │           │   ├── FLOAT
                │       │           │   └── 2
                │       │           └── *
                │       │               ├── typcast
                │       │               │   ├── FLOAT
                │       │               │   └── 4
                │       │               └── -
                │       │                   ├── /
                │       │                   │   ├── 123.32
                │       │                   │   └── typcast
                │       │                   │       ├── FLOAT
                │       │                   │       └── 9
                │       │                   └── typcast
                │       │                       ├── FLOAT
                │       │                       └── 123
                │       └── k
                └── return
                    └── 0


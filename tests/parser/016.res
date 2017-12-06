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
                │       │   ├── a
                │       │   └── Qualified 0
                │       │       └── FLOAT
                │       ├── InitDeclarator
                │       │   ├── b
                │       │   └── Qualified 0
                │       │       └── FLOAT
                │       ├── InitDeclarator
                │       │   ├── c
                │       │   └── Qualified 0
                │       │       └── FLOAT
                │       ├── InitDeclarator
                │       │   ├── y2
                │       │   └── Qualified 0
                │       │       └── FLOAT
                │       └── InitDeclarator
                │           ├── l
                │           └── Qualified 0
                │               └── FLOAT
                ├── ;
                │   └── /
                │       ├── *
                │       │   ├── /
                │       │   │   ├── -
                │       │   │   │   ├── a
                │       │   │   │   └── b
                │       │   │   └── /
                │       │   │       ├── c
                │       │   │       └── typcast
                │       │   │           ├── FLOAT
                │       │   │           └── 3
                │       │   └── typcast
                │       │       ├── FLOAT
                │       │       └── 9
                │       └── *
                │           ├── y2
                │           └── -
                │               ├── typcast
                │               │   ├── FLOAT
                │               │   └── 2
                │               └── l
                └── return
                    └── 0


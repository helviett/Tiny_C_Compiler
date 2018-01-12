└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── main
        │   └── Function returning
        │       └── Qualified 0
        │           └── INT32
        │       └── Params
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   ├── a
                │       │   └── Qualified 0
                │       │       └── INT32
                │       ├── InitDeclarator
                │       │   ├── b
                │       │   └── Qualified 0
                │       │       └── INT32
                │       ├── InitDeclarator
                │       │   ├── c
                │       │   └── Qualified 0
                │       │       └── INT32
                │       ├── InitDeclarator
                │       │   ├── d
                │       │   └── Qualified 0
                │       │       └── INT32
                │       ├── InitDeclarator
                │       │   ├── e
                │       │   └── Qualified 0
                │       │       └── INT32
                │       ├── InitDeclarator
                │       │   ├── f
                │       │   └── Qualified 0
                │       │       └── INT32
                │       └── InitDeclarator
                │           ├── g
                │           └── Array of
                │               ├── Qualified 0
                │               │   └── INT32
                │               └── 5
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── max
                │           ├── Qualified 0
                │           │   └── INT32
                │           └── Initializer 
                │               └── ?:
                │                   ├── >
                │                   │   ├── c
                │                   │   └── d
                │                   ├── c
                │                   └── d
                ├── ;
                │   └── =
                │       ├── a
                │       └── 5
                ├── ;
                │   └── =
                │       ├── a
                │       └── ?:
                │           ├── >
                │           │   ├── +
                │           │   │   └── 1
                │           │   └── 4
                │           ├── &&
                │           │   ├── &
                │           │   │   ├── <<
                │           │   │   │   ├── >>
                │           │   │   │   │   ├── -
                │           │   │   │   │   │   ├── ^
                │           │   │   │   │   │   │   ├── 123
                │           │   │   │   │   │   │   └── 7
                │           │   │   │   │   │   └── d
                │           │   │   │   │   └── 8
                │           │   │   │   └── 7
                │           │   │   └── ==
                │           │   │       ├── +
                │           │   │       │   ├── 12
                │           │   │       │   └── ~
                │           │   │       │       └── 1
                │           │   │       └── <=
                │           │   │           ├── 9
                │           │   │           └── 5
                │           │   └── -
                │           │       ├── +
                │           │       │   ├── f
                │           │       │   └── ++'
                │           │       │       └── []
                │           │       │           ├── g
                │           │       │           └── 5
                │           │       └── 15
                │           └── 12
                ├── ;
                │   └── =
                │       ├── a
                │       └── =
                │           ├── c
                │           └── =
                │               ├── d
                │               └── 15
                └── return
                    └── 0


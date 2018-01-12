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
                │       └── InitDeclarator
                │           ├── c
                │           └── Qualified 0
                │               └── INT32
                ├── ;
                │   └── ==
                │       ├── >
                │       │   ├── <=
                │       │   │   ├── 1
                │       │   │   └── 3
                │       │   └── 4
                │       └── >=
                │           ├── <
                │           │   ├── 3
                │           │   └── 8
                │           └── 9
                ├── ;
                │   └── !=
                │       ├── +
                │       │   ├── 5
                │       │   └── *
                │       │       ├── 12
                │       │       └── 8
                │       └── >
                │           ├── <<
                │           │   ├── 5
                │           │   └── +
                │           │       ├── 3
                │           │       └── 1
                │           └── 4
                ├── ;
                │   └── >
                │       ├── ==
                │       │   ├── a
                │       │   └── c
                │       └── 123
                ├── ;
                │   └── ==
                │       ├── <=
                │       │   ├── <<
                │       │   │   ├── -
                │       │   │   │   ├── /
                │       │   │   │   │   ├── 8
                │       │   │   │   │   └── 2
                │       │   │   │   └── 3
                │       │   │   └── 4
                │       │   └── 4
                │       └── 0
                └── return
                    └── 0


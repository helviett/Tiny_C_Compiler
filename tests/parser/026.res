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
                │       └── InitDeclarator
                │           ├── f
                │           └── Qualified 0
                │               └── INT32
                ├── ;
                │   └── ^
                │       ├── +
                │       │   ├── a
                │       │   └── b
                │       └── +
                │           ├── c
                │           └── d
                ├── ;
                │   └── ^
                │       ├── &
                │       │   ├── a
                │       │   └── f
                │       └── b
                ├── ;
                │   └── ^
                │       ├── *
                │       │   ├── /
                │       │   │   ├── 2
                │       │   │   └── 9
                │       │   └── 8
                │       └── ==
                │           ├── 1
                │           └── 0
                └── return
                    └── 0


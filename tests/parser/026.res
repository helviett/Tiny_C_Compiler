└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── main
        │   └── Function returning
        │       ├── INT32
        │       └── Params
        │           └── #0
        │               └── VOID
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   ├── a
                │       │   └── INT32
                │       ├── InitDeclarator
                │       │   ├── b
                │       │   └── INT32
                │       ├── InitDeclarator
                │       │   ├── c
                │       │   └── INT32
                │       ├── InitDeclarator
                │       │   ├── d
                │       │   └── INT32
                │       ├── InitDeclarator
                │       │   ├── e
                │       │   └── INT32
                │       └── InitDeclarator
                │           ├── f
                │           └── INT32
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


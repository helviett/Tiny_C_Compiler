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
                │   └── &
                │       ├── a
                │       └── c
                ├── ;
                │   └── &
                │       ├── +
                │       │   ├── a
                │       │   └── b
                │       └── c
                ├── ;
                │   └── &
                │       ├── +
                │       │   ├── a
                │       │   └── *
                │       │       ├── b
                │       │       └── c
                │       └── d
                ├── ;
                │   └── ^
                │       ├── a
                │       └── &
                │           ├── ==
                │           │   ├── b
                │           │   └── c
                │           └── e
                ├── ;
                │   └── ^
                │       ├── <<
                │       │   ├── f
                │       │   └── *
                │       │       ├── 12
                │       │       └── 8
                │       └── &
                │           ├── 13
                │           └── <=
                │               ├── 12
                │               └── 3
                └── return
                    └── 0


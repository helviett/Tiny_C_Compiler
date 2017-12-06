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


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
                ├── ;
                │   └── &&
                │       ├── >>
                │       │   ├── +
                │       │   │   ├── `--
                │       │   │   │   └── []
                │       │   │   │       ├── g
                │       │   │   │       └── 1
                │       │   │   └── *
                │       │   │       ├── b
                │       │   │       └── c
                │       │   └── +
                │       │       ├── 3
                │       │       └── *
                │       │           ├── 12
                │       │           └── 5
                │       └── <=
                │           ├── +
                │           │   ├── -
                │           │   │   └── 8
                │           │   └── /
                │           │       ├── *
                │           │       │   ├── 2
                │           │       │   └── f
                │           │       └── c
                │           └── ==
                │               ├── 12
                │               └── d
                ├── ;
                │   └── &&
                │       ├── &
                │       │   ├── <<
                │       │   │   ├── >>
                │       │   │   │   ├── -
                │       │   │   │   │   ├── ^
                │       │   │   │   │   │   ├── 123
                │       │   │   │   │   │   └── 7
                │       │   │   │   │   └── d
                │       │   │   │   └── 8
                │       │   │   └── 7
                │       │   └── ==
                │       │       ├── +
                │       │       │   ├── 12
                │       │       │   └── ~
                │       │       │       └── 1
                │       │       └── <=
                │       │           ├── 9
                │       │           └── 5
                │       └── -
                │           ├── +
                │           │   ├── f
                │           │   └── ++'
                │           │       └── []
                │           │           ├── g
                │           │           └── 5
                │           └── 15
                └── return
                    └── 0


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
                │       │   ├── longername
                │       │   └── INT32
                │       └── InitDeclarator
                │           ├── pointer
                │           └── Pointer to
                │               └── INT32
                ├── ;
                │   └── -
                │       └── a
                ├── ;
                │   └── +
                │       └── b
                ├── ;
                │   └── &
                │       └── longername
                ├── ;
                │   └── *
                │       └── pointer
                ├── ;
                │   └── !
                │       └── 0
                ├── ;
                │   └── ~
                │       └── 1
                ├── ;
                │   └── ++'
                │       └── a
                ├── ;
                │   └── --`
                │       └── b
                ├── ;
                │   └── ++'
                │       └── --`
                │           └── longername
                ├── ;
                │   └── sizeof
                │       └── 10
                ├── ;
                │   └── sizeof
                │       └── -
                │           └── 10
                ├── ;
                │   └── sizeof
                │       └── ++'
                │           └── 10
                ├── ;
                │   └── sizeof
                │       └── --`
                │           └── -
                │               └── 10
                ├── ;
                │   └── sizeof()
                │       └── TypeName
                │           └── INT32
                ├── ;
                │   └── sizeof()
                │       └── TypeName
                │           └── Pointer to
                │               └── Pointer to
                │                   └── INT32
                ├── ;
                │   └── sizeof()
                │       └── TypeName
                │           └── Pointer to
                │               └── INT32
                └── return
                    └── 0


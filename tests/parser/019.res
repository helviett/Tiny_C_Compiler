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
                │       └── InitDeclarator
                │           ├── b
                │           ├── INT32
                │           └── 10
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── a
                │           ├── Pointer to
                │           │   └── INT32
                │           └── &
                │               └── b
                ├── ;
                │   └── typcast
                │       ├── TypeName
                │       │   └── Pointer to
                │       │       └── INT32
                │       └── 10
                ├── ;
                │   └── typcast
                │       ├── TypeName
                │       │   └── Pointer to
                │       │       └── VOID
                │       └── a
                ├── ;
                │   └── typcast
                │       ├── TypeName
                │       │   └── Pointer to
                │       │       └── Function returning
                │       │           ├── INT32
                │       │           └── Params
                │       │               └── #0
                │       │                   └── VOID
                │       └── a
                └── return
                    └── 0


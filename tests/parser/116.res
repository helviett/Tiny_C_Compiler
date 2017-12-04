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
                │       └── InitDeclarator
                │           ├── b
                │           └── Qualified 0
                │               └── INT32
                ├── ;
                │   └── =
                │       ├── a
                │       └── ^
                │           ├── a
                │           └── b
                ├── ;
                │   └── =
                │       ├── b
                │       └── ^
                │           ├── b
                │           └── a
                └── ;
                    └── =
                        ├── a
                        └── ^
                            ├── a
                            └── b


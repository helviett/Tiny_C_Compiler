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
                │       │   └── Qualified 1
                │       │       └── INT8
                │       └── InitDeclarator
                │           ├── b
                │           └── Qualified 1
                │               └── INT8
                └── ;
                    └── &
                        ├── typcast
                        │   ├── INT32
                        │   └── a
                        └── +
                            ├── 3
                            └── typcast
                                ├── INT32
                                └── b


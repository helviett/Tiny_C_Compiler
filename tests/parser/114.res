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
                │       └── InitDeclarator
                │           ├── b
                │           └── Qualified 0
                │               └── INT32
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── c
                │           └── Qualified 0
                │               └── FLOAT
                └── ;
                    └── *
                        ├── typcast
                        │   ├── FLOAT
                        │   └── a
                        └── +
                            ├── c
                            └── typcast
                                ├── FLOAT
                                └── b


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
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── c
                │           └── Qualified 0
                │               └── FLOAT
                └── ;
                    └── /
                        ├── typcast
                        │   ├── FLOAT
                        │   └── a
                        └── +
                            ├── c
                            └── typcast
                                ├── FLOAT
                                └── %
                                    ├── b
                                    └── a


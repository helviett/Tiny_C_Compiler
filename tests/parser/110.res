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
                │           └── struct 
                │               └── m
                │                   └── Qualified 0
                │                       └── INT32
                └── ;
                    └── +
                        ├── +
                        │   ├── a
                        │   └── b
                        └── .
                            ├── c
                            └── m


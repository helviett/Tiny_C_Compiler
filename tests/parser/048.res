└── Unit
    ├── Decl
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           ├── dosomething
    │           └── Function returning
    │               ├── Qualified 0
    │               │   └── VOID
    │               └── Params
    │                   └── #0
    │                       └── Qualified 0
    │                           └── VOID
    └── FuncDef
        ├── Declarator
        │   ├── forloop
        │   └── Function returning
        │       ├── Qualified 0
        │       │   └── VOID
        │       └── Params
        │           └── n
        │               └── Qualified 0
        │                   └── INT32
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── i
                │           └── Qualified 0
                │               └── INT32
                └── for
                    ├── ;
                    │   └── =
                    │       ├── i
                    │       └── 0
                    ├── ;
                    │   └── <
                    │       ├── i
                    │       └── n
                    ├── ++'
                    │   └── i
                    └── {}
                        └── BlockItemList
                            └── ;
                                └── FuncCall
                                    └── dosomething


└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── main
        │   └── Function returning
        │       ├── Qualified 0
        │       │   └── VOID
        │       └── Params
        │           └── #0
        │               └── Qualified 0
        │                   └── VOID
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── a
                │           └── Qualified 0
                │               └── INT32
                └── if
                    ├── >
                    │   ├── a
                    │   └── 8
                    └── {}
                        └── BlockItemList
                            ├── ;
                            │   └── -=
                            │       ├── a
                            │       └── -
                            │           ├── a
                            │           └── 12
                            └── ;
                                └── *=
                                    ├── a
                                    └── *
                                        ├── a
                                        └── 11


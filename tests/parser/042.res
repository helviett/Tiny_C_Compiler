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
                │           ├── a
                │           ├── INT32
                │           └── 10
                ├── label
                │   ├── label1
                │   └── ;
                │       └── +=
                │           ├── a
                │           └── 10
                └── label
                    ├── label2
                    └── {}
                        └── BlockItemList
                            ├── ;
                            │   └── -=
                            │       ├── a
                            │       └── 12
                            └── goto
                                └── label1


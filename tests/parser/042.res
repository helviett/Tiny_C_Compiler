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
                │       └── InitDeclarator
                │           ├── a
                │           ├── Qualified 0
                │           │   └── INT32
                │           └── Initializer 
                │               └── 10
                ├── label
                │   ├── label1
                │   └── ;
                │       └── +=
                │           ├── a
                │           └── +
                │               ├── a
                │               └── 10
                └── label
                    ├── label2
                    └── {}
                        └── BlockItemList
                            ├── ;
                            │   └── -=
                            │       ├── a
                            │       └── -
                            │           ├── a
                            │           └── 12
                            └── goto
                                └── label1


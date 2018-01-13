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
                │       └── InitDeclarator
                │           ├── a
                │           ├── Qualified 0
                │           │   └── INT32
                │           └── Initializer 
                │               └── 10
                ├── functionLabel
                │   ├── label1
                │   └── ;
                │       └── +=
                │           ├── a
                │           └── +
                │               ├── a
                │               └── 10
                └── functionLabel
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


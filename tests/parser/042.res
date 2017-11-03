└── Unit
    └── FuncDef
        ├── DeclarationSpecifiers
        │   └── int
        ├── Declarator
        │   └── Func Decl
        │       ├── main
        │       └── ParameterList
        │           └── param
        │               ├── DeclarationSpecifiers
        │               │   └── void
        │               └── Declarator
        └── {}
            └── BlockItemList
                ├── Decl
                │   ├── DeclarationSpecifiers
                │   │   └── int
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── Declarator
                │           │   └── a
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


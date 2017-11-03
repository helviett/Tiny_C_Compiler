└── Unit
    └── FuncDef
        ├── DeclarationSpecifiers
        │   └── void
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
                │           └── Declarator
                │               └── a
                └── if
                    ├── >
                    │   ├── a
                    │   └── 8
                    └── {}
                        └── BlockItemList
                            ├── ;
                            │   └── -=
                            │       ├── a
                            │       └── 12
                            └── ;
                                └── *=
                                    ├── a
                                    └── 11


└── Unit
    └── FuncDef
        ├── DeclarationSpecifiers
        │   └── void
        ├── Declarator
        │   └── Func Decl
        │       ├── forloop
        │       └── ParameterList
        │           └── param
        │               ├── DeclarationSpecifiers
        │               │   └── int
        │               └── Declarator
        │                   └── n
        └── {}
            └── BlockItemList
                ├── Decl
                │   ├── DeclarationSpecifiers
                │   │   └── int
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           └── Declarator
                │               └── i
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


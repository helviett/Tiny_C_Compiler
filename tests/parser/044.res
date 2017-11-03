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
                └── if else
                    ├── &&
                    │   ├── <=
                    │   │   ├── a
                    │   │   └── 10
                    │   └── >
                    │       ├── a
                    │       └── 0
                    ├── ;
                    │   └── `++
                    │       └── a
                    └── if else
                        ├── a
                        ├── {}
                        │   └── BlockItemList
                        │       └── ;
                        │           └── -=
                        │               ├── a
                        │               └── 12
                        └── ;


└── Unit
    ├── Decl
    │   ├── DeclarationSpecifiers
    │   │   └── char
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           └── Declarator
    │               ├── *
    │               └── []
    │                   └── Declarator
    │                       ├── *
    │                       └── Func Decl
    │                           ├── Declarator
    │                           │   ├── *
    │                           │   └── []
    │                           │       ├── foo
    │                           │       └── 5
    │                           └── ParameterList
    │                               ├── param
    │                               │   ├── DeclarationSpecifiers
    │                               │   │   └── char
    │                               │   └── Declarator
    │                               │       └── *
    │                               └── param
    │                                   ├── DeclarationSpecifiers
    │                                   │   └── int
    │                                   └── Declarator
    └── Decl
        ├── DeclarationSpecifiers
        │   └── char
        └── InitDeclaratorList
            └── InitDeclarator
                └── Declarator
                    ├── *
                    └── []
                        └── Declarator
                            ├── *
                            └── Func Decl
                                ├── Declarator
                                │   ├── *
                                │   │   └── *
                                │   └── []
                                │       ├── []
                                │       │   └── foo
                                │       └── 8
                                └── ParameterList
                                    └── param
                                        ├── DeclarationSpecifiers
                                        │   └── void
                                        └── Declarator


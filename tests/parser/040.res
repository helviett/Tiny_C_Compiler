└── Unit
    ├── Decl
    │   ├── DeclarationSpecifiers
    │   │   └── void
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           └── Declarator
    │               └── Func Decl
    │                   ├── f
    │                   └── ParameterList
    │                       └── param
    │                           ├── DeclarationSpecifiers
    │                           │   └── void
    │                           └── Declarator
    ├── Decl
    │   ├── DeclarationSpecifiers
    │   │   └── int
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           └── Declarator
    │               └── Func Decl
    │                   ├── a
    │                   └── ParameterList
    │                       ├── param
    │                       │   ├── DeclarationSpecifiers
    │                       │   │   └── int
    │                       │   └── Declarator
    │                       └── param
    │                           ├── DeclarationSpecifiers
    │                           │   └── int
    │                           └── Declarator
    └── Decl
        ├── DeclarationSpecifiers
        │   └── float
        └── InitDeclaratorList
            └── InitDeclarator
                └── Declarator
                    └── Func Decl
                        ├── b
                        └── ParameterList
                            ├── param
                            │   ├── DeclarationSpecifiers
                            │   │   └── float
                            │   └── Declarator
                            │       └── c
                            ├── param
                            │   ├── DeclarationSpecifiers
                            │   │   └── char
                            │   └── Declarator
                            │       ├── *
                            │       │   └── *
                            │       └── b
                            └── param
                                ├── DeclarationSpecifiers
                                │   └── int
                                └── Declarator
                                    └── []
                                        ├── a
                                        └── 50


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
                │           │   └── b
                │           └── 10
                ├── Decl
                │   ├── DeclarationSpecifiers
                │   │   └── int
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── Declarator
                │           │   ├── *
                │           │   └── a
                │           └── &
                │               └── b
                ├── ;
                │   └── typcast
                │       ├── TypeName
                │       │   ├── SpecQualList
                │       │   │   └── int
                │       │   └── Declarator
                │       │       └── *
                │       └── 10
                ├── ;
                │   └── typcast
                │       ├── TypeName
                │       │   ├── SpecQualList
                │       │   │   └── void
                │       │   └── Declarator
                │       │       └── *
                │       └── a
                ├── ;
                │   └── typcast
                │       ├── TypeName
                │       │   ├── SpecQualList
                │       │   │   └── int
                │       │   └── Declarator
                │       │       └── Func Decl
                │       │           └── ParameterList
                │       │               └── param
                │       │                   ├── DeclarationSpecifiers
                │       │                   │   └── void
                │       │                   └── Declarator
                │       └── a
                └── return
                    └── 0


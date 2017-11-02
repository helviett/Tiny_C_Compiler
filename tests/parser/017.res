└── Unit
    ├── FuncDef
    │   ├── DeclarationSpecifiers
    │   │   └── int
    │   ├── Declarator
    │   │   └── Func Decl
    │   │       ├── f
    │   │       └── ParameterList
    │   │           └── param
    │   │               ├── DeclarationSpecifiers
    │   │               │   └── void
    │   │               └── Declarator
    │   └── {}
    │       └── BlockItemList
    │           └── return
    │               └── 0
    ├── FuncDef
    │   ├── DeclarationSpecifiers
    │   │   └── void
    │   ├── Declarator
    │   │   └── Func Decl
    │   │       ├── func
    │   │       └── ParameterList
    │   │           ├── param
    │   │           │   ├── DeclarationSpecifiers
    │   │           │   │   └── int
    │   │           │   └── Declarator
    │   │           │       └── a
    │   │           └── param
    │   │               ├── DeclarationSpecifiers
    │   │               │   └── int
    │   │               └── Declarator
    │   │                   └── b
    │   └── {}
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
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── []
                │       │           ├── []
                │       │           │   ├── []
                │       │           │   │   ├── a
                │       │           │   │   └── 10
                │       │           │   └── 15
                │       │           └── 16
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── b
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── longername
                │       └── InitDeclarator
                │           └── Declarator
                │               ├── *
                │               └── pointer
                ├── Decl
                │   ├── DeclarationSpecifiers
                │   │   └── struct
                │   │       ├── G
                │   │       └── StructDeclarationList
                │   │           └── StructDeclaratorList
                │   │               ├── SpecQualList
                │   │               │   └── int
                │   │               └── StructDeclaratorList
                │   │                   ├── StructDeclarator
                │   │                   │   └── Declarator
                │   │                   │       └── a
                │   │                   └── StructDeclarator
                │   │                       └── Declarator
                │   │                           └── b
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── g
                │       └── InitDeclarator
                │           └── Declarator
                │               ├── *
                │               └── g2
                ├── ;
                │   └── []
                │       ├── []
                │       │   ├── []
                │       │   │   ├── a
                │       │   │   └── 1
                │       │   └── 3
                │       └── 15
                ├── ;
                │   └── `++
                │       └── a
                ├── ;
                │   └── `--
                │       └── a
                ├── ;
                │   └── `--
                │       └── `++
                │           └── a
                ├── ;
                │   └── FuncCall
                │       └── f
                ├── ;
                │   └── FuncCall
                │       ├── func
                │       └── ArgumentExprList
                │           ├── 10
                │           └── 12
                ├── ;
                │   └── .
                │       ├── g
                │       └── a
                ├── ;
                │   └── ->
                │       ├── g2
                │       └── b
                └── return
                    └── 0


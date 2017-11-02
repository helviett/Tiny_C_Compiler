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
                │   │   └── float
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── A
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── B
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── C
                │       └── InitDeclarator
                │           └── Declarator
                │               └── k
                ├── ;
                │   └── *
                │       ├── /
                │       │   ├── C
                │       │   └── /
                │       │       ├── +
                │       │       │   ├── A
                │       │       │   └── B
                │       │       └── +
                │       │           ├── 2
                │       │           └── *
                │       │               ├── 4
                │       │               └── -
                │       │                   ├── /
                │       │                   │   ├── 123.32
                │       │                   │   └── 9
                │       │                   └── 123
                │       └── k
                └── return
                    └── 0


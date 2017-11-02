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
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── a
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── b
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── c
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── d
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── e
                │       └── InitDeclarator
                │           └── Declarator
                │               └── f
                ├── ;
                │   └── ^
                │       ├── +
                │       │   ├── a
                │       │   └── b
                │       └── +
                │           ├── c
                │           └── d
                ├── ;
                │   └── ^
                │       ├── &
                │       │   ├── a
                │       │   └── f
                │       └── b
                ├── ;
                │   └── ^
                │       ├── *
                │       │   ├── /
                │       │   │   ├── 2
                │       │   │   └── 9
                │       │   └── 8
                │       └── ==
                │           ├── 1
                │           └── 0
                └── return
                    └── 0


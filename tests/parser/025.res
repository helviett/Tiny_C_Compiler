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
                │   └── &
                │       ├── a
                │       └── c
                ├── ;
                │   └── &
                │       ├── +
                │       │   ├── a
                │       │   └── b
                │       └── c
                ├── ;
                │   └── &
                │       ├── +
                │       │   ├── a
                │       │   └── *
                │       │       ├── b
                │       │       └── c
                │       └── d
                ├── ;
                │   └── ^
                │       ├── a
                │       └── &
                │           ├── ==
                │           │   ├── b
                │           │   └── c
                │           └── e
                ├── ;
                │   └── ^
                │       ├── <<
                │       │   ├── f
                │       │   └── *
                │       │       ├── 12
                │       │       └── 8
                │       └── &
                │           ├── 13
                │           └── <=
                │               ├── 12
                │               └── 3
                └── return
                    └── 0


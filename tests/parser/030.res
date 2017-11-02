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
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── f
                │       └── InitDeclarator
                │           └── Declarator
                │               └── []
                │                   ├── g
                │                   └── 5
                ├── Decl
                │   ├── DeclarationSpecifiers
                │   │   └── int
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── Declarator
                │           │   └── max
                │           └── ?:
                │               ├── >
                │               │   ├── c
                │               │   └── d
                │               ├── c
                │               └── d
                ├── ;
                │   └── ?:
                │       ├── |
                │       │   ├── <=
                │       │   │   ├── +
                │       │   │   │   ├── 5
                │       │   │   │   └── *
                │       │   │   │       ├── 12
                │       │   │   │       └── 8
                │       │   │   └── 5
                │       │   └── >
                │       │       ├── <<
                │       │       │   ├── 9
                │       │       │   └── +
                │       │       │       ├── 3
                │       │       │       └── 1
                │       │       └── 4
                │       ├── &&
                │       │   ├── &
                │       │   │   ├── <<
                │       │   │   │   ├── >>
                │       │   │   │   │   ├── -
                │       │   │   │   │   │   ├── ^
                │       │   │   │   │   │   │   ├── 123
                │       │   │   │   │   │   │   └── 7
                │       │   │   │   │   │   └── d
                │       │   │   │   │   └── 8
                │       │   │   │   └── 7
                │       │   │   └── ==
                │       │   │       ├── +
                │       │   │       │   ├── 12
                │       │   │       │   └── ~
                │       │   │       │       └── 1
                │       │   │       └── <=
                │       │   │           ├── 9
                │       │   │           └── 5
                │       │   └── -
                │       │       ├── +
                │       │       │   ├── f
                │       │       │   └── ++'
                │       │       │       └── []
                │       │       │           ├── g
                │       │       │           └── 5
                │       │       └── 15
                │       └── 12
                └── return
                    └── 0


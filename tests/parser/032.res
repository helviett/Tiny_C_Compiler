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
                ├── ;
                │   └── =
                │       ├── a
                │       └── 5
                ├── ;
                │   └── =
                │       ├── a
                │       └── ?:
                │           ├── >
                │           │   ├── +
                │           │   │   └── 1
                │           │   └── 4
                │           ├── &&
                │           │   ├── &
                │           │   │   ├── <<
                │           │   │   │   ├── >>
                │           │   │   │   │   ├── -
                │           │   │   │   │   │   ├── ^
                │           │   │   │   │   │   │   ├── 123
                │           │   │   │   │   │   │   └── 7
                │           │   │   │   │   │   └── d
                │           │   │   │   │   └── 8
                │           │   │   │   └── 7
                │           │   │   └── ==
                │           │   │       ├── +
                │           │   │       │   ├── 12
                │           │   │       │   └── ~
                │           │   │       │       └── 1
                │           │   │       └── <=
                │           │   │           ├── 9
                │           │   │           └── 5
                │           │   └── -
                │           │       ├── +
                │           │       │   ├── f
                │           │       │   └── ++'
                │           │       │       └── []
                │           │       │           ├── g
                │           │       │           └── 5
                │           │       └── 15
                │           └── 12
                ├── ;
                │   └── =
                │       ├── a
                │       └── =
                │           ├── c
                │           └── =
                │               ├── d
                │               └── 15
                ├── ;
                │   └── +=
                │       ├── a
                │       └── ?:
                │           ├── >
                │           │   ├── c
                │           │   └── d
                │           ├── c
                │           └── d
                ├── ;
                │   └── <<=
                │       ├── a
                │       └── 1
                ├── ;
                │   └── %=
                │       ├── a
                │       └── *
                │           ├── 9
                │           └── 19
                ├── ;
                │   └── |=
                │       ├── a
                │       └── >>
                │           ├── -
                │           │   ├── ^
                │           │   │   ├── 123
                │           │   │   └── 7
                │           │   └── d
                │           └── 8
                ├── ;
                │   └── ^=
                │       ├── a
                │       └── b
                ├── ;
                │   └── &=
                │       ├── b
                │       └── +
                │           ├── +
                │           │   ├── []
                │           │   │   ├── g
                │           │   │   └── 1
                │           │   └── []
                │           │       ├── g
                │           │       └── 2
                │           └── *
                │               └── +
                │                   ├── g
                │                   └── 3
                ├── ;
                │   └── >>=
                │       ├── f
                │       └── >>=
                │           ├── 1
                │           └── 3
                └── return
                    └── 0


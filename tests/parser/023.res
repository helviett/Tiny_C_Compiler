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
                │       └── InitDeclarator
                │           └── Declarator
                │               └── c
                ├── ;
                │   └── ==
                │       ├── >
                │       │   ├── <=
                │       │   │   ├── 1
                │       │   │   └── 3
                │       │   └── 4
                │       └── >=
                │           ├── <
                │           │   ├── 3
                │           │   └── 8
                │           └── 9
                ├── ;
                │   └── !=
                │       ├── +
                │       │   ├── 5
                │       │   └── *
                │       │       ├── 12
                │       │       └── 8
                │       └── >
                │           ├── <<
                │           │   ├── 5
                │           │   └── +
                │           │       ├── 3
                │           │       └── 1
                │           └── 4
                ├── ;
                │   └── >
                │       ├── ==
                │       │   ├── a
                │       │   └── c
                │       └── 123
                ├── ;
                │   └── ==
                │       ├── <=
                │       │   ├── <<
                │       │   │   ├── -
                │       │   │   │   ├── /
                │       │   │   │   │   ├── 8
                │       │   │   │   │   └── 2
                │       │   │   │   └── 3
                │       │   │   └── 4
                │       │   └── 4
                │       └── 0
                └── return
                    └── 0


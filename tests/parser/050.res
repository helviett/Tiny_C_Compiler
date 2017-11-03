└── Unit
    ├── FuncDef
    │   ├── DeclarationSpecifiers
    │   │   └── int
    │   ├── Declarator
    │   │   └── Func Decl
    │   │       ├── gcd
    │   │       └── ParameterList
    │   │           ├── param
    │   │           │   ├── DeclarationSpecifiers
    │   │           │   │   └── int
    │   │           │   └── Declarator
    │   │           │       └── x
    │   │           └── param
    │   │               ├── DeclarationSpecifiers
    │   │               │   └── int
    │   │               └── Declarator
    │   │                   └── y
    │   └── {}
    │       └── BlockItemList
    │           ├── Decl
    │           │   ├── DeclarationSpecifiers
    │           │   │   └── int
    │           │   └── InitDeclaratorList
    │           │       ├── InitDeclarator
    │           │       │   ├── Declarator
    │           │       │   │   └── r
    │           │       │   └── 0
    │           │       ├── InitDeclarator
    │           │       │   └── Declarator
    │           │       │       └── a
    │           │       └── InitDeclarator
    │           │           └── Declarator
    │           │               └── b
    │           ├── ;
    │           │   └── =
    │           │       ├── a
    │           │       └── ?:
    │           │           ├── >
    │           │           │   ├── x
    │           │           │   └── y
    │           │           ├── x
    │           │           └── y
    │           ├── ;
    │           │   └── =
    │           │       ├── b
    │           │       └── ?:
    │           │           ├── <
    │           │           │   ├── x
    │           │           │   └── y
    │           │           ├── x
    │           │           └── y
    │           ├── ;
    │           │   └── =
    │           │       ├── r
    │           │       └── b
    │           ├── while
    │           │   ├── !=
    │           │   │   ├── %
    │           │   │   │   ├── a
    │           │   │   │   └── b
    │           │   │   └── 0
    │           │   └── {}
    │           │       └── BlockItemList
    │           │           ├── ;
    │           │           │   └── =
    │           │           │       ├── r
    │           │           │       └── %
    │           │           │           ├── a
    │           │           │           └── b
    │           │           ├── ;
    │           │           │   └── =
    │           │           │       ├── a
    │           │           │       └── b
    │           │           └── ;
    │           │               └── =
    │           │                   ├── b
    │           │                   └── r
    │           └── return
    │               └── r
    └── FuncDef
        ├── DeclarationSpecifiers
        │   └── int
        ├── Declarator
        │   └── Func Decl
        │       ├── lcm
        │       └── ParameterList
        │           ├── param
        │           │   ├── DeclarationSpecifiers
        │           │   │   └── int
        │           │   └── Declarator
        │           │       └── x
        │           └── param
        │               ├── DeclarationSpecifiers
        │               │   └── int
        │               └── Declarator
        │                   └── y
        └── {}
            └── BlockItemList
                ├── Decl
                │   ├── DeclarationSpecifiers
                │   │   └── int
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           └── Declarator
                │               └── a
                ├── ;
                │   └── =
                │       ├── a
                │       └── ?:
                │           ├── >
                │           │   ├── x
                │           │   └── y
                │           ├── x
                │           └── y
                └── while
                    ├── 1
                    └── {}
                        └── BlockItemList
                            ├── if
                            │   ├── &&
                            │   │   ├── ==
                            │   │   │   ├── %
                            │   │   │   │   ├── a
                            │   │   │   │   └── x
                            │   │   │   └── 0
                            │   │   └── ==
                            │   │       ├── %
                            │   │       │   ├── a
                            │   │       │   └── y
                            │   │       └── 0
                            │   └── return
                            │       └── a
                            └── ;
                                └── ++'
                                    └── a


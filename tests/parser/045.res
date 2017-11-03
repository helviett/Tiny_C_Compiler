└── Unit
    └── FuncDef
        ├── DeclarationSpecifiers
        │   └── int
        ├── Declarator
        │   └── Func Decl
        │       ├── binpow
        │       └── ParameterList
        │           ├── param
        │           │   ├── DeclarationSpecifiers
        │           │   │   └── int
        │           │   └── Declarator
        │           │       └── a
        │           └── param
        │               ├── DeclarationSpecifiers
        │               │   └── int
        │               └── Declarator
        │                   └── n
        └── {}
            └── BlockItemList
                ├── Decl
                │   ├── DeclarationSpecifiers
                │   │   └── int
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── Declarator
                │           │   └── res
                │           └── 1
                ├── while
                │   ├── n
                │   └── {}
                │       └── BlockItemList
                │           ├── if
                │           │   ├── &
                │           │   │   ├── n
                │           │   │   └── 1
                │           │   └── ;
                │           │       └── *=
                │           │           ├── res
                │           │           └── a
                │           ├── ;
                │           │   └── *=
                │           │       ├── a
                │           │       └── a
                │           └── ;
                │               └── >>=
                │                   ├── n
                │                   └── 1
                └── return
                    └── res


└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── binpow
        │   └── Function returning
        │       ├── INT32
        │       └── Params
        │           ├── a
        │           │   └── INT32
        │           └── n
        │               └── INT32
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── res
                │           ├── INT32
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


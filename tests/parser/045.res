└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── binpow
        │   └── Function returning
        │       ├── Qualified 0
        │       │   └── INT32
        │       └── Params
        │           ├── a
        │           │   └── Qualified 0
        │           │       └── INT32
        │           └── n
        │               └── Qualified 0
        │                   └── INT32
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── res
                │           ├── Qualified 0
                │           │   └── INT32
                │           └── Initializer 
                │               └── 1
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
                │           │           └── *
                │           │               ├── res
                │           │               └── a
                │           ├── ;
                │           │   └── *=
                │           │       ├── a
                │           │       └── *
                │           │           ├── a
                │           │           └── a
                │           └── ;
                │               └── >>=
                │                   ├── n
                │                   └── >>
                │                       ├── n
                │                       └── 1
                └── return
                    └── res


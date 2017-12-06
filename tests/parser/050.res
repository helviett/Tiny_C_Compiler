└── Unit
    ├── FuncDef
    │   ├── Declarator
    │   │   ├── gcd
    │   │   └── Function returning
    │   │       ├── Qualified 0
    │   │       │   └── INT32
    │   │       └── Params
    │   │           ├── x
    │   │           │   └── Qualified 0
    │   │           │       └── INT32
    │   │           └── y
    │   │               └── Qualified 0
    │   │                   └── INT32
    │   └── {}
    │       └── BlockItemList
    │           ├── Decl
    │           │   └── InitDeclaratorList
    │           │       ├── InitDeclarator
    │           │       │   ├── r
    │           │       │   ├── Qualified 0
    │           │       │   │   └── INT32
    │           │       │   └── Initializer 
    │           │       │       └── 0
    │           │       ├── InitDeclarator
    │           │       │   ├── a
    │           │       │   └── Qualified 0
    │           │       │       └── INT32
    │           │       └── InitDeclarator
    │           │           ├── b
    │           │           └── Qualified 0
    │           │               └── INT32
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
        ├── Declarator
        │   ├── lcm
        │   └── Function returning
        │       ├── Qualified 0
        │       │   └── INT32
        │       └── Params
        │           ├── x
        │           │   └── Qualified 0
        │           │       └── INT32
        │           └── y
        │               └── Qualified 0
        │                   └── INT32
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── a
                │           └── Qualified 0
                │               └── INT32
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


└── Unit
    ├── FuncDef
    │   ├── Declarator
    │   │   ├── gcd
    │   │   └── Function returning
    │   │       ├── INT32
    │   │       └── Params
    │   │           ├── x
    │   │           │   └── INT32
    │   │           └── y
    │   │               └── INT32
    │   └── {}
    │       └── BlockItemList
    │           ├── Decl
    │           │   └── InitDeclaratorList
    │           │       ├── InitDeclarator
    │           │       │   ├── r
    │           │       │   ├── INT32
    │           │       │   └── 0
    │           │       ├── InitDeclarator
    │           │       │   ├── a
    │           │       │   └── INT32
    │           │       └── InitDeclarator
    │           │           ├── b
    │           │           └── INT32
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
        │       ├── INT32
        │       └── Params
        │           ├── x
        │           │   └── INT32
        │           └── y
        │               └── INT32
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── a
                │           └── INT32
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


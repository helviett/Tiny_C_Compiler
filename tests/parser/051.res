└── Unit
    ├── FuncDef
    │   ├── Declarator
    │   │   ├── swap
    │   │   └── Function returning
    │   │       ├── VOID
    │   │       └── Params
    │   │           ├── x
    │   │           │   └── Pointer to
    │   │           │       └── INT32
    │   │           └── y
    │   │               └── Pointer to
    │   │                   └── INT32
    │   └── {}
    │       └── BlockItemList
    │           ├── Decl
    │           │   └── InitDeclaratorList
    │           │       └── InitDeclarator
    │           │           ├── temp
    │           │           └── INT32
    │           ├── ;
    │           │   └── =
    │           │       ├── temp
    │           │       └── *
    │           │           └── x
    │           ├── ;
    │           │   └── =
    │           │       ├── *
    │           │       │   └── x
    │           │       └── *
    │           │           └── y
    │           └── ;
    │               └── =
    │                   ├── *
    │                   │   └── y
    │                   └── temp
    ├── FuncDef
    │   ├── Declarator
    │   │   ├── choose_pivot
    │   │   └── Function returning
    │   │       ├── INT32
    │   │       └── Params
    │   │           ├── i
    │   │           │   └── INT32
    │   │           └── j
    │   │               └── INT32
    │   └── {}
    │       └── BlockItemList
    │           └── return
    │               └── /
    │                   ├── +
    │                   │   ├── i
    │                   │   └── j
    │                   └── 2
    └── FuncDef
        ├── Declarator
        │   ├── quicksort
        │   └── Function returning
        │       ├── VOID
        │       └── Params
        │           ├── list
        │           │   └── Array of
        │           │       └── INT32
        │           ├── m
        │           │   └── INT32
        │           └── n
        │               └── INT32
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   ├── key
                │       │   └── INT32
                │       ├── InitDeclarator
                │       │   ├── i
                │       │   └── INT32
                │       ├── InitDeclarator
                │       │   ├── j
                │       │   └── INT32
                │       └── InitDeclarator
                │           ├── k
                │           └── INT32
                └── if
                    ├── <
                    │   ├── m
                    │   └── n
                    └── {}
                        └── BlockItemList
                            ├── ;
                            │   └── =
                            │       ├── k
                            │       └── FuncCall
                            │           ├── choose_pivot
                            │           └── ArgumentExprList
                            │               ├── m
                            │               └── n
                            ├── ;
                            │   └── FuncCall
                            │       ├── swap
                            │       └── ArgumentExprList
                            │           ├── &
                            │           │   └── []
                            │           │       ├── list
                            │           │       └── m
                            │           └── &
                            │               └── []
                            │                   ├── list
                            │                   └── k
                            ├── ;
                            │   └── =
                            │       ├── key
                            │       └── []
                            │           ├── list
                            │           └── m
                            ├── ;
                            │   └── =
                            │       ├── i
                            │       └── +
                            │           ├── m
                            │           └── 1
                            ├── ;
                            │   └── =
                            │       ├── j
                            │       └── n
                            ├── while
                            │   ├── <=
                            │   │   ├── i
                            │   │   └── j
                            │   └── {}
                            │       └── BlockItemList
                            │           ├── while
                            │           │   ├── &&
                            │           │   │   ├── <=
                            │           │   │   │   ├── i
                            │           │   │   │   └── n
                            │           │   │   └── <=
                            │           │   │       ├── []
                            │           │   │       │   ├── list
                            │           │   │       │   └── i
                            │           │   │       └── key
                            │           │   └── ;
                            │           │       └── `++
                            │           │           └── i
                            │           ├── while
                            │           │   ├── &&
                            │           │   │   ├── >=
                            │           │   │   │   ├── j
                            │           │   │   │   └── m
                            │           │   │   └── >
                            │           │   │       ├── []
                            │           │   │       │   ├── list
                            │           │   │       │   └── j
                            │           │   │       └── key
                            │           │   └── ;
                            │           │       └── `--
                            │           │           └── j
                            │           └── if
                            │               ├── <
                            │               │   ├── i
                            │               │   └── j
                            │               └── ;
                            │                   └── FuncCall
                            │                       ├── swap
                            │                       └── ArgumentExprList
                            │                           ├── &
                            │                           │   └── []
                            │                           │       ├── list
                            │                           │       └── i
                            │                           └── &
                            │                               └── []
                            │                                   ├── list
                            │                                   └── j
                            ├── ;
                            │   └── FuncCall
                            │       ├── swap
                            │       └── ArgumentExprList
                            │           ├── &
                            │           │   └── []
                            │           │       ├── list
                            │           │       └── m
                            │           └── &
                            │               └── []
                            │                   ├── list
                            │                   └── j
                            ├── ;
                            │   └── FuncCall
                            │       ├── quicksort
                            │       └── ArgumentExprList
                            │           ├── list
                            │           ├── m
                            │           └── -
                            │               ├── j
                            │               └── 1
                            └── ;
                                └── FuncCall
                                    ├── quicksort
                                    └── ArgumentExprList
                                        ├── list
                                        ├── +
                                        │   ├── j
                                        │   └── 1
                                        └── n


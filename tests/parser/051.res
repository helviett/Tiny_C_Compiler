└── Unit
    ├── FuncDef
    │   ├── Declarator
    │   │   ├── swap
    │   │   └── Function returning
    │   │       ├── Qualified 0
    │   │       │   └── VOID
    │   │       └── Params
    │   │           ├── x
    │   │           │   └── Pointer to
    │   │           │       └── Qualified 0
    │   │           │           └── INT32
    │   │           └── y
    │   │               └── Pointer to
    │   │                   └── Qualified 0
    │   │                       └── INT32
    │   └── {}
    │       └── BlockItemList
    │           ├── Decl
    │           │   └── InitDeclaratorList
    │           │       └── InitDeclarator
    │           │           ├── temp
    │           │           └── Qualified 0
    │           │               └── INT32
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
    │   │       ├── Qualified 0
    │   │       │   └── INT32
    │   │       └── Params
    │   │           ├── i
    │   │           │   └── Qualified 0
    │   │           │       └── INT32
    │   │           └── j
    │   │               └── Qualified 0
    │   │                   └── INT32
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
        │       ├── Qualified 0
        │       │   └── VOID
        │       └── Params
        │           ├── list
        │           │   └── Pointer to
        │           │       └── Qualified 0
        │           │           └── INT32
        │           ├── m
        │           │   └── Qualified 0
        │           │       └── INT32
        │           └── n
        │               └── Qualified 0
        │                   └── INT32
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   ├── key
                │       │   └── Qualified 0
                │       │       └── INT32
                │       ├── InitDeclarator
                │       │   ├── i
                │       │   └── Qualified 0
                │       │       └── INT32
                │       ├── InitDeclarator
                │       │   ├── j
                │       │   └── Qualified 0
                │       │       └── INT32
                │       └── InitDeclarator
                │           ├── k
                │           └── Qualified 0
                │               └── INT32
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


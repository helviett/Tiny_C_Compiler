└── Unit
    ├── Decl
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           ├── A
    │           └── Qualified 0
    │               └── INT32
    ├── Decl
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           ├── B
    │           └── Array of
    │               ├── Pointer to
    │               │   └── Qualified 0
    │               │       └── DOUBLE
    │               └── 10
    ├── Decl
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           ├── C
    │           └── Array of
    │               ├── Pointer to
    │               │   └── Function returning
    │               │       ├── Pointer to
    │               │       │   └── Array of
    │               │       │       └── Pointer to
    │               │       │           └── Qualified 0
    │               │       │               └── INT8
    │               │       └── Params
    │               │           └── #0
    │               │               └── Qualified 0
    │               │                   └── INT32
    │               └── 5
    └── FuncDef
        ├── Declarator
        │   ├── main
        │   └── Function returning
        │       └── Qualified 0
        │           └── INT32
        │       └── Params
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── a
                │           └── Qualified 0
                │               └── INT32
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── b
                │           └── Array of
                │               ├── Pointer to
                │               │   └── Qualified 0
                │               │       └── DOUBLE
                │               └── 10
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── c
                │           └── Array of
                │               ├── Pointer to
                │               │   └── Function returning
                │               │       ├── Pointer to
                │               │       │   └── Array of
                │               │       │       └── Pointer to
                │               │       │           └── Qualified 0
                │               │       │               └── INT8
                │               │       └── Params
                │               │           └── #0
                │               │               └── Qualified 0
                │               │                   └── INT32
                │               └── 5
                └── ;
                    └── *
                        └── []
                            ├── *
                            │   └── FuncCall
                            │       ├── *
                            │       │   └── []
                            │       │       ├── c
                            │       │       └── 0
                            │       └── ArgumentExprList
                            │           └── a
                            └── 0


└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── main
        │   └── Function returning
        │       ├── Qualified 0
        │       │   └── INT32
        │       └── Params
        │           └── #0
        │               └── Qualified 0
        │                   └── VOID
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── b
                │           ├── Qualified 0
                │           │   └── INT32
                │           └── Initializer 
                │               └── 10
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── a
                │           ├── Pointer to
                │           │   └── Qualified 0
                │           │       └── INT32
                │           └── Initializer 
                │               └── &
                │                   └── b
                ├── ;
                │   └── typcast
                │       ├── Pointer to
                │       │   └── Qualified 0
                │       │       └── INT32
                │       └── 10
                ├── ;
                │   └── typcast
                │       ├── Pointer to
                │       │   └── Qualified 0
                │       │       └── VOID
                │       └── a
                ├── ;
                │   └── typcast
                │       ├── Pointer to
                │       │   └── Function returning
                │       │       ├── Qualified 0
                │       │       │   └── INT32
                │       │       └── Params
                │       │           └── #0
                │       │               └── Qualified 0
                │       │                   └── VOID
                │       └── a
                └── return
                    └── 0


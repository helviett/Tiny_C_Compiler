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
                │       ├── InitDeclarator
                │       │   ├── a
                │       │   └── Qualified 0
                │       │       └── INT32
                │       └── InitDeclarator
                │           ├── b
                │           └── Qualified 0
                │               └── INT32
                ├── ;
                │   └── =
                │       ├── b
                │       └── a
                ├── ;
                │   └── +=
                │       ├── b
                │       └── +
                │           ├── b
                │           └── a
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── c
                │           └── Qualified 0
                │               └── DOUBLE
                ├── ;
                │   └── =
                │       ├── c
                │       └── typcast
                │           ├── Qualified 0
                │           │   └── DOUBLE
                │           └── a
                ├── ;
                │   └── +=
                │       ├── c
                │       └── +
                │           ├── c
                │           └── typcast
                │               ├── DOUBLE
                │               └── a
                ├── ;
                │   └── +=
                │       ├── a
                │       └── typcast
                │           ├── Qualified 0
                │           │   └── INT32
                │           └── +
                │               ├── typcast
                │               │   ├── DOUBLE
                │               │   └── a
                │               └── c
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── p
                │           └── Pointer to
                │               └── Qualified 0
                │                   └── INT32
                └── ;
                    └── +=
                        ├── p
                        └── +
                            ├── p
                            └── 20


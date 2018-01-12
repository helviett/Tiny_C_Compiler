└── Unit
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
                │       ├── InitDeclarator
                │       │   ├── a
                │       │   └── Qualified 0
                │       │       └── INT32
                │       └── InitDeclarator
                │           ├── b
                │           └── Pointer to
                │               └── Pointer to
                │                   └── Qualified 0
                │                       └── INT32
                ├── Decl
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   ├── d
                │       │   └── Qualified 0
                │       │       └── DOUBLE
                │       └── InitDeclarator
                │           ├── c
                │           └── Qualified 0
                │               └── DOUBLE
                ├── Decl
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   ├── e
                │       │   └── struct A
                │       │       └── a
                │       │           └── Qualified 0
                │       │               └── INT32
                │       └── InitDeclarator
                │           ├── f
                │           └── Pointer to
                │               └── struct A
                │                   └── a
                │                       └── Qualified 0
                │                           └── INT32
                ├── ;
                │   └── typcast
                │       ├── Qualified 0
                │       │   └── INT32
                │       └── d
                ├── ;
                │   └── typcast
                │       ├── Qualified 0
                │       │   └── DOUBLE
                │       └── a
                ├── ;
                │   └── typcast
                │       ├── Pointer to
                │       │   └── struct A
                │       │       └── a
                │       │           └── Qualified 0
                │       │               └── INT32
                │       └── a
                ├── ;
                │   └── typcast
                │       ├── Pointer to
                │       │   └── Qualified 0
                │       │       └── INT32
                │       └── a
                └── return
                    └── 0


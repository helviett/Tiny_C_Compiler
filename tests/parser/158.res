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
                │           ├── a
                │           └── struct A
                │               └── a
                │                   └── Qualified 0
                │                       └── INT32
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── b
                │           └── Qualified 0
                │               └── INT32
                ├── ;
                │   └── typcast
                │       ├── Pointer to
                │       │   └── struct A
                │       │       └── a
                │       │           └── Qualified 0
                │       │               └── INT32
                │       └── b
                └── return
                    └── 0


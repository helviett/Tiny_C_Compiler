└── Unit
    ├── Decl
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           ├── a
    │           └── Qualified 0
    │               └── INT32
    ├── Decl
    │   └── InitDeclaratorList
    │       ├── InitDeclarator
    │       │   ├── b
    │       │   └── Qualified 0
    │       │       └── INT32
    │       └── InitDeclarator
    │           ├── c
    │           └── Qualified 0
    │               └── INT32
    ├── Decl
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           ├── N
    │           ├── Qualified 1
    │           │   └── INT32
    │           └── Initializer 
    │               └── 10
    └── Decl
        └── InitDeclaratorList
            └── InitDeclarator
                ├── d
                ├── Pointer to
                │   └── Qualified 1
                │       └── Pointer to
                │           └── Qualified 1
                │               └── INT32
                └── Initializer 
                    └── typcast
                        ├── Pointer to
                        │   └── Qualified 1
                        │       └── Pointer to
                        │           └── Qualified 1
                        │               └── INT32
                        └── 0


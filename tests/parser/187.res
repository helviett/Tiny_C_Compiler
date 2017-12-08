└── Unit
    ├── Decl
    ├── Decl
    │   └── InitDeclaratorList
    │       └── InitDeclarator
    │           ├── a
    │           ├── struct A
    │           │   ├── a
    │           │   │   └── Qualified 0
    │           │   │       └── INT32
    │           │   ├── b
    │           │   │   └── Array of
    │           │   │       ├── Qualified 0
    │           │   │       │   └── INT32
    │           │   │       └── 10
    │           │   └── c
    │           │       └── Array of
    │           │           ├── struct B
    │           │           │   ├── a
    │           │           │   │   └── Qualified 0
    │           │           │   │       └── DOUBLE
    │           │           │   ├── b
    │           │           │   │   └── Qualified 0
    │           │           │   │       └── DOUBLE
    │           │           │   └── c
    │           │           │       └── Array of
    │           │           │           ├── Qualified 0
    │           │           │           │   └── DOUBLE
    │           │           │           └── 12
    │           │           └── 10
    │           └── InitializerList
    │               ├── Initializer 
    │               │   └── 123
    │               ├── InitializerList
    │               │   ├── Initializer 
    │               │   │   └── 1
    │               │   ├── Initializer 
    │               │   │   └── 2
    │               │   ├── Initializer 
    │               │   │   └── 3
    │               │   └── DesignatedInitializer
    │               │       ├── 
    │               │       │   └── DesignatorList
    │               │       │       ├── []
    │               │       │       │   └── 3
    │               │       │       └── []
    │               │       │           └── 5
    │               │       └── Initializer 
    │               │           └── 12
    │               └── DesignatedInitializer
    │                   ├── 
    │                   │   └── DesignatorList
    │                   │       └── .
    │                   │           └── c
    │                   └── InitializerList
    │                       └── InitializerList
    │                           ├── DesignatedInitializer
    │                           │   ├── 
    │                           │   │   └── DesignatorList
    │                           │   │       ├── .
    │                           │   │       │   └── a
    │                           │   │       └── .
    │                           │   │           └── b
    │                           │   └── Initializer 
    │                           │       └── 10
    │                           ├── Initializer 
    │                           │   └── typcast
    │                           │       ├── Qualified 0
    │                           │       │   └── DOUBLE
    │                           │       └── 1
    │                           ├── Initializer 
    │                           │   └── typcast
    │                           │       ├── Qualified 0
    │                           │       │   └── DOUBLE
    │                           │       └── 2
    │                           └── DesignatedInitializer
    │                               ├── 
    │                               │   └── DesignatorList
    │                               │       └── .
    │                               │           └── c
    │                               └── InitializerList
    │                                   ├── Initializer 
    │                                   │   └── typcast
    │                                   │       ├── Qualified 0
    │                                   │       │   └── DOUBLE
    │                                   │       └── 1
    │                                   ├── Initializer 
    │                                   │   └── typcast
    │                                   │       ├── Qualified 0
    │                                   │       │   └── DOUBLE
    │                                   │       └── 1.2
    │                                   └── Initializer 
    │                                       └── typcast
    │                                           ├── Qualified 0
    │                                           │   └── DOUBLE
    │                                           └── 0.123
    └── Decl
        └── InitDeclaratorList
            └── InitDeclarator
                ├── b
                ├── Array of
                │   ├── Array of
                │   │   ├── Qualified 0
                │   │   │   └── INT32
                │   │   └── 12
                │   └── 123
                └── InitializerList
                    ├── InitializerList
                    │   ├── Initializer 
                    │   │   └── 1
                    │   ├── Initializer 
                    │   │   └── 2
                    │   ├── Initializer 
                    │   │   └── 3
                    │   └── Initializer 
                    │       └── 4
                    └── InitializerList
                        ├── Initializer 
                        │   └── 4
                        └── Initializer 
                            └── 5


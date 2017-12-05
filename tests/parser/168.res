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
                │           ├── i
                │           └── Qualified 0
                │               └── INT32
                └── for
                    ├── ;
                    │   └── =
                    │       ├── i
                    │       └── 0
                    ├── ;
                    │   └── <
                    │       ├── i
                    │       └── 10
                    ├── ++'
                    │   └── i
                    └── {}
                        └── BlockItemList
                            ├── continue
                            ├── Decl
                            │   └── InitDeclaratorList
                            │       └── InitDeclarator
                            │           ├── j
                            │           ├── Qualified 0
                            │           │   └── INT32
                            │           └── i
                            ├── for
                            │   ├── ;
                            │   ├── ;
                            │   ├── 
                            │   └── break
                            ├── while
                            │   ├── 1
                            │   └── do
                            │       ├── {}
                            │       │   └── BlockItemList
                            │       │       ├── continue
                            │       │       └── break
                            │       └── 1
                            └── while
                                ├── 2
                                └── {}
                                    └── BlockItemList
                                        ├── continue
                                        └── break


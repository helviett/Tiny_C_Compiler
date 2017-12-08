└── Unit
    ├── FuncDef
    │   ├── Declarator
    │   │   ├── f
    │   │   └── Function returning
    │   │       ├── Pointer to
    │   │       │   └── struct 
    │   │       │       └── a
    │   │       │           └── Qualified 0
    │   │       │               └── INT32
    │   │       └── Params
    │   │           └── #0
    │   │               └── Qualified 0
    │   │                   └── VOID
    │   └── {}
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
                └── ;
                    └── =
                        ├── ->
                        │   ├── FuncCall
                        │   │   └── f
                        │   └── a
                        └── 12


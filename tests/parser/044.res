└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── main
        │   └── Function returning
        │       ├── Qualified 0
        │       │   └── VOID
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
                │           └── Qualified 0
                │               └── INT32
                └── if else
                    ├── &&
                    │   ├── <=
                    │   │   ├── a
                    │   │   └── 10
                    │   └── >
                    │       ├── a
                    │       └── 0
                    ├── ;
                    │   └── `++
                    │       └── a
                    └── if else
                        ├── a
                        ├── {}
                        │   └── BlockItemList
                        │       └── ;
                        │           └── -=
                        │               ├── a
                        │               └── -
                        │                   ├── a
                        │                   └── 12
                        └── ;


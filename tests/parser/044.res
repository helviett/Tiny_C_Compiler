└── Unit
    └── FuncDef
        ├── Declarator
        │   ├── main
        │   └── Function returning
        │       ├── VOID
        │       └── Params
        │           └── #0
        │               └── VOID
        └── {}
            └── BlockItemList
                ├── Decl
                │   └── InitDeclaratorList
                │       └── InitDeclarator
                │           ├── a
                │           └── INT32
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
                        │               └── 12
                        └── ;


└── Unit
    └── FuncDef
        ├── DeclarationSpecifiers
        │   └── int
        ├── Declarator
        │   └── Func Decl
        │       ├── main
        │       └── ParameterList
        │           └── param
        │               ├── DeclarationSpecifiers
        │               │   └── void
        │               └── Declarator
        └── {}
            └── BlockItemList
                ├── Decl
                │   ├── DeclarationSpecifiers
                │   │   └── int
                │   └── InitDeclaratorList
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── a
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── b
                │       ├── InitDeclarator
                │       │   └── Declarator
                │       │       └── longername
                │       └── InitDeclarator
                │           └── Declarator
                │               ├── *
                │               └── pointer
                ├── ;
                │   └── -
                │       └── a
                ├── ;
                │   └── +
                │       └── b
                ├── ;
                │   └── &
                │       └── longername
                ├── ;
                │   └── *
                │       └── pointer
                ├── ;
                │   └── !
                │       └── 0
                ├── ;
                │   └── ~
                │       └── 1
                ├── ;
                │   └── ++'
                │       └── a
                ├── ;
                │   └── --`
                │       └── b
                ├── ;
                │   └── ++'
                │       └── --`
                │           └── longername
                ├── ;
                │   └── sizeof
                │       └── 10
                ├── ;
                │   └── sizeof
                │       └── -
                │           └── 10
                ├── ;
                │   └── sizeof
                │       └── ++'
                │           └── 10
                ├── ;
                │   └── sizeof
                │       └── --`
                │           └── -
                │               └── 10
                ├── ;
                │   └── sizeof()
                │       └── TypeName
                │           ├── SpecQualList
                │           │   └── int
                │           └── Declarator
                ├── ;
                │   └── sizeof()
                │       └── TypeName
                │           ├── SpecQualList
                │           │   └── int
                │           └── Declarator
                │               └── *
                │                   └── *
                ├── ;
                │   └── sizeof()
                │       └── TypeName
                │           ├── SpecQualList
                │           │   └── int
                │           └── Declarator
                │               └── *
                │                   └── TypeQualList
                │                       └── const
                └── return
                    └── 0


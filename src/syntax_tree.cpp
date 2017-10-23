//
// Created by keltar on 10/15/17.
//

#include "../includes/syntax_tree.h"

std::ostream &operator<<(std::ostream &os, SyntaxTree &st)
{
    st.root->Print(os);
    os << std::endl;
    return os;
}

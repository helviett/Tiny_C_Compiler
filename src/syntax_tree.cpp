//
// Created by keltar on 10/15/17.
//

#include "../includes/syntax_tree.h"

std::ostream &operator<<(std::ostream &os, SyntaxTree &st)
{
    std::vector<int> depths(512, 0);
    st.root->Print(os, 0, depths, SubtreeType::Left);
    os << std::endl;
    return os;
}

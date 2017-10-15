//
// Created by keltar on 10/15/17.
//

#include "../includes/syntax_tree.h"

void SyntaxTree::print(std::ostream &os, uint64_t deph, const Node *n) const
{
    if (n != nullptr)
    {
        os << std::string(deph * 4, ' ') << std::endl;
        print(os, deph + 1, n->child);
    }
}

void SyntaxTree::Print()
{

}

std::ostream &operator<<(std::ostream &os, SyntaxTree &st)
{
    std::vector<int> v(500, 0);
    st.root->Print(os, 0, v, SubtreeType::Left);
    return os;
}

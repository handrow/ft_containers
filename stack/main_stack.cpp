#include <stack>
#include "stack.hpp"

template <class _Stack>
void stack_print(_Stack copy, const std::string& prefix = "STACK") {
    std::cout << prefix << ":";
    while (!copy.empty()) {
        std::cout << " " << copy.top();
        copy.pop();
    }
    std::cout << std::endl;
}

int main()
{
    ft::stack<int> s;
    std::stack<int> st;

    s.push(1);
    s.push(2);
    s.push(2);
    s.push(2);
    s.push(2);
    s.push(2);
    s.push(2);
    s.push(2);
    s.push(2);
    stack_print(s, "mine");
    st.push(1);
    st.push(2);
    stack_print(st, "his");
}
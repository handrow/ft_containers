#include <stack>
#include "stack.hpp"
int main()
{
    ft::stack<int> s;

    s.push(1);
    s.push(2);
    for (size_t i = 0; i < s.size(); i++)
        std::cout << s.top() << std::endl;
}
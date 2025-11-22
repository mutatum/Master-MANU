#include <iostream>

template <class L, class F>
class bidule
{
    L lhs;
    F func;

public:
    bidule(L lhs, F func) : lhs(lhs), func(func) {}
    template <class R>
    auto operator>(R &&rhs) -> decltype(func(lhs, rhs)) { return func(std::forward<L>(lhs), std::forward<R>(rhs)); }
};

template <class L, class F>
bidule<L, F> operator<(L &&l, F &&f) { return {std::forward<L>(l), std::forward<F>(f)}; }

class vvector
{
public:
    vvector cross(const vvector &rhs) const { std::cout << "cross\n"; return {}; }
    vvector dot(const vvector &rhs) const { std::cout << "dot\n"; return {}; }
};

auto cross = [](const vvector &lhs, const vvector &rhs) -> vvector
{ return lhs.cross(rhs); };

auto dot = [](const vvector &lhs, const vvector &rhs) -> vvector
{ return lhs.dot(rhs); };

int main()
{
    vvector vg;
    vvector vd;
    vvector result = vg <cross> vd;
    vvector result2 = vg <dot> vd;

    return 0;
}
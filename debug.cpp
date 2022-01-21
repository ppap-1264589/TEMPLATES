#define requires(...) typename std::enable_if<__VA_ARGS__::value, int>::type = 0
template<class Ostream, class Container, requires(is_same<Ostream, ostream>)>
Ostream &operator << (Ostream &os, const Container &container) {
    auto _begin = begin(container), _end = end(container);
    for (auto it = _begin; it != _end;)
    os << "{ "[it != _begin] << *it << ",}"[++it == _end];
    return os;
}
template<class U, class V>
ostream &operator << (ostream &os, const pair<U, V> &p){
    return os << "(" << p.first << ", " << p.second << ")" << "\n";
}
template<class X, class Y>
bool Minim(X &x, const Y &y) {
    X eps = 1e-9;
    return (x - eps > y ? (x = y) : 0);
}
template<class X, class Y>
bool Maxim(X &x, const Y &y) {
    X eps = 1e-9;
    return (x + eps < y ? (x = y) : 0);
}

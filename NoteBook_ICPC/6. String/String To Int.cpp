string int_to_string(int x){
    ostringstream ss;
    ss << x;// << x + 1 << x+2;
    return ss.str();
}

int string_to_int(string s){
    istringstream si(s);
    int x;
    si >> x;
    return x;
}
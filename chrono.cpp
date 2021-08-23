const int MAXDATA = 201;
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<mt19937::result_type> random_number(1, MAXDATA);

int randome(){
    return random_number(RNG);
}
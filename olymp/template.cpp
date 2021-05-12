#include <bits/stdc++.h>
#include <random>

using namespace std;

#define rep(x) for(int i = 0; i < (x); ++i)
#define fo(i, x) for (int (i) = 0; (i) < (x); ++(i))
#define fi first
#define se second
#define re return
#define mp make_pair
#define pb push_back
#define True true
#define False false
#define all(v) (v).begin(), (v).end()
#define edg(a, n) (a), ((a)+(n))
#define max(a, b) (a)>(b)?(a):(b)
#define min(a, b) (a)<(b)?(a):(b)

#define int int64_t

typedef long double ld;
typedef long long ll;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
typedef vector<vector<int>> vvi;
typedef map<std::string, int> mapsi;
typedef map<int, std::string> mapis;

const int inf = 2 * pow(10, 18);

int gcd(int a, int b) {
    if (a < b) swap(a, b);
    return (b) ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * (b / gcd(a, b));
}

int fastpow(int number, int power) {
    int result = 1;
    while (power) {
        if (power & 1)
            result *= number;
        number *= number;
        power >>= 1;
    }
    return result;
}

int fastpow_modulo(int number, int power, int modulo) {
    int result = 1;
    number %= modulo;
    while (power) {
        if (power & 1) {
            result *= number;
            result %= modulo;
        }
        number *= number;
        number %= modulo;
        power >>= 1;
    }
    return result;
}

int dsu_parent[5 * 100 * 1000 + 1];
int dsu_rank[5 * 100 * 1000 + 1];

void make_set(int v) {
    dsu_parent[v] = v;
    dsu_rank[v] = 0;
}

int find_set(int v) {
    if (v == dsu_parent[v])
        return v;
    return dsu_parent[v] = find_set(dsu_parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (dsu_rank[a] < dsu_rank[b])
            swap(a, b);
        dsu_parent[b] = a;
        if (dsu_rank[a] == dsu_rank[b])
            ++dsu_rank[a];
    }
}

template<typename T>
void print(T elem_1) {
    std::cout << elem_1 << '\n';
}

template<typename T1, typename T2>
void print(T1 elem_1, T2 elem_2) {
    std::cout << elem_1 << ' ' << elem_2 << '\n';
}

template<typename T1, typename T2, typename T3>
void print(T1 elem_1, T2 elem_2, T3 elem_3) {
    std::cout << elem_1 << elem_2 << elem_3 << '\n';
}

template<typename T1, typename T2>
void printa(T1 container, T2 size) {
    rep(size) std::cout << container[i] << ' ';
    std::cout << '\n';
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    if (!v.empty()) {
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
        out << "\n";
    }
    return out;
}

template<typename T>
std::istream &operator>>(std::istream &in, std::vector<T> &v) {
    for (int i = 0; i < v.size(); ++i) in >> v[i];
    return in;
}

void io_optimization() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void read_file(const char *in, const char *out) {
    freopen(in, "r", stdin);
    freopen(out, "w", stdout);
}

// ******************************************

bool is_prime(int number) {
    if (number <= 1)
        return false;
    for (int divider = 2; divider * divider <= number; ++divider)
        if (!(number % divider))
            return false;
    return true;
}

vi all_primes(int edge) { // edge is included
    vi primes;
    auto table = new bool[edge + 1]{true, true};
    for (int i = 2; i < edge + 1; ++i) {
        for (int j = i * i; j < edge + 1; j += i) {
            table[j] = true;
        }
    }
    for (int i = 1; i < edge + 1; ++i)
        if (!table[i])primes.push_back(i);
    return primes;
}

int count_primes(int start, int finish) { // edge is included
    auto primes = all_primes(finish);
    return primes.size() - (lower_bound(all(primes), start) - primes.begin());
}

int next_prime(int number) {
    while (!is_prime(++number));
    return number;
}

vi prime_factors(int number) {
    vi factors;
    if (number == 1)factors.push_back(1);
    auto primes = all_primes((int) sqrt(number) + 1);
    for (auto x: primes) {
        while (number % x == 0 && number > 1) {
            factors.push_back(x);
            number /= x;
        }
    }
    return factors;
}

vi factor(int number) {
    vi factors;
    int divider = 2;
    for (; divider * divider < number; ++divider) {
        if (!(number % divider)) {
            factors.push_back(divider);
            factors.push_back(number / divider);
        }
    }
    if (divider * divider + 2 * divider + 1 == number) factors.push_back(divider + 1);
    if (factors.empty())factors.push_back(number);
    sort(all(factors));
    return factors;
}

vector<pair<int, int >> prime_factors_map(int n) {
    vector<pair<int, int>> result;
    auto factors = prime_factors(n);
    int cur = factors[0];
    result.emplace_back(cur, 1);
    for (int i = 1; i < factors.size(); ++i) {
        if (cur == factors[i]) {
            result.back().second++;
        } else {
            cur = factors[i];
            result.emplace_back(cur, 1);
        }
    }
    return result;
}

int euler(int n) {
    int result = 1;
    for (auto x : prime_factors_map(n)) {
        result *= x.second == 1 ? x.first - 1 : pow(x.first, x.second) - pow(x.first, x.second - 1);
    }
    return result;
}

bool ferma(int base, int candidate) {
    return fastpow_modulo(base, candidate - 1, candidate) - 1 == 0;
}

bool is_pseudoprime(int number) {
    random_device generator;
    for (int i = 0; i < 100; ++i) {
        int base = (generator() + 2) % number;
        if (base == 0) base = 2;
        if (!ferma(base, number)) return false;
    }
    return true;
}

// ******************************************

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"

auto split(const vector<string> &s) {
    vector<vector<string> > result;
    vector<string> buf;
    auto sz = s.size();
    for (int i = 0; i < sz; ++i) {
        buf.pb(s[i]);
        if (i + 1 < sz) {
            if (s[i + 1].length() < 3) {
                result.pb(buf);
                buf.clear();
            }
        }
    }
    if (!buf.empty())
        result.pb(buf);
    re result;
}

int m = 1000000000 + 7;

int get_group_ans(const vector<string> &s, int k) {
    int dp = 1;
    int max_digit_len = s[0].length();
    int prev_max_cnt = 0;
    if (s[0].length() + 3 > k)
        prev_max_cnt++;
    for (int i = 1; i < s.size(); ++i) {
        if (s[i][0] != '0') {
            dp *= 2;
            dp -= prev_max_cnt;
            dp %= m;
            if (max_digit_len + 3 <= k)
                max_digit_len += 3;
            if (max_digit_len + 3 > k)
                prev_max_cnt = min(dp, prev_max_cnt + 1);
        } else {
            dp -= prev_max_cnt;
        }
    }
    return dp;
}


signed main() {
    srand(time(nullptr));
    io_optimization();

    print(factor(120));
    print(prime_factors(120));
    print(euler(120));
}

#pragma clang diagnostic pop

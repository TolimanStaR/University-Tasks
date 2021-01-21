#include <bits/stdc++.h>

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

void io_optimization() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

// ******************************************

bool is_prime(int number) {
    for (int divider = 2; divider * divider <= number; ++divider)if (!(number % divider))return false;
    return true;
}

vi all_primes(int edge) {
    vi primes;
    auto table = new bool[edge + 1]{true, true};
    for (int i = 2; i < edge + 1; ++i) {
        for (int j = i * i; j < edge + 1; j += i) {
            table[j] = true;
        }
    }

    for (int i = 1; i < edge + 1; ++i)if (!table[i])primes.push_back(i);
    return primes;
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

bool ferma(int base, int candidate) {
    base = fastpow_modulo(base, candidate - 1, candidate);
    if (base - 1) return false;
    return true;
}


bool is_pseudoprime(int number) {
    for (int i = 0; i < 100; ++i) {
        int base = (abs(random()) + 2) % number;
        if (!ferma(base, number)) return false;
    }
    return true;
}

// ******************************************


signed main() {
    io_optimization();

//    freopen("input.in", "r", stdin);
//    freopen("input.txt", "w", stdout);


    return 0;
}

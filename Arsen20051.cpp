#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define all(x) (x).begin(), (x).end()
#define ll long long
#define ss second
#define ff first

ll p = 31, mod = 1325732621;
ll power[100000];

void Ios()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

bool cmp(pair<pair<ll, ll>, ll>  x, pair<pair<ll, ll>, ll>  y) {
    return x.ff < y.ff;
}

vector<ll> pref(string s) {
    ll n = s.length();
    vector<ll> p(n);

    for (int i = 1; i < n; ++i) {
        ll k = p[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            p[i] = k + 1;
        }
    }
    return p;
}

vector<ll> z_func(string s) {
    ll n = s.length();
    vector<ll> z(n);
    ll l = 0, r = -1;
    for (int i = 1; i < n; ++i) {
        z[i] = max(0LL, min(r - i + 1, i - l));

        while (i + z[i] < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

vector<ll> getHash(const string& s) {
    ll n = s.length();
    vector<ll> H(n);
    H[0] = s[0];
    for (int i = 1; i < n; ++i) {
        H[i] = (H[i - 1] * p + s[i]) % mod;
    }
    return H;
}

ll subHash(ll l, ll r, const vector<ll>& H) {
    ll big = H[r];
    ll small = 0;
    
    if (l > 0) {
        small = (H[l - 1] * power[r - l + 1]) % mod;
    }

    return(big - small + mod) % mod;
}

ll find_period_in_string(const string& s) {
    vector<ll> a = pref(s);
    ll n = s.size();
    ll k = n - a[n - 1];

    if (n % k == 0) {
        return k;
    } else {
        return n;
    }
}

ll manaker(const string& s) {
    ll n = s.length();

    ll ans = 0;
    vector<ll> d1(n), d2(n);

    {
        ll l = 0, r = -1;
        for (ll i = 0; i < n; i++) {
            ll k = i > r ? 0 : min(d1[l + r - i], r - i);
            while (i + k + 1 < n && i - k - 1 >= 0 && s[i - k - 1] == s[i + k + 1]) {
                k++;
            }
            d1[i] = k;
            ans += k;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
    }

    {
        ll l = 0, r = -1;
        for (ll i = 0; i < n; i++) {
            ll k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (i + k < n && i - k - 1 >= 0 && s[i - k - 1] == s[i + k]) {
                k++;
            }
            d2[i] = k;
            ans += k;
            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }
    }

    return ans;
}

int main()
{
    Ios();

    string s;
    cin >> s;
}

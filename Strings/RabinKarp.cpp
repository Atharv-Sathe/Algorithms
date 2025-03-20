#include <iostream>
#include <string>
#include <math.h>

#define mod 1000000
#define base 31

using namespace std;

int rabinKarp(string text, string pat) {
    int m = pat.size();
    int power = 1;
    for (int i = 0; i < m - 1; i++) {
        power = (power * base) % mod;
    }

    int patHash = 0;
    int textHash = 0;
    for (int i = 0; i < m; i++) {
        patHash = (patHash * base + pat[i]) % mod;
        textHash = (textHash * base + text[i]) % mod;
    }

    for (int i = m - 1; i < text.size(); i++) {
        if (textHash < 0) textHash += mod;
        if (textHash == patHash) {
            if (text.substr(i - m + 1, m) == pat) return i - m + 1;
        }

        // Calculating Rolling Hash
        if (i < text.size() - 1) {
            textHash = ((textHash - text[i - m + 1] * power) * base + text[i + 1]) % mod;
        }
    }
    return -1;
}

int main() {
  // string text = "sdfsklkjjlkjlkdfsdfh";
  // string pat = "jj";
  string text, pat;
  cout << "Enter Text and Pattern to Search for:\n";
  cin >> text >> pat;
  int ind = rabinKarp(text, pat);
  cout << ((ind == -1) ? "Pattern Not Found" : "Pattern Found at ind: " + to_string(ind)) << endl;
  return 0;
}

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getLps(string& pattern) {
  int n = pattern.size();
  vector<int> lps(n, 0);

  int prevLps = 0, i = 1;
  while (i < n) {
    if (pattern[i] == pattern[prevLps]) {
      lps[i] = prevLps + 1;
      prevLps++, i++;
    } else if (prevLps == 0) lps[i] = 0, i++;
    else prevLps = lps[prevLps - 1];
  }
  return lps;
}

int kmp(string& text, string& pattern) {
  vector<int> lps = getLps(pattern);

  int i = 0, j = 0; 
  while (i < text.size())
  {
    if (text[i] == pattern[j]) i++, j++;
    else if (j == 0) i++;
    else j = lps[j - 1];

    if (j == pattern.size()) return i - pattern.size();
  }

  return -1;
}

int main() {
  
  // string text = "AAAXAAAA";
  // string pattern = "AAAA";
  // vector<int> lps = getLps(pattern);
  // for (int i: lps) {
  //   cout << i << "\n";
  // }

  string text, pattern;
  cout << "Enter text followed by pattern to search:\n";
  cin >> text >> pattern;
  cout << kmp(text, pattern);

  return 0;
}
 // CSS 343 · PA4 — implementation SKELETON. fileLines is given; the four
// graded functions are TODOs. Port your ICA 14 lcs and ICA 15 editDistance
// thinking — the DP is the same, the keys change (lines instead of chars).
#include "diff.h"
#include <algorithm>

// ---- GIVEN — read a stream into lines (do not change) ----------------------
vector<string> fileLines(istream& in) {
    vector<string> v;
    string s;
    while (getline(in, s)) v.push_back(s);
    return v;
}

long lcsLines(const vector<string>& a, const vector<string>& b) {
    // TODO: the LCS VALUE only, with TWO ROLLING ROWS — O(min(n,m)) memory.
    //       This must work on files whose full n×m table would not fit
    //       (the --stat mode and the grader both count on it).
    //(void)a; (void)b;
    //return 0;
    if(a.size() < b.size()){
        return lcsLines(b,a);
    }
    int m = a.size();
    int n = b.size();
    if(n == 0) return 0;
    vector<long> prev(n+1, 0);
    vector<long> curr(n+1, 0);
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(a[i-1] == b[j-1]){
                curr[j] = prev[j-1] + 1;
            }else{
                curr[j] = max(prev[j], curr[j-1]);
            }
        }
        prev = curr;
    }
    //finally
    return prev[n];
}

vector<Edit> diffLines(const vector<string>& a, const vector<string>& b) {
    // TODO: 1) strip the common PREFIX and SUFFIX (they become ' ' edits —
    //          this is what keeps real inputs inside the n*m budget);
    //       2) full LCS table over what remains;
    //       3) TRACEBACK into an edit script. Convention: within a changed
    //          run, '-' lines come before '+' lines (mind that a backward
    //          walk reverses your tie-break!).
    //(void)a; (void)b;
    //return {};
    int m = a.size();
    int n = b.size();
    //strip
    int start = 0;
    while(start < m && start < n && a[start] == b[start]){
        start++;
    }
    int enda = m-1;
    int endb = n-1;
    while(enda >= start && endb >= start && a[enda] == b[endb]){
        enda--;
        endb--;
    }
    //LCA table
    vector<string> atrim(a.begin()+start, a.begin() + enda + 1);
    vector<string> btrim(b.begin()+start, b.begin() + endb + 1);
    int mt = atrim.size();
    int nt = btrim.size();
    vector<vector<int>> L(mt+1, vector<int>(nt+1 , 0));
    for(int i = 1; i <= mt; i++){
        for(int j = 1; j <= nt; j++){
            if(atrim[i-1] == btrim[j-1]){
                L[i][j] = L[i-1][j-1] + 1;
            }else{
                L[i][j] = max(L[i-1][j], L[i][j-1]);
            }
        }
    }
    //traceback to result, or edit script
    vector<Edit> tedit;
    int i = mt;
    int j = nt;
    while(i > 0 || j > 0){
        if(i > 0 && j > 0 && (atrim[i-1] == btrim[j-1])){
            tedit.push_back({' ', atrim[i-1]});
            i--;
            j--;
        }else if(i > 0 && (j==0 || L[i-1][j] > L[i][j-1])){
            tedit.push_back({'-', atrim[i-1]});
            i--;
        }else{
            tedit.push_back({'+', btrim[j-1]});
            j--;
        }
    }
    reverse(tedit.begin(), tedit.end());
    vector<Edit> res;
    for(int k = 0; k < start; k++){
        res.push_back({' ', a[k]});
    }
    res.insert(res.end(), tedit.begin(), tedit.end());

    for(int k = enda + 1; k < m; k++){
        res.push_back({' ', a[k]});
    }
    return res;
}

string unifiedDiff(const vector<string>& a, const vector<string>& b, int context) {
    // TODO: group the edit script into hunks — runs of changes plus `context`
    //       common lines on each side — headed "@@ -start,count +start,count @@".
    //       Prefix each body line with ' ', '-' or '+'. "" if identical.
    //       Check yourself against expected-unified.txt.
    //(void)a; (void)b; (void)context;
    //return "";
    //To check if there has been changes or not, check for ' '
    vector<Edit> scrip = diffLines(a, b); //escript or edit script
    vector<int> change;
    for(int i = 0; i < scrip.size(); i++){
        if(scrip[i].op != ' ') change.push_back(i);
    }
    if(change.empty()) return "";

    int N = scrip.size();
    vector<int> al(N+1, 0);
    vector<int> bl(N+1, 0);
    int acur = 1;
    int bcur = 1;
    for(int i = 1; i < N; i++){
        al[i] = acur;
        bl[i] = bcur;
        
    }
    
}

string markLine(const string& a, const string& b) {
    // TODO: the SAME DP one level down — characters instead of lines. Render
    //       the traceback as wdiff markup: [-deleted-] and {+inserted+},
    //       merging consecutive same-op characters into one bracket pair.
    (void)a; (void)b;
    return "";
}

#include <bits/stdc++.h>
using namespace std;
int main() {
    int n = 0;
    vector<vector<int>> lvl(6, vector<int>());
    for (int i = 0; i < 6; i++) {
        int m;
        cin >> m;
        n += m;
        lvl[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> lvl[i][j];
        }
    }
    vector<vector<vector<int>>> g(n, vector<vector<int>>());
    for (int i = 0; i < n; i++) {
        int cnt;
        cin >> cnt;
        g[i].resize(cnt);
        for (int j = 0; j < cnt; j++) {
            int cnt_j;
            cin >> cnt_j;
            g[i][j].resize(cnt_j);
            for (int k = 0; k < cnt_j; k++) {
                cin >> g[i][j][k];
            }
        }
    }
    cout << "lol" << endl;
    vector<int> priority(lvl[2].size());
    for (int i = 0; i < lvl[2].size(); i++) {
        cin >> priority[i];
    }
    int lvl5, lvl3_1, lvl3_2, lvl3_3;
    int min_courses_count;
    cin >> lvl5 >> lvl3_1 >> lvl3_2 >> lvl3_3 >> min_courses_count;
    int ans_mask = 0;
    int ans_course_cnt = n;
    int ans_value = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask & (1 << lvl5)) ||
            !(mask & (1 << lvl3_1)) ||
            !(mask & (1 << lvl3_2)) ||
            !(mask & (1 << lvl3_3))) {
            continue;
        }
        if (__builtin_popcount(mask) < min_courses_count) {
            continue;
        }
        if (__builtin_popcount(mask) > ans_course_cnt) {
            continue;
        }
        int current_value = 0;
        for (int course : lvl[2]) {
            if (mask & (1 << course)) {
                current_value += priority[course];
            }
        }
        if (current_value < ans_value) {
            continue;
        }
        vector<bool> used(n, false);
        bool is_correct = true;
        for (auto current_lvl : lvl) {
            for (auto course : current_lvl) {
                if (!(mask & (1 << course))) {
                    continue;
                }
                int cnt = 0;
                for (int i = 0; i < g[course].size(); i++) {
                    for (int prev_course:  g[course][i]) {
                        if (used[prev_course]) {
                            cnt++;
                            break;
                        }
                    }
                }
                if (cnt != g[course].size()) {
                    is_correct = false;
                } else {
                    used[course] = true;
                }
            }
        }
        if (is_correct) {
            ans_mask = mask;
            ans_course_cnt = __builtin_popcount(mask);
            ans_value = current_value;
        }
    }
    if (min_courses_count == n) {
        cout << "No solution";
        return 0;
    }
    cout << "Courses:\n";
    for (int i = 0; i < n; i++) {
        if(ans_mask & (1 << i)) {
            cout << i << " ";
        }
    }

    return 0;
}
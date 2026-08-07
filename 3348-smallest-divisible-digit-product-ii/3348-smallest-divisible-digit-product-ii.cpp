#include <string>
#include <vector>
#include <array>
#include <algorithm>

class Solution {
public:
    string smallestNumber(string num, long long t) {
        
        std::array<int, 4> t_factors = {0, 0, 0, 0};
        long long temp_t = t;
        const std::array<int, 4> primes = {2, 3, 5, 7};
        
        for (int i = 0; i < 4; ++i) {
            while (temp_t % primes[i] == 0) {
                t_factors[i]++;
                temp_t /= primes[i];
            }
        }

        // If t contains prime factors other than 2, 3, 5, 7, it's impossible
        if (temp_t > 1) {
            return "-1";
        }

        // Prime factor representations for digits '1' through '9'
        const std::array<std::array<int, 4>, 10> digit_factors = {{
            {0, 0, 0, 0}, // '0' (unused)
            {0, 0, 0, 0}, // '1'
            {1, 0, 0, 0}, // '2'
            {0, 1, 0, 0}, // '3'
            {2, 0, 0, 0}, // '4'
            {0, 0, 1, 0}, // '5'
            {1, 1, 0, 0}, // '6'
            {0, 0, 0, 1}, // '7'
            {3, 0, 0, 0}, // '8'
            {0, 2, 0, 0}  // '9'
        }};

        // Greedily groups needed factors into minimal count of single digits 2..9
        auto get_min_digits = [](const std::array<int, 4>& needed_factors) -> std::string {
            int c2 = std::max(0, needed_factors[0]);
            int c3 = std::max(0, needed_factors[1]);
            int c5 = std::max(0, needed_factors[2]);
            int c7 = std::max(0, needed_factors[3]);

            int c9 = c3 / 2;
            c3 %= 2;

            int c8 = c2 / 3;
            c2 %= 3;

            int c4 = c2 / 2;
            c2 %= 2;

            int c6 = 0;
            if (c3 == 1 && c2 == 1) {
                c6 = 1;
                c3 = 0;
                c2 = 0;
            } else if (c3 == 1 && c4 == 1) {
                c6 = 1;
                c2 = 1;
                c3 = 0;
                c4 = 0;
            }

            std::string res;
            res.append(c2, '2');
            res.append(c3, '3');
            res.append(c4, '4');
            res.append(c5, '5');
            res.append(c6, '6');
            res.append(c7, '7');
            res.append(c8, '8');
            res.append(c9, '9');
            return res;
        };

        int n = num.length();

        
        std::vector<std::array<int, 4>> pref_factors(n + 1, {0, 0, 0, 0});
        int first_zero_idx = n;

        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero_idx = i;
                break;
            }
            int d = num[i] - '0';
            for (int k = 0; k < 4; ++k) {
                pref_factors[i + 1][k] = pref_factors[i][k] + digit_factors[d][k];
            }
        }

        
        if (first_zero_idx == n) {
            bool ok = true;
            for (int k = 0; k < 4; ++k) {
                if (pref_factors[n][k] < t_factors[k]) {
                    ok = false;
                    break;
                }
            }
            if (ok) return num;
        }

        
        for (int i = n - 1; i >= 0; --i) {
            if (i > first_zero_idx) continue;

            int current_digit = num[i] - '0';
            for (int d = current_digit + 1; d <= 9; ++d) {
                std::array<int, 4> needed;
                for (int k = 0; k < 4; ++k) {
                    needed[k] = t_factors[k] - pref_factors[i][k] - digit_factors[d][k];
                }

                std::string req_digits = get_min_digits(needed);
                int remaining_space = n - 1 - i;

                if (static_cast<int>(req_digits.length()) <= remaining_space) {
                    int ones_needed = remaining_space - req_digits.length();
                    std::string res = num.substr(0, i);
                    res += std::to_string(d);
                    res.append(ones_needed, '1');
                    res += req_digits;
                    return res;
                }
            }
        }

       
        std::string req_digits = get_min_digits(t_factors);
        int target_len = std::max(n + 1, static_cast<int>(req_digits.length()));
        int ones_needed = target_len - req_digits.length();

        std::string res;
        res.append(ones_needed, '1');
        res += req_digits;
        return res;
    }
};
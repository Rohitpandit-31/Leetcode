class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr, sc;
        vector<vector<int>> id(m, vector<int>(n, -1));

        int cnt = 0;

        // Find S and assign an ID to every L
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if (classroom[i][j] == 'L') {
                    id[i][j] = cnt++;
                }
            }
        }

        // No litter
        if (cnt == 0)
            return 0;

        int fullMask = (1 << cnt) - 1;

        /*
            bestEnergy[r][c][mask]

            Maximum energy with which we have reached
            (r, c) after collecting the litter represented
            by mask.
        */

        vector<vector<vector<int>>> bestEnergy(
            m,
            vector<vector<int>>(n, vector<int>(1 << cnt, -1))
        );

        // r, c, remaining energy, mask
        queue<array<int, 4>> q;

        q.push({sr, sc, energy, 0});

        bestEnergy[sr][sc][0] = energy;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            int size = q.size();

            while (size--) {

                auto [r, c, e, mask] = q.front();
                q.pop();

                // All litter collected
                if (mask == fullMask)
                    return moves;

                // Can't make another move
                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {

                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    // One move costs one energy
                    int ne = e - 1;

                    int nmask = mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    /*
                        If we have already reached this
                        position with the same mask and
                        MORE energy, this state is useless.
                    */
                    if (bestEnergy[nr][nc][nmask] >= ne)
                        continue;

                    bestEnergy[nr][nc][nmask] = ne;

                    q.push({nr, nc, ne, nmask});
                }
            }

            moves++;
        }

        return -1;
    }
};
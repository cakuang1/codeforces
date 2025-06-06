#include <bits/stdc++.h>
using namespace std;

/*
  Sqrt‐decomposition solution to “Holes” (Problem E).

  We keep:
    - a[i]:   current power of hole i.
    - nxt[i]: immediate jump target = min(n+1, i + a[i]).
    - go[i]:  first hole in a different block (or n+1) reached by repeatedly
              jumping from i, staying within i’s block.
    - tot[i]: number of in‐block jumps from i to reach go[i].

  Blocks of size num = floor(sqrt(n)).  Block b covers indices [L..R],
  where L = (b-1)*num + 1, R = min(n, b*num).  belong[i] = block index of i.

  “init()” builds go[] and tot[] by scanning each block from right→left.
  Type 0 update rebuilds exactly one block in O(num).  Type 1 query hops
  block‐to‐block in O(#blocks) and then “unwinds” the last block to find
  the final hole.
*/

static const int MAXN = 100000 + 5;

int n, m;
int a[MAXN], nxt[MAXN];    // a[i] = power of hole i; nxt[i] = min(n+1, i+a[i])
int belong[MAXN];          // belong[i] = block index of hole i
int Lft[MAXN], Rgt[MAXN];  // Lft[b], Rgt[b] = left/right endpoints of block b
int goTo[MAXN], tot[MAXN]; // goTo[i] = first outside‐block index; tot[i] = jumps to reach goTo[i]

int numBlocks, blockSize;

void initBlocks() {
    // Compute blockSize = floor(sqrt(n)), ensuring ≥1
    blockSize = (int) sqrt(n);
    if (blockSize <= 0) blockSize = 1;

    // Number of blocks
    numBlocks = (n + blockSize - 1) / blockSize;

    // Assign each i ∈ [1..n] to a block index in [1..numBlocks]
    for (int i = 1; i <= n; i++) {
        belong[i] = (i - 1) / blockSize + 1;
    }

    // Compute each block's [Lft[b]..Rgt[b]] and build goTo[]/tot[] right→left
    for (int b = 1; b <= numBlocks; b++) {
        Lft[b] = (b - 1) * blockSize + 1;
        Rgt[b] = min(n, b * blockSize);

        for (int i = Rgt[b]; i >= Lft[b]; i--) {
            int j = nxt[i];  // immediate jump from i
            if (j > Rgt[b]) {
                // Jump goes outside block b (possibly > n)
                tot[i] = 1;
                goTo[i] = j;
            } else {
                // Jump stays within block b: chain from j
                tot[i] = tot[j] + 1;
                goTo[i] = goTo[j];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read n (#holes) and m (#queries)
    scanf("%d %d", &n, &m);

    // Read initial powers and set nxt[i]
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        int jump = i + a[i];
        nxt[i] = (jump > n ? n + 1 : jump);
    }

    // Build initial block decomposition
    initBlocks();

    while (m--) {
        int type;
        scanf("%d", &type);

        if (type == 0) {
            // Update: “0 x y” means set a[x] = y
            int x, y;
            scanf("%d %d", &x, &y);
            a[x] = y;
            int jump = x + y;
            nxt[x] = (jump > n ? n + 1 : jump);

            // Rebuild the entire block containing x, from right→left
            int b = belong[x];
            for (int i = Rgt[b]; i >= Lft[b]; i--) {
                int j = nxt[i];
                if (j > Rgt[b]) {
                    tot[i] = 1;
                    goTo[i] = j;
                } else {
                    tot[i] = tot[j] + 1;
                    goTo[i] = goTo[j];
                }
            }
        }
        else {
            // Query: “1 x” means throw a ball into hole x
            int x;
            scanf("%d", &x);

            int totalJumps = 0;
            int lastHole = x;
            int curr = x;

            // Block‐by‐block hopping
            while (curr <= n) {
                totalJumps += tot[curr];
                lastHole = curr;
                curr = goTo[curr];
            }

            // Unwind within the final block to find the exact last hole
            int y = lastHole;
            while (y <= n) {
                lastHole = y;
                y = nxt[y];
            }

            printf("%d %d\n", lastHole, totalJumps);
        }
    }

    return 0;
}

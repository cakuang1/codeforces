// a[i] = how many of Alice’s hand‐type i (0=Rock,1=Paper,2=Scissors)
// b[j] = how many of Bob’s hand‐type j

vector<pair<int,int>> blockers = {
    {0,0}, // AliceRock vs BobRock (tie)
    {0,2}, // AliceRock vs BobScissors (Bob wins)
    {1,1}, // AlicePaper vs BobPaper (tie)
    {1,0}, // AlicePaper vs BobRock (Bob wins)
    {2,2}, // AliceScissors vs BobScissors (tie)
    {2,1}  // AliceScissors vs BobPaper (Bob wins)
};

int bestMinWins = INT_MAX;
sort(blockers.begin(), blockers.end());
do {
    // copy the original counts
    auto A = a, B = b;
    // “Use up” as many non‐win matchups as possible in this order:
    for (auto &pr : blockers) {
        int i = pr.first, j = pr.second;
        int can = min(A[i], B[j]);
        A[i] -= can;
        B[j] -= can;
    }
    // Now A[i], B[j] are leftover.  Those can only form Alice‐win pairs:
    int aliceWins =
       min(A[0], B[1])   // Rock vs Paper
     + min(A[1], B[2])   // Paper vs Scissors
     + min(A[2], B[0]);  // Scissors vs Rock

    bestMinWins = min(bestMinWins, aliceWins);
} while (next_permutation(blockers.begin(), blockers.end()));



// minimuzeize moeny lose w


//  projecsts not chosen + machines chosenw er

//wrespsetn s] eahc temr win r aflwro wgparhw 

// lose w w
// wmin cut wr r
// wesum  fsal wlerssdgse corss resdi wew
// preojscst i needs wernmmachsien j we

// weawlwaysd weeasi
// wcit wec ewcos rwminizmei ers we 

// wgneraliywew viewwthe cvgpawrh r we
// not chosen wthen wewe tu wer
// wchose wtth nwerwe wer wcut we 
//wmsut wrals wbe weron wetwt wer
// wcheapest w wdpensdcsy webrekaign werconficguareting wthe only cuts it ever wewcinosderis are cavalid proejct amchiens bominatison wr
// wer wdsetwnru wwtewh cheastser er
// if  wewe wcosniwer wtw wrenot e w
// wthen werer dont wrwened wtowe removwetshi wer
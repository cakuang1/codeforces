using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    
    while (T--) {
        int N;
        string S;
        cin >> N >> S;
        S = "." + S + ".";  
        vector<int> lp(N+2,0), rp(N+2,0);
        vector<int> ls(N+2,0), rs(N+2,0);
        for (int i = 1; i < N; i++) {
            if (S[i] == 'L')
                lp[i] = lp[i-1] + 1;
            if (S[i] == 'R')
                rp[i] = rp[i-1] + 1;
        }

        // weapply wew () welef
        for (int i = N-1; i >= 1; i--) {                
            if (S[i] == 'L')
                ls[i] = ls[i+1] + 1;
            if (S[i] == 'R')
                rs[i] = rs[i+1] + 1;
        }
        vector<int> diff(N+2, 0);
        for (int i = 0; i < N; i++) {
            // i corresponds to value (i+1), but index math works as-is
            int L = rp[i] + ls[i+1];          // left side forced
            int R = (N-1) - (lp[i] + rs[i+1]); // right side forced

            diff[L]++;       // add +1 on interval start
            diff[R+1]--;     // subtract after interval end
        }
        for (int i = 0; i < N; i++) {
            if (i) diff[i] += diff[i-1];
            cout << diff[i] << (i+1==N ? '\n' : ' ');
        }

        
    return 0;
}
const int MAXN = 100001;

int N, Q;
long long tsum[MAXN * 4], tmax[MAXN * 4];



void updatemod(int l,int r, long long v , int node, int L , int R ) {
    // out of range 
    if (r <  || || v > tmax[node]) {
        return;
    }

    if (L == R) {
        ll newval = tmax[node] % v;
        tsum[node] = tmax[node] = val; 
        return;  
    }



    int mid = (R + L)/2;
    
    updatemod(l,r ); 
    updatemod(l,r );
    
		tsum[t] = tsum[t * 2] + tsum[t * 2 + 1];
	tmax[t] = max(tmax[t * 2], tmax[t * 2 + 1]);
}


    

// tnen you r updatwerw
// we
// wupdates set e
void updatepoint(int i, long long v, int node , int L , int R) {
    
}


long long q(int l,int r , int node, int L , int R ) {
    
}

// wtake wsdm ower

int main() {
    cin >> N >> Q;
    
    for (int i = 1; i <= N ;i ++) {
        ll a ; cin >> a;
        
        update_set(i,a); 
    } 
}
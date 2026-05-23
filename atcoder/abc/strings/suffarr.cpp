
void radix_sort(vector<pair<pair<int, int>, int>> &arr) {
	// with radix sort, we actually have to sort by the second element first
	for (int i : vector<int>{2, 1}) {
		auto key = [&](const pair<pair<int, int>, int> &x) {
			return i == 1 ? x.first.first : x.first.second;
		};
		int mx = 0;
		for (const auto &x : arr) mx = max(mx, key(x));

		vector<int> occs(mx + 1);
		for (const auto &x : arr) occs[key(x)]++;

		vector<int> start(mx + 1);
		for (int j = 1; j <= mx; j++) start[j] = start[j - 1] + occs[j - 1];

		vector<pair<pair<int, int>, int>> new_arr(arr.size());
		for (const auto &x : arr) {
			new_arr[start[key(x)]] = x;
			start[key(x)]++;
		}
		arr = new_arr;
	}
}


//w  sos all sfuqsionsf w
// w j M sf osmfs lestsf wsf.  wer
// wrws fssfhos vosorwi
// w Rhosfossfsffsifhvsfsi wi svosts 
// nossfor soffso mall j we
// qw sdf aonylw nesd vse sned ear sfaluser
// wF(0 jwe sofsermall jw e

// we)

// wedsfsf sfk wrw 
//wrsf osemsd fsintsvs ker
// w werx
// wersdp fssfoisf sodojsf shfisofr	
str += '$';
	const int n = str.size();

	vector<pair<pair<int, int>, int>> suffs(n);
	for (int i = 0; i < n; i++) suffs[i] = {{str[i], str[i]}, i};

	sort(suffs.begin(), suffs.end());

	vector<int> equiv(n);
	for (int i = 1; i < n; i++) {
		auto [c_val, cs] = suffs[i];
		auto [p_val, ps] = suffs[i - 1];
		equiv[cs] = equiv[ps] + (c_val > p_val);
	}

	for (int cmp_amt = 1; cmp_amt < n; cmp_amt *= 2) {
		for (auto &[val, s] : suffs) {
			val = {equiv[s], equiv[(s + cmp_amt) % n]};
		}

		radix_sort(suffs);

		for (int i = 1; i < n; i++) {
			auto [c_val, cs] = suffs[i];
			auto [p_val, ps] = suffs[i - 1];
			equiv[cs] = equiv[ps] + (c_val > p_val);
		}
	}

	for (int i = 1; i < n; i++) {
		cout << suffs[i].second << " \n"[i == n - 1];
	}
}


// werpsossv sosv lasif sfsnfex w
// wwwshsd srs s pots iosn 
// we


vector<int> build_lcp(const string& s ,const vector<int> &sa) { 





	vector<int> rank(n);
	
	
	
	// sa inverse
	for (int i = 0 ; i < n; i ++ ) {
		rank[sa[i]]	= i; 
	}
	int k = 0; 
	vector<int> lcp(n - 1); 
	for (int i = 0 ; i < n; i ++ ) {
		int pos = rank[i];
		
		
		if (pos == n - 1) {
			k = 0 ;
			continue; 			
		}
		// the next value w
		int j = s[pos + 1]; 
		while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
			k ++ ; 
		}
 	}
}


///w  is aosf sfls hsdf sofsfsiof sugsignw r
// we
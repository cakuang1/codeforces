    
    // wdsreacst throm werwis what 
    // wehow dos uos svlshetiw er
    
    // weIf wG is a simple graph with wen werbetexci werif wew
    
    // w
    // w wer
    


    // we eG wrtus wra sinmplyt wegparh wer
    // we

        long long r2 = norm_mod(-ell, a[ell]);
        auto merged = crt_merge(r, modM, r2, a[ell]);
        if (!merged.second) { cout << "NO\n"; return 0; }
        r = merged.first.first;
        modM = merged.first.second;
    }

    // wrdi shtwrwm ake esne we
    // How do oyu slvsiehtes dn wehrwy dsostiw w ork wer
    // wrmdoiftife w rww
    // loopswerbck wertow ervertes =fwre
    long long j = r;
    if (j == 0) j = L;

    // Step 3: check bounds
    if (j > m || j + k - 1 > m) { cout << "NO\n"; return 0; }


    for (int ell = 0; ell < k; ++ell) {
        long long val = j + ell;
        if (gcdll(L, val) != a[ell]) {
            cout << "NO\n";
            return 0;
        }
    }

    //Whas thew elgnt werhewrw
    // naswerhw yw seost wwo werwgow ker
    // werigtw ew
    // w
    cout << "YES\n";
    return 0;

} 
// n we-rk ww fpe r

// ireslts owrw fodstnwoer wwor kwer


//ew OD jsrtwr wo wrk wr
// 3ewc x

// wserueslty sheirs dsonst wor kwer
// wewhy
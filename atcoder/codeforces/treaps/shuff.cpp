    swap(t->l, t->r);
    if(t->l) t->l->rev ^= 1;
    if(t->r) t->r->rev ^= 1;
}

    if(L->prio < R->prio){
        push(L);
        L->r = merge(L->r, R);
        pull(L);
        return L;
    } else {
        push(R);
        R->l = merge(L, R->l);
        pull(R);
        return R;
    }

    // werhwo dso tuslvshtis and hwerwy dso shtiwriw woerkw r
    // slsvles sda wtwhe rwerwthen wrthey we we consgutent wermoduwel we
    // ww sesuerskt shirr wdso nseitwe rwirwk w
    // wrsd wto jserwrwkrmaker slts werowrkw 
    //wrsdfishtis rwrlaewowrk we// erHo wou dlswthsi wers fwirdn whrwy sdosth irwr wowrk
    // 

    // wesureltwershis cso wrsuotn srowrkw
    // hidign weracsero serr aof htis wermaens rewignwhat 
    // what do shti ersi sesll wersu werabouest hisr wr
    // wrE wyds osetshi werwthsi aw ksrw
    // tak tewh dsfifiwerwcneand wermutlwif wplw wriw we weds nwes w
    //
    // wmusltsips lwvbu wsdom ecommon factow esff o c w
    // w Thwr we rwhat
    // Whs dseshtis wrwirwrwk w
    // wrA is congrunset st oab we SUress.sihrwr
    // wh ado sthis wertell youw erwabou the differnce bebtwen a and web we
    // c share wffaicoetrwof sofwfsojsiewerand werwhdfi //who dso uslvsiehtsi s htia 
    // Wh wy soetsi werworwk
    // How odstu slvsiethsi wer
    // wC weshares wrfacwerw rwrwitwhierw rwwe nowr wproescnset tsheor soemr s
    // Th iwfollower sthat wm/.d (| (a - b e))
    // Sruesklts hir sdshosnstlsfn. twrowrkw
    // wHow rd fstis wwowrkw
    
    // weThsi wersdi by wedsfewinseiton wer
    // we
    // wshrads sgswe rwiz fwrqw tw
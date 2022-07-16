int merge(int p, int q, int l, int r) {
    if(!p || !q) return p + q;
    if(l == r) {
        //维护信息，一般是t[p].val += t[q].val等
        // t[p].val.first += t[q].val.first;
        return p;
    }
    int mid = l + r >> 1;
    t[p].l = merge(t[p].l, t[q].l, l, mid);
    t[p].r = merge(t[p].r, t[q].r, mid + 1, r);
    // pushup();
    //  t[p].val = max(t[t[p].l].val, t[t[p].r].val);
    return p;
}
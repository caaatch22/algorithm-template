namespace SegTree {

struct Info {
    int v, x;
    Info(int v=0,int x=-1) : x(x), v(v) {}
    bool operator>(const Info &o) const {
        if(v == o.v) return x < o.x;
        else return v > o.v;
    }
};

Info max(const Info x, const Info y) {
    if(x > y) return x;
    else return y;
}

Info merge(const Info &a, const Info &b) {
    return max(a, b);
}

struct Node {
    Node *l,*r;
    Info val;
    Node() : l(nullptr), r(nullptr), val() {}
};

void pull(Node *&p) {
    p->val = merge(p->l == nullptr ? Info() : p->l->val, p->r == nullptr ? Info() : p->r->val);
}

// query(t, 0, n, query_left, query_right)
Info query(Node *t, int l, int r, int le, int ri) { // [le, ri)
    //   l    r
    // ooxxxxxooo
    // L R LR L R
    // xxooxooxxo
    if(ri <= l || r <= le || t == nullptr) {
        return Info();
    }
    if(le <= l && r <= ri) {
        return t->val;
    }
    int mid = l + r >> 1;
    return merge(query(t->l, l, mid, le, ri), query(t->r, mid, r, le, ri));
}

void modify(Node *&t, int l, int r, int x, int v) { // [l,r)
    if(t == nullptr) {
        t = new Node();
    }
    if(r - l == 1) {
        t->val.v += v;
        t->val.x = x;
        return;
    }

    int mid = l + r >> 1;
    if(x < mid) {
        modify(t->l, l, mid, x, v);
    }else {
        modify(t->r, mid, r, x, v);
    }
    pull(t);
}

Node* merge(Node *&t, Node *&o, int l, int r) { // [l,r)
    if(t == nullptr) return o;
    else if(o == nullptr) return t;

    Node *p = new Node();

    if(r - l == 1) {
        p->val = t->val;
        p->val.v += o->val.v;
        return p;
    }

    int mid = l + r >> 1;
    p->l = merge(t->l, o->l, l, mid);
    p->r = merge(t->r, o->r, mid, r);
    pull(p);
    return p;
}

}
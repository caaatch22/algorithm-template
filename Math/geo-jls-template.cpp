#define vec point
typedef long double db ; //卡精度就换long double
const db eps = 1e-6 ; //调参
const db pi = acos(-1.0) ;
int sgn(db x)
{
	if(x < -eps) return -1 ;
	else if (x > eps)  return 1 ;
	else return 0 ;
}
int cmp(db x , db y)
{
	return sgn(x - y) ;
}
void print(int num , db x)
{
	cout << fixed << setprecision(num) << x << '\n' ;
}
struct point
{
	db x , y ;
	point(){}
	point(db x2 , db y2)
	{
		x = x2 , y = y2 ;
	}
	point operator + (const point& s)const{return (point){x + s.x , y + s.y} ;}
	point operator - (const point& s)const{return (point){x - s.x , y - s.y} ;}
	point operator * (const db& k)const{return (point){x * k , y * k} ;}
	point operator / (const db& k)const{return (point){x / k , y / k} ;}
	bool operator < (point b) const
	{
		return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x ;
	}
	bool equal(point p2)
	{
		return cmp(x , p2.x) == 0 && cmp(y , p2.y) == 0 ;
	}
	db get_angle(){return atan2(y , x) ;} //极角
	db sq(db x) {return x * x ;}
	db dis(point p) //很吃精度，可能需要1e-10或更小的eps
	{
		return sqrtl(sq(x - p.x) + sq(y - p.y)) ; //check sqrt or sqrtl
	}
	db len()
	{
		return sqrtl(sq(x) + sq(y)) ;
	}
	db len2()
	{
		return sq(x) + sq(y) ;
	}
    point unit()
    {
        db w = len() ;
        return (point){x / w , y / w} ;
    }
	vec rotate_left()  //向量逆时针旋转90度
	{
		return vec(-y , x) ;
	}
	vec rotate_right()  //向量顺时针旋转90度
	{
		return vec(y , -x) ;
	}
	point move(db r) //原点沿该点代表的向量方向移动r
	{
		db l = len() ;
		if(sgn(l) == 0)  return *this ;
		else  return point(x * r / l , y * r / l) ;
	}
} ;
db cross(vec s , vec t){return s.x * t.y - s.y * t.x ;} // 叉积
db dot(vec s , vec t){return s.x * t.x + s.y * t.y ;} // 点积
db rad(vec p1 , vec p2){ return atan2(cross(p1 , p2) , dot(p1 , p2)) ;} // 有向弧度
int in_mid(db k1 , db k2 , db k3) // k3 在 [k1,k2] 内
{
	return cmp(k1 , k3) * cmp(k2 , k3) <= 0 ;
}
int in_mid(point p1 , point p2 , point p3)
{
	return in_mid(p1.x , p2.x , p3.x) && in_mid(p1.y , p2.y , p3.y) ;
}
int counter_clockwise(point p1 , point p2 , point p3) // p1 p2 p3 逆时针 1 顺时针 -1 否则 0  
{
    return sgn(cross(p2 - p1 , p3 - p1)) ;
}
struct line
{
	point s , e ; // 点s在直线上，方向向量是e ，半平面在e左侧
	db ang ; //在运算时注意设置ang的值！
	line() {}
	line(point s2 , point e2)
	{
		s = s2 , e = e2 ;
		ang = e.get_angle() ;
	}
	bool operator < (const line& l1)const{return ang < l1.ang ;}
	int onRight(point p){return sgn(cross(e , p - s)) < 0 ;} //点p在直线右侧
	point projection(point p) //p在该直线上的投影点
	{
		db t = dot(e , p - s) / e.len() ;
		return s + e.move(t) ;
	}
	point reflection(point p) //p关于直线的对称点
	{
		point p2 = projection(p) ;
		vec v = p2 - p ;
		return p + v * 2 ;
	}
	db dis_point(point p) //点到直线的距离
	{
		db t = dot(e , p - s) / e.len() ;
		point pp = s + e.move(t) ;
		return p.dis(pp) ;
	}
	db dis_segment_point(point p) //点到线段的距离
	{
		point p1 = s ; //线段p1->p2
		point p2 = s + e ;
		point p3 = projection(p) ;
		if(in_mid(p1 , p2 , p3))  return p.dis(p3) ;
		else  return min(p.dis(p1) , p.dis(p2)) ;
	}
	bool on_segment(point p) //p在线段s->s+e上
	{
		return sgn((p.dis(s) + p.dis(s + e)) - s.dis(s + e)) == 0 ;//
	}
	int direction(point p2) //p0 = s , p1 = s + e 判断p2与向量p0->p1的位置关系
	{
		point p0 = s ;
		point p1 = s + e ;
		db res = cross(p1 - p0 , p2 - p0) ;
		if(sgn(res) > 0)  return 1 ; //p0->p1逆时针旋转得到p0->p2的方向
		else if(sgn(res) < 0)  return 2 ; //p0->p1顺时针旋转得到p0->p2的方向
		else
		{
			db res2 = dot(p1 - p0 , p2 - p0) ;
			if(on_segment(p2))  return 5 ; //p2在线段p0->p1上
			else if(sgn(res2) < 0)  return 3 ; //p0->p1与p0->p2方向相反
			else  return 4 ; //p0->p1与p0->p2方向相同
		}
	}
	int Parallel_Orthogonal(line l2) //判断两条直线平行、正交
	{
		if(sgn(cross(e , l2.e)) == 0)  return 2 ; //平行
		else if(sgn(dot(e , l2.e)) == 0)  return 1 ; //正交
		else  return 0 ;
	}
	point line_intersect(point s1 , point t1 , point s2 , point t2) // 直线交点（点+向量表示直线）
	{
		db x = cross(t2 , s1 - s2) / cross(t1 , t2) ;
		return s1 + t1 * x ;
	} 
	point line_intersect(line l2) //直线交点（点+向量表示直线）
	{ 
		assert(sgn(cross(e , l2.e)) != 0) ;
		return line_intersect(s , e , l2.s , l2.e) ;
	}
	point segment_intersect(line l2) //线段s->s+e与线段l2.s->l2.s+l2.e的交点
	{
		assert(sgn(cross(e , l2.e)) != 0) ;
		return line_intersect(s , e , l2.s , l2.e) ;
	}
	bool can_segment_intersect(line l2) //线段s->s+e与线段l2.s->l2.s+l2.e
	{
		int t1 = sgn(cross(e , l2.s - s)) ;
		int t2 = sgn(cross(e , (l2.s + l2.e) - s)) ;
		int t3 = sgn(cross(l2.e , s - l2.s)) ;
		int t4 = sgn(cross(l2.e , (s + e) - l2.s)) ;
		if(on_segment(l2.s) || on_segment(l2.s + l2.e) 
		|| l2.on_segment(s) || l2.on_segment(s + e))  //端点在另一条线段上的情况
		return true ;
		else if(t1 * t2 < 0 && t3 * t4 < 0)  return true ;
		else  return false ;
	}
	db segment_segment_dis(line l2) //线段s->s+e与线段l2.s->l2.s+l2.e
	{
		if(can_segment_intersect(l2))  return 0.0 ;
		else
		{
			db res = min({s.dis(l2.s) , s.dis(l2.s + l2.e) , (s + e).dis(l2.s) , (s + e).dis(l2.s + l2.e)}) ;
			point t = l2.projection(s) ;
			if(l2.on_segment(t))  res = min(res , s.dis(t)) ;
			point t2 = l2.projection(s + e) ;
			if(l2.on_segment(t2))  res = min(res , (s + e).dis(t2)) ;
			point t3 = projection(l2.s) ;
			if(on_segment(t3))  res = min(res , l2.s.dis(t3)) ;
			point t4 = projection(l2.s + l2.e) ;
			if(on_segment(t4))  res = min(res , (l2.s + l2.e).dis(t4)) ;
			return res ;
		}
	}
	line trans(db r) //半平面u向内平移r
	{
		line v ;
		v.s = s + e.rotate_left().move(r) ;
		v.e = e ;
		v.ang = e.get_angle() ; //注意设置ang的值
		return v ;
	}
} ;
struct Polygon
{
	vector<point> pp ;
	Polygon() {}
	Polygon(int n)
	{
		pp.resize(n) ;
	}
	int size() const
	{
		return pp.size() ;
	}
	void resize(int n)
	{
		pp.resize(n) ;
	}
	point operator [](int id) const
	{
		if(id < 0 || id >= size())  assert(false) ;
		else  return pp[id] ;
	}
	point &operator [](int id) 
	{
		return pp[id] ;
	}
	// 凸包
	// Andrew算法
	// 按照x优先的顺序排序（坐标从小到大）
	// 从第一个点开始遍历，如果下一个点在栈顶的两个元素所连成直线的左边，那么就入栈
	// 否则如果在右边，说明凸包有更优的方案，上次的点出栈，并直到新点在栈顶两个点所在的直线的左边为止
	// 这样求得下凸包，类似方法求得上凸包。
	void Convex_Hull(vector<point> P , vector<point> &res , int flag = 1) // flag = 0 不严格（存在三点共线） flag = 1 严格（不存在三点共线） 
	{
		int n = P.size() ;
		res.resize(0) ;
		res.resize(n * 2) ;
		sort(P.begin() , P.end()) ; 
		int now = -1 ;
		for(int i = 0 ; i < (int)P.size() ; i ++)
		{
			while(now > 0 && sgn(cross(res[now] - res[now - 1] , P[i] - res[now - 1])) < flag)  now -- ;
			res[++ now] = P[i] ;
		}
		int pre = now ;
		for(int i = n - 2 ; i >= 0 ; i --)
		{
			while(now > pre && sgn(cross(res[now] - res[now - 1] , P[i] - res[now - 1])) < flag)  now -- ;
			res[++ now] = P[i] ;
		}
		res.resize(now) ;
	}
	// 半平面交
	// 排序增量算法
	// 1.以逆时针为正方向，建边。(输入方向不确定时，可用叉乘求面积看正负得知输入的顺逆方向。)
	// 2.对线段根据极角排序。
	// 3.去除极角相同的情况下，位置在右边的边。
	// 4.用双端队列储存线段集合L，遍历所有线段。
	// 5.判断该线段加入后对半平面交的影响，(对双端队列的头部和尾部进行判断，因为线段加入是有序的。)。
	// 6.如果某条线段对于新的半平面交没有影响，则从队列中剔除掉。
	// 7.最后剩下的线段集合L，即使最后要求的半平面交。
	int Half_Plane_Intersection(vector<line>L , vector<point> &res) 	//L.push_back({p[i] , p[(i + 1) % m] - p[i]}) ;
	{  
		int n = L.size() ;
		sort(L.begin() , L.end()) ;
		int l = 0 , r = 0 ;
		vector<point> p(n) ;
		vector<line> q(n) ;
		q[0] = L[0] ;
		for(int i = 1 ; i <= n - 1 ; i ++)
		{
			while(l < r && L[i].onRight(p[r - 1]))  r -- ;
			while(l < r && L[i].onRight(p[l]))  l ++ ;
			q[++ r] = L[i] ;
			if (sgn(cross(q[r].e , q[r - 1].e)) == 0)
			{
				r -- ;
				if(!q[r].onRight(L[i].s))  q[r] = L[i] ;
			}
			if(l < r)  p[r - 1] = q[r - 1].line_intersect(q[r]) ;
		}
		while(l < r && q[l].onRight(p[r - 1]))  r -- ;
		if(r - l <= 1)  return 0 ; // 交不存在
		res.clear() ;
		p[r] = q[l].line_intersect(q[r]) ;
		for(int i = l ; i <= r ; i ++)  res.push_back(p[i]) ;
		return 1 ;
	}
	db perimeter(vector<point> A) // 多边形用 vector<point> 表示 , 逆时针 
	{
		db ans = 0 ;
		for(int i = 0 ; i < (int)A.size() ; i ++)  ans += A[i].dis(A[(i + 1) % (int)A.size()]) ;
		return ans ;
	} 
	db area() // 多边形用 vector<point> 表示 , 逆时针 
	{
		db ans = 0 ;
		for(int i = 0 ; i < (int)pp.size() ; i ++)  ans += cross(pp[i] , pp[(i + 1) % (int)pp.size()]) ;
		return fabs(ans) / 2 ;
	}
	bool is_convex(vector<point> A) // 多边形用 vector<point> 表示 , 逆时针 
	{
		int n = A.size() ;
		assert(n >= 3) ;
		bool flag = true ;
		for(int i = 0 ; i < n ; i ++)
		{
			int lst = (i - 1 + n) % n ;
			int nxt = (i + 1) % n ;
			if(sgn(cross(A[lst] - A[i] , A[nxt] - A[i])) > 0)  flag = false ;
		}
		return flag ;
	}
	int contain_point(point p0)  // 不一定是凸的 2 内部 1 边界 0 外部
	{
		int n = pp.size() ;
		int res = 0 ;
		for(int i = 0 ; i < n ; i ++)
		{
			point u = pp[(i - 1 + n) % n] ;
			point v = pp[i] ;
			line l ;
			l.s = u ;
			l.e = v - u ;
			if(l.on_segment(p0))  return 1 ;
			if(cmp(u.y , v.y) > 0)  swap(u , v) ;
			if(cmp(u.y , p0.y) >= 0 || cmp(v.y , p0.y) < 0)  continue ;
			if(sgn(cross(u - v , p0 - v)) < 0)  res ^= 1 ;
		}
		return res << 1 ;
	}
	db Convex_Diameter()
	{
		//原理是凸多边形的凸函数性质
		int now = 0 ;
		int n = pp.size() ;
		db res = 0 ;
		for(int i = 0 ; i < n ; i ++)
		{
			now = max(now , i) ;
			while(true)
			{
				db k1 = pp[i].dis(pp[now % n]) ;
				db k2 = pp[i].dis(pp[(now + 1) % n]) ;
				res = max({res , k1 , k2}) ;
				if(cmp(k2 , k1) > 0)  now ++ ;
				else  break ;
			}
		}
		return res ;
	}
    Polygon line_cut_convex(point p1 , point p2)
    {
        //在已有凸多边形基础上新加一个半平面p1->p2
        //问之后的凸多边形
        int n = pp.size() ;
        line l ;
        l.s = p1 ;
        l.e = p2 - p1 ;
        Polygon res ;
        for(int i = 0 ; i < n ; i ++)
        {
            int w1 = counter_clockwise(p1 , p2 , pp[i]) ;
            int w2 = counter_clockwise(p1 , p2 , pp[(i + 1) % n]) ;
            if(w1 >= 0)  res.pp.push_back(pp[i]) ;
            line l2 ;
            l2.s = pp[i] ;
            l2.e = pp[(i + 1) % n] - pp[i] ;
            if(w1 * w2 < 0)  res.pp.push_back(l.line_intersect(l2)) ;
        }
        return res ;
    }
} ;
struct circle
{
    point o ;
    db r ;
	db area()
	{
		return pi * r * r ;
	}
	int inside(point p2)
	{
		return cmp(r , o.dis(p2)) ;
	}
    circle get_circle(point p1 , point p2 , point p3) //三点确定一个圆
    {
        db a1 = p2.x - p1.x , b1 = p2.y - p1.y , c1 = (a1 * a1 + b1 * b1) / 2 ;
        db a2 = p3.x - p1.x , b2 = p3.y - p1.y , c2 = (a2 * a2 + b2 * b2) / 2 ;
        db d = a1 * b2 - a2 * b1 ;
        point o = (point){p1.x + (c1 * b2 - c2 * b1) / d , p1.y + (a1 * c2 - a2 * c1) / d} ;
        return (circle){o , p1.dis(o)} ;
    }
    vector<point> Tangent_Point_Circle(point p) //沿圆的逆时针方向给出切点，点在圆上也给出两个
    {
        //相似三角形
        assert(cmp(p.dis(o) , r) >= 0) ;
        db a = (p - o).len() ;
        assert(sgn(a) >= 0) ;
        db b = r * r / a ;
        db c = sqrt(max(db(0.0) , r * r - b * b)) ;
        point k = (p - o).unit() ;
        point m = o + k * b ;
        point v = k.rotate_left() * c ;
        return {m - v , m + v} ;
    }
	int check_pos_circle_circle(circle c1 , circle c2) //返回两个圆的公切线数量，即位置关系
	{
		//根据圆心之间的距离及两个圆的半径判断
		if(cmp(c1.r , c2.r) < 0)  swap(c1 , c2) ;
		db d = c1.o.dis(c2.o) ;
		int w1 = cmp(d , c1.r + c2.r) ;
		int w2 = cmp(d , c1.r - c2.r) ;
		if(w1 > 0)  return 4 ; //相离
		else if(w1 == 0)  return 3 ; //外切
		else if(w2 > 0)  return 2 ; //相交
		else if(w2 == 0)  return 1 ; //内切
		else  return 0 ; //内含
	}
	vector<point> get_circle_line(line l) //圆与直线求交点，沿l.e方向的顺序给出交点，相切给出两个
	{
		//投影后勾股定理
		point k = l.projection(o) ;
		db d = r * r - (k - o).len2() ;
		if(sgn(d) < 0)  return {} ;
		vec v = l.e.unit() * sqrtl(max((db)0.0 , d)) ;
		return {k - v , k + v} ;
	}
	vector<point> get_circle_circle(circle c1 , circle c2) //两个圆的交点，沿圆c1逆时针给出，相切给出两个
	{
		//余弦定理
		int pos = check_pos_circle_circle(c1 , c2) ;
		if(pos == 0 || pos == 4)  return {} ;
		db a = (c2.o - c1.o).len2() ;
		db cosA = (c1.r * c1.r + a - c2.r * c2.r) / (2 * c1.r * sqrtl(max(a , (db)0.0))) ;
		db b = c1.r * cosA ;
		db c = sqrtl(max((db)0.0 , c1.r * c1.r - b * b)) ;
		point k = (c2.o - c1.o).unit() ;
		point m = c1.o + k * b ;
		vec v = k.rotate_left() * c ;
		return {m - v , m + v} ;
	}
	circle Incircle_of_a_Triangle(point p1 , point p2 , point p3) //三角形p1p2p3内接圆
	{
		//角平分线求交点，点到直线距离
		line l1 ;
		l1.s = p1 ;
		l1.e = (p2 - p1).unit() + (p3 - p1).unit() ;
		line l2 ;
		l2.s = p2 ;
		l2.e = (p1 - p2).unit() + (p3 - p2).unit() ;
		point p = l1.line_intersect(l2) ;
		line l3 ;
		l3.s = p1 ;
		l3.e = p2 - p1 ;
		circle cc ;
		cc.o = p ;
		cc.r = l3.dis_point(p) ;
		return cc ;
	}
	circle Circumscribed_Circle_of_a_Triangle(point p1 , point p2 , point p3) //三角形p1p2p3外接圆
	{
		//垂直平分线求交点，点到直线距离
		line l1 ;
		l1.s = p1 + (p2 - p1) / 2 ;
		l1.e = (p2 - p1).rotate_left() ; //顺时针或逆时针旋转90度均可，因为是直线求交
		line l2 ;
		l2.s = p2 + (p3 - p2) / 2 ;
		l2.e = (p3 - p2).rotate_left() ;
		point p = l1.line_intersect(l2) ;
		circle cc ;
		cc.o = p ;
		cc.r = p.dis(p1) ;
		return cc ;
	}
	vector<line> Tangent_out_Circle_Circle(circle c1 , circle c2) //外切线
	{
		//相似三角形
		int pos = check_pos_circle_circle(c1 , c2) ;
		if(pos == 0)  return {} ;
		if(pos == 1)
		{
			point k = get_circle_circle(c1 , c2)[0] ;
			vec v = k - c1.o ;
			v = v.rotate_left() ;
			line l ;
			l.s = k ;
			l.e = v ;
			return {l} ;
		}
		if(cmp(c1.r , c2.r) == 0)
		{
			vec v = (c2.o - c1.o).rotate_left().unit() * c1.r ;
			vec p1 = c1.o + v ;
			line l1 ;
			l1.s = p1 ;
			l1.e = c2.o - c1.o ;
			vec p2 = c1.o - v ;
			line l2 ;
			l2.s = p2 ;
			l2.e = c2.o - c1.o ;
			return {l1 , l2} ;
		}
		else
		{
			vec v = c2.o - c1.o ;
			v = v.unit() * (c1.o.dis(c2.o) * c1.r / (c1.r - c2.r)) ;
			point H = c1.o + v ;
			vector<point> pp1 = c1.Tangent_Point_Circle(H) ;
			line l1 ;
			l1.s = H ;
			l1.e = pp1[0] - H ;
			line l2 ;
			l2.s = H ;
			l2.e = pp1[1] - H ;
			return {l1 , l2} ;
		}
	}
	vector<line> Tangent_in_Circle_Circle(circle c1 , circle c2) //内切线
	{
		int pos = check_pos_circle_circle(c1 , c2) ;
		if(pos <= 2)  return {} ;
		if(pos == 3)
		{
			point k = get_circle_circle(c1 , c2)[0] ;
			vec v = k - c1.o ;
			v = v.rotate_left() ;
			line l ;
			l.s = k ;
			l.e = v ;
			return {l} ;
		}
		db t = c1.r / (c1.r + c2.r) * c1.o.dis(c2.o) ;
		point p = c1.o + (c2.o - c1.o).unit() * t ;
		vector<point> pp1 = c1.Tangent_Point_Circle(p) ;
		line l1 ;
		l1.s = p ;
		l1.e = pp1[0] - p ;
		line l2 ;
		l2.s = p ;
		l2.e = pp1[1] - p ;
		return {l1 , l2} ;
	}
	vector<line> Tangent_Circle_Circle(circle c1 , circle c2) //两个圆的公切线
	{
		//外切线和内切线一起考虑
		if(cmp(c1.r , c2.r) < 0)  swap(c1 , c2) ;
		vector<line> A = Tangent_out_Circle_Circle(c1 , c2) ;
		vector<line> B = Tangent_in_Circle_Circle(c1 , c2) ;
		for(auto u : B)  A.push_back(u) ;
		return A ;
	}
	db get_area_of_Circle_Triangle(circle c1 , point p2 , point p3)
	{
		//圆c1与三角形c1 p2 p3的交
		point k = c1.o ;
		c1.o = c1.o - k ;
		p2 = p2 - k ;
		p3 = p3 - k ;
		int pos1 = c1.inside(p2) ;
		int pos2 = c1.inside(p3) ;
		line l ;
		l.s = p2 ;
		l.e = p3 - p2 ;
		vector<point> pp = c1.get_circle_line(l) ;
		if(pos1 >= 0)
		{
			if(pos2 >= 0)  return cross(p2 , p3) / 2 ;
			return c1.r * c1.r * rad(pp[1] , p3) / 2 + cross(p2 , pp[1]) / 2 ;
		}
		else if(pos2 >= 0)
		{
			return c1.r * c1.r * rad(p2 , pp[0]) / 2 + cross(pp[0] , p3) / 2 ;
		}
		else
		{
			line l ;
			l.s = p2 ;
			l.e = p3 - p2 ;
			int pos = cmp(c1.r , l.dis_segment_point(c1.o)) ;
			if(pos <= 0)  return c1.r * c1.r * rad(p2 , p3) / 2 ;
			return cross(pp[0] , pp[1]) / 2 + c1.r * c1.r * (rad(p2 , pp[0]) + rad(pp[1] , p3)) / 2 ;
		}
	}
	db get_area_of_Circle_Polygon(circle c1 , vector<point> pp) //pp按照逆时针给出
	{
		//转成三角形和圆求有向面积交
		int n = pp.size() ;
		db res = 0 ;
		for(int i = 0 ; i < n ; i ++)
		{
			point now = pp[i] ; //三角形o pp[i] pp[(i + 1) % n] 需要按照顺序给出
			point nxt = pp[(i + 1) % n] ;
			res += get_area_of_Circle_Triangle(c1 , now , nxt) ; //已经除2
		}
		return fabs(res) ;
	}
	db get_area_of_Circle_Circle(circle c1 , circle c2) //两个圆的相交面积
	{
		//扇形减去四边形面积
		if(cmp(c1.r , c2.r) < 0)  swap(c1 , c2) ;
		int pos = check_pos_circle_circle(c1 , c2) ;
		if(pos >= 3)  return 0.0 ;
		if(pos <= 1)  return c2.area() ;
		vector<point> pp = get_circle_circle(c1 , c2) ;
		db S1 = fabs(2.0 * rad(pp[0] - c1.o , c2.o - c1.o)) * c1.r * c1.r / 2 ;
		db S2 = fabs(2.0 * rad(pp[0] - c2.o , c1.o - c2.o)) * c2.r * c2.r / 2 ;
		db S3 = fabs(cross(pp[0] - c1.o , c2.o - c1.o)) ;
		return S1 + S2 - S3 ;
	}
} c ;
db closest_point(vector<point> &A , int l , int r)
{
	if(r - l <= 5)
	{
		db res = 1e20 ;
		for(int i = l ; i <= r ; i ++)
			for(int j = i + 1 ; j <= r ; j ++)
				res = min(res , A[i].dis(A[j])) ;	
		return res ;
	}
	int mid = (l + r) / 2 ;
	db res = min(closest_point(A , l , mid) , closest_point(A , mid + 1 , r)) ;
	vector<point> B ;
	for(int i = l ; i <= r ; i ++)
		if(cmp(fabs(A[i].x - A[mid].x) , res) <= 0)
			B.push_back(A[i]) ;
	sort(B.begin() , B.end() , [&](point p1 , point p2){ return cmp(p1.y , p2.y) < 0 ; }) ;
	for(int i = 0 ; i < B.size() ; i ++)
		for(int j = i + 1 ; j < B.size() && B[j].y - B[i].y < res ; j ++)
			res = min(res , B[i].dis(B[j])) ;
	return res ;
}
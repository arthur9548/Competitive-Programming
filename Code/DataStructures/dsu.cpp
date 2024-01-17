int dsu[MXN];
int level[MXN];

int pai(int a){
	if (dsu[a]==a)return a;
	else return dsu[a] = pai(dsu[a]);
}

void merge(int a, int b){
	int pa = pai(a), pb = pai(b);
	if (pa==pb)return;
	if (level[pb]>level[pa])swap(pa, pb);
	dsu[pb] = pa; level[pa] += (level[pa]==level[pb]);
}
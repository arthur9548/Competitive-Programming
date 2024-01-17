int trie[MXN][26];
int freq[MXN];
int cn=1;

int nxt(char proxc, int curno){
	if (trie[curno][proxc-'a'])return trie[curno][proxc-'a'];
	return trie[curno][proxc-'a'] = cn++;
}	
 
void insert(string& s){
	int no=0;
	for(char c : s)no = nxt(c, no);
	freq[no]++;
}

int count(string& s){
	int no = 0;
	rep(i, 0, s.size())no = nxt(c, no);
	return freq[no];
}
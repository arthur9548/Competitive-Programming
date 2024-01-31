//Recursive DFS without requiring global scope
auto dfs = [&](auto self, int v){
	if (visited[v])return;
	visited[v] = true;
	for(int adj : g[v])self(self, adj);
};

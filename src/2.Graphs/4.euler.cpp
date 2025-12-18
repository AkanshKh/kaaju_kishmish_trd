// Hierholzer's Algorithm undirected
// check remove the seen for directed
void dfs(int node) {
	while (!g[node].empty()) {
		auto [son, idx] = g[node].back();
		g[node].pop_back();
		if (seen[idx]) { continue; }
		seen[idx] = true;
		dfs(son);
	}
	path.push_back(node);
}
for (int node = 0; node < n; node++) {
    if (degree[node] % 2) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
}
dfs(0);
if (path.size() != m + 1) {
    cout << "IMPOSSIBLE";
}
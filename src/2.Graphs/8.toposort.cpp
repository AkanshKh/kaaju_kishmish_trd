vector<int> topoSort(const vector<vector<int>>& gr) {
vector<int> indeg(n), q;
for (auto& li : gr) for (int x : li) indeg[x]++;
rep(i,0,n) if (indeg[i] == 0) q.push_back(i);
rep(j,0,sz(q)) for (int x : gr[q[j]])
if (--indeg[x] == 0) q.push_back(x);
return q;
}
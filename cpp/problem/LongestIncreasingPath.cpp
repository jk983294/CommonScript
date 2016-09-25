#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class PathNode{
public:
    PathNode(int x, int y) : x(x), y(y){ }
    int x, y;
};
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int size = matrix.size();
        if(size <= 0) return 0;
        int ySize = matrix[0].size();
        if(ySize <= 0) return 0;
        int maxStep = 1;
        vector<vector<int>> step(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < ySize; ++j) {
                for (int k = 0; k < size; ++k) {
                    step[k].resize(ySize, -1);
                }
                step[i][j] = 1;
                queue<PathNode> q;
                q.push(PathNode(i, j));
                while (!q.empty()){
                    PathNode node = q.front();
                    q.pop();
                    if(node.x + 1 < size && matrix[node.x][node.y] < matrix[node.x + 1][node.y]
                            && (step[node.x + 1][node.y] <= step[node.x][node.y])){
                        step[node.x + 1][node.y] = step[node.x][node.y] + 1;
                        q.push(PathNode(node.x + 1, node.y));
                        if(maxStep < step[node.x + 1][node.y]) maxStep = step[node.x + 1][node.y];
                    }
                    if(node.y + 1 < ySize && matrix[node.x][node.y] < matrix[node.x][node.y + 1]
                       && (step[node.x][node.y + 1] <= step[node.x][node.y])){
                        step[node.x][node.y + 1] = step[node.x][node.y] + 1;
                        q.push(PathNode(node.x, node.y + 1));
                        if(maxStep < step[node.x][node.y + 1]) maxStep = step[node.x][node.y + 1];
                    }
                    if(node.x - 1 >= 0 && matrix[node.x][node.y] < matrix[node.x - 1][node.y]
                       && (step[node.x - 1][node.y] <= step[node.x][node.y])){
                        step[node.x - 1][node.y] = step[node.x][node.y] + 1;
                        q.push(PathNode(node.x - 1, node.y));
                        if(maxStep < step[node.x - 1][node.y]) maxStep = step[node.x - 1][node.y];
                    }
                    if(node.y - 1 >= 0 && matrix[node.x][node.y] < matrix[node.x][node.y - 1]
                       && (step[node.x][node.y - 1] <= step[node.x][node.y])){
                        step[node.x][node.y - 1] = step[node.x][node.y] + 1;
                        q.push(PathNode(node.x, node.y - 1));
                        if(maxStep < step[node.x][node.y - 1]) maxStep = step[node.x][node.y - 1];
                    }
                }
            }
        }
        return maxStep;
    }
};

int main(){
    vector<vector<int>> matrix{{9,9,4},
                               {6,6,8},
                               {2,1,1}};
    vector<vector<int>> matrix1{{3,4,5},
                               {3,2,6},
                               {2,2,1}};
    vector<vector<int>> matrix2{{1, 2}};
    cout<<Solution().longestIncreasingPath(matrix)<<endl;
    cout<<Solution().longestIncreasingPath(matrix1)<<endl;
    cout<<Solution().longestIncreasingPath(matrix2)<<endl;
    return 0;
}
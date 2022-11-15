# editDistance
在信息论、语言学和计算机科学中，莱文斯坦距离是衡量两个序列之间差异的字符串指标。两个词之间的莱文斯坦距离是将一个词变为另一个词所需的单字符编辑（插入、删除或替换）的最小操作次数。它是以苏联数学家Vladimir Levenshtein命名的，他在1965年提出了这个距离。该距离的实际应用在于搜索引擎或输入法中输入错误的纠正。

以下为Wikipedia给出的计算公式：
{\displaystyle \operatorname {lev} (a,b)={\begin{cases}|a|&{\text{ if }}|b|=0,\\|b|&{\text{ if }}|a|=0,\\\operatorname {lev} {\big (}\operatorname {tail} (a),\operatorname {tail} (b){\big )}&{\text{ if }}a[0]=b[0],\\1+\min {\begin{cases}\operatorname {lev} {\big (}\operatorname {tail} (a),b{\big )}\\\operatorname {lev} {\big (}a,\operatorname {tail} (b){\big )}\\\operatorname {lev} {\big (}\operatorname {tail} (a),\operatorname {tail} (b){\big )}\\\end{cases}}&{\text{ otherwise,}}\end{cases}}}

# C++的编辑距离实现
在Levenshtein.cpp中给出了莱文斯坦距离的C++实现。由于该问题具有最优子结构的性质，即字符串子串的最小编辑距离也是原字符串的最小编辑距离，该距离可以采用动态规划方法求解。

我们以kitten和sitting为例，解释该算法的求解方法，以及其中的原理。

Levenshtein("kitten","sitting")的minDist矩阵:
        k	i	t	t	e	n
    0	1	2	3	4	5	6
s	1	1	2	3	4	5	6
i	2	2	1	2	3	4	5
t	3	3	2	1	2	3	4
t	4	4	3	2	1	2	3
i	5	5	4	3	2	2	3
n	6	6	5	4	3	3	2
g	7	7	6	5	4	4	3

minDist矩阵的含义是对应字串的编辑距离，例如左上角的0是空串到空串的编辑距离。
动态规划方法的第一步是设置初值，在minDist矩阵中，先设置一行一列的值，其实际含义为：
从“ ”到“k”,“ki”，“kit”，“kitt”，“kitte”，“kitten”的编辑距离分别为1，2，3，4，5，6。

该矩阵计算的方向为自左上至右下计算
公式为：
(*)minDist[i][j] = minDist[i-1][j-1];                                              if s1[i]==s2[j]
(**)minDist[i][j] = min(minDist[i-1][j-1],minDist[i][j-1],minDist[i-1][j])+1;      else
即从该矩阵的↖，↑，←三个方向中的最短编辑距离中增加一格

(*)式说明，当前指针指向的字符相同时，编辑距离不变。
而(**)式说明，当前指针指向的字符不同时，编辑距离由s1串的该位置和前一个位置，s2串的该位置和前一个位置的字符共同决定。
↖，↑，←三个方向恰好对应了编辑距离中的替换、插入和删除三个操作，具体例子如下：

minDist[1][1]处的1由↖的0+1得来，代表s1到s2的替换操作。
minDist[1][4]处的4由←的3+1得来，代表s1到s2的删除操作。
minDist[6][3]处的4由↑的3+1得来，代表s1到s2的插入操作。

该算法不仅实现了莱文斯廷编辑距离的计算，还可以根据矩阵溯源具体的字符串操作。
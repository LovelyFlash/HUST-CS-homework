{{ self.title() }}

{{ s('description') }}

假设有数列 $f$，$f(i)$ 为数列的第 $i$ 项，$f(i)=a\cdot f(i-1)+b\cdot f(i-2)+c(i>2)$。

求 $f(n)$，由于答案可能很大，只需要输出答案对 $998244353$ 取模的结果。

{{ s('input format') }}

输入共三行。

输入的第一行为一个正整数 $n$。

输入的第二行为两个正整数，依次表示 $f(1),f(2)$。

输入的第三行为三个非负整数 $a,b,c$。

{{ s('output format') }}

输出一行一个整数，表示答案。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

对于 $100\%$ 的测试数据，$1 \le n \le 10^{18}$，$1 \le f(1),f(2) < 998244353$，$0 \le a, b, c<998244343$。

{{ s('hints') }}

计算 $a^b$，存在 $O(\log b)$ 的算法，请自行查找资料学习**快速幂**算法。

假设 $A$ 是 $n$ 阶方阵，$A^k$ 亦可使用快速幂计算，只需要将快速幂中的普通乘法全部换为矩阵乘法。

有递推公式，$f(i)=a\cdot f(i-1)+b\cdot f(i-2)+c$，我们可以用矩阵来表示这个递推式。
$$
\begin{bmatrix}
f(i) & f(i-1) & c
\end{bmatrix}^T
=
A \times
\begin{bmatrix}
f(i-1) & f(i-2) & c
\end{bmatrix}^T
$$
容易发现，$A$ 一定是一个 $3\times 3$ 的方阵，那么核心就是得到 $A$，请自行进行推导。

求出 $A$ 后，容易得到，
$$
\begin{bmatrix}
f(n) & f(n-1) & c
\end{bmatrix}^T
= A^{n-2}\times
\begin{bmatrix}
f(2) & f(1) & c
\end{bmatrix}^T
$$
即可在 $O(\Sigma^2\log n)$ 的时间复杂度求得答案，其中 $\Sigma$ 代表 $A$ 的阶。

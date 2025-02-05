{{ self.title() }}

{{ s('description') }}

小 F 得到了一组由 $n$ 个数组成的信息。第 $i$ 个数 $b_i$ 可能的取值范围为 $0 \sim a_i - 1$。

小 F 发明了一种编码方式，可以用一个数 $m$ 来表示这些信息。记 $c_i = a_1 \cdot a_2 \cdot \ldots \cdot a_i(i\ge1),c_0=1$，则 $m$ 的计算公式如下：

$$m = \sum\limits_{i=1}^{n}{c_{i-1}\cdot b_i}\\=c_0\cdot b_1+c_1\cdot b_2 + \cdots + c_{n-1}\cdot b_n$$

现在，给出 $m$ 和数组 $a$，请你还原出数组 $b$。

{{ s('input format') }}

输入共两行。

输入的第一行为两个整数 $n,m$。

输入的第二行为 $n$ 个整数，第 $i$ 个表示 $a_i$。

{{ s('output format') }}

输出一行 $n$ 个整数，表示数组 $b$。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('sample', 3) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

对于 $100\%$ 的测试数据，$1 \le n \le 20$，$2 \le a_i \le 20$，$\prod a_i \le 10^9$

{{ s('hints') }}

对于所有的 $j>i$，有 $c_j$ 是 $c_i$ 的倍数。$m \bmod c_i=\sum\limits_{k=1}^{i}{c_{k-1}\cdot b_k}$。
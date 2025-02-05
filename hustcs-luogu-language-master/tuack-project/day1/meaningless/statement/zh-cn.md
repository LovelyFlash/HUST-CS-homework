{{ self.title() }}

{{ s('description') }}

已知每个数都可以通过唯一分解定理分解成若干个质数相乘的形式,形如 $a = p_1^{a_1}\times p_2^{a_2}\times...\times p_n^{a_n}$,现在我们想求出通过分解 $a$，忽略的指数小于 $k$ 的质数，剩下数的乘积。

{{ s('input format') }}

输入共 $q+1$ 行

输入的第一行包含一个正整数 $q$ ，表示询问个数

接下来 $q$ 行每行包含两个整数 $a$ ,  $k$ 表示一个询问

{{ s('output format') }}

输出共 $q$ 行，每行一个整数，表示所求的数。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

对于 $100\%$ 的测试数据，$1 < k,q \le 10$，$0 < a \le 10^{10}$。

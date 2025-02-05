{{ self.title() }}

{{ s('description') }}

倍增算法是算法领域中常用的一种优化算法，不过在这道题中，你并不需要用到这种算法。

对一个数 $x$ ，规定一次操作为：将 $x$ 除以 $2$ 并向下取整，即将 $x$ 变为$\lfloor \frac{x}{2} \rfloor$。

请问这个数需要多少次操作 $2x$ 才能变为 $1$ 。

{{ s('input format') }}

输入一个正整数 $x$ 。

{{ s('output format') }}

输出一个正整数，表示要多少次操作后 $2x$ 变为 $1$ 。

**请输出答案 $+1$ 的结果**。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

数据范围：$1 \le x\le 10^9$。

{{ self.title() }}

{{ s('description') }}

给你 $n$ 个数和一个整数 $k$。

问有你有多少种方法从 $n$ 个数里面选 $k$ 个数使得和为质数？

{{ s('input format') }}

第一行两个空格隔开的整数 $n,k$。

第二行 $n$ 个整数，分别为 $x_1,x_2,\cdots,x_n$。

{{ s('output format') }}

输出一个整数，表示种类数。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

数据保证：$1 \le n \le 20$，$k<n$，$1 \le x_i \le 5\times 10^6$。

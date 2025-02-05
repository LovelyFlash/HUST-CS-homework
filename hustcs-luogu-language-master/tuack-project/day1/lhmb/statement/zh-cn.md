{{ self.title() }}

{{ s('description') }}

lhm 有 $n$ 个正整数，他很喜欢它们。lhm 突然想知道这些正整数中第 $k$ 个最小整数（大小一样的整数只算一次），你能帮帮他吗？

{{ s('input format') }}

第一行为 $n$ 和 $k$。

第二行开始为 $n$ 个正整数的值，整数间用空格隔开。

{{ s('output format') }}

第 $k$ 个最小整数的值；若无解，则输出 `NO RESULT`。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

数据保证：$n \leq 10000$，$k \leq 1000$，正整数均小于 $30000$。

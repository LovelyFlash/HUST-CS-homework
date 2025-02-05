{{ self.title() }}

{{ s('description') }}

现在给你 $n$ 个 $8\times 8$ 的字符矩阵,仅由大小写的 `*`、`k`、`q`、`r`、`b`、`n`、`q` 组成，你需要判断第 $i$ 个字符矩阵在之前出现过几次。

{{ s('input format') }}

输入共 $8\cdot n+1$ 行。

输入的第一行包含两个正整数 $n$ ，分别表示有 $n$ 个字符矩阵。

接下来 $8\cdot n$ 行,依次表示这 $n$ 个字符矩阵。

{{ s('output format') }}

输出共 $n$ 行，表示这个字符矩阵是第几次出现。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

对于 $100\%$ 的测试数据，$1 \le n \le 100$。

{{ s('hints') }}

可用字符串哈希进行判断。

亦可以使用 STL 提供的 map、set、unordered_map 等容器进行去重，请自行查找资料学习。
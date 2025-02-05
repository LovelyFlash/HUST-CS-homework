{{ self.title() }}

{{ s('description') }}

线性筛素数是一种常用的素数筛法，不过在这道题中，你并不需要用到这个算法。

给出一个正整数 $S$ ，请问最多可以选出多少个质数，使它们的和小于等于 $S$ 。

{{ s('input format') }}

一行一个正整数 $S$ 。

{{ s('output format') }}

将这些质数从小往大输出，随后输出质数个数。所有数单独占一行。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('sample', 3) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

数据范围：$1 \le S \le {10}^5$。

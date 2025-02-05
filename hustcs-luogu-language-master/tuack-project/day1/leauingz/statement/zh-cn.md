{{ self.title() }}

{{ s('description') }}

LeauingZ 非常懂造题， 如果让 LeauingZ  造题， 一个题只需要造 $3$ 分钟， 如果你自己造题， 则一个题需要花 $5$ 分钟。 但是如果让 LeauingZ 造题， 因为 LeauingZ 很忙， 他需要额外花费 $11$ 分钟用来休息。（注意， 总共多花费 $11$ 分钟而不是每造一个题休息 $11$ 分钟）

现在要造 $n$ 个题， 你可以选择自己造完或者让 LeauingZ 造完所有题。如果你自己造题配置花费的总时间短，请输出 `Local`，否则输出 `Luogu`。

{{ s('input format') }}

输入一个正整数 $n$，表示需要造的题目量。

{{ s('output format') }}

输出一行，一个字符串。如果自己造花费的总时间短，请输出 `Local`，否则输出 `Luogu`。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

数据保证 $1 \leq n\leq 100$。

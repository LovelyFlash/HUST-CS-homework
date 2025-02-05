# hustcs-luogu-language

## 任务书下载

方法 1（推荐）：

使用 git 工具直接下载本仓库，内含任务书，数据集等，任务书为 `/release/version-2-2025winter.pdf`

```shell
git clone git@github.com:QianQNanami/hustcs-luogu-language.git
```

方法 2：

在网页打开 [release 文件夹](https://github.com/QianQNanami/hustcs-luogu-language/tree/master/release)，下载 `version-2-2025winter.pdf`

## 文件结构

- `codes`：代码仓库，每题对应一个文件夹。我们鼓励同学们将自己通过的代码，通过 Pull Request 的方式，上传到仓库中，请将自己的代码命名为 `学号.cpp`，放置在对应试题文件夹中 PR。
- `evaldata`：测试集。无法通过的试题，可参考测试集调试。
- `release`：试题发行版本，均为 PDF 文件。
- `solutions`：试题题解，为 Markdown File。我们鼓励同学们将自己通过的试题，以 Markdown 格式撰写题解，通过 Pull Request 的方式，上传到仓库中，请将自己的题解命名为 `学号.md`，放置在对应试题文件夹中 PR。
- `tuack-project`：生成试题发行 PDF 的工程文件，同学们无需关注。

## 提交与结果评估

加入[华中科技大学计算机科学与技术学院团队](https://www.luogu.com.cn/team/29447)，报名对应比赛，在试题中提交。

代码由洛谷平台使用测试集进行黑盒测试，代码必须通过一题的全部测试集方为正确。

#include<bits/stdc++.h>

using namespace std;
TSMatrix ADD(TSMatrix A, TSMatrix B)
//返回矩阵A、B相加的结果
{
  /************** begin *****************/
  auto cmp = [](const Triple a,
    const Triple b) {
    return a.i < b.i || (a.i == b.i && a.j < b.j);
  };
  auto equal = [](const Triple a,
    const Triple b) {
    return a.i == b.i && a.j == b.j;
  };
  auto add = [](const Triple a,
    const Triple b) -> Triple {
    Triple tmp;
    tmp.i = a.i;
    tmp.j = a.j;
    tmp.e = a.e + b.e;
    return tmp;
  };
  int i = 1, j = 1;
  TSMatrix res;
  Triple inf = {
    0x3f3f3f3f,
    0x3f3f3f3f,
    0x3f3f3f3f
  };
  A.data[A.tu + 1] = B.data[B.tu + 1] = inf;
  res.mu = A.mu;
  res.nu = A.nu;
  res.tu = 1;
  while (i <= A.tu || j <= B.tu) {
    if (equal(A.data[i], B.data[j])) {
      res.data[res.tu++] = add(A.data[i], B.data[j]);
      if (res.data[res.tu - 1].e == 0) res.tu--;
      i++, j++;
    } else {
      if (cmp(A.data[i], B.data[i])) {
        res.data[res.tu++] = A.data[i++];
      } else {
        res.data[res.tu++] = B.data[j++];
      }
    }
  }

  res.tu--;
  return res;
  /**************  end  *****************/
}

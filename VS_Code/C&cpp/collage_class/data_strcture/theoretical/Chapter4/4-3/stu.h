#include <bits/stdc++.h>
using namespace std;
void Replace(HString &S, HString T, HString V)
//
{
  /************** begin *****************/
  auto equal = [](char *p, HString s) -> bool
  {
    for (int i = 0; i < s.length; i++)
    {
      if (p[i] != s.ch[i])
        return false;
    }
    return true;
  };
  char *res = new char[10001];
  int i = 0, k = 0;
  for (i = 0; i < S.length - T.length + 1; i++)
  {
    if (equal(S.ch + i, T))
    {
      for (int j = 0; j < V.length; j++)
      {
        res[k++] = V.ch[j];
      }
      i += T.length - 1;
    }
    else
    {
      res[k++] = S.ch[i];
    }
  }
  while (i < S.length)
    res[k++] = S.ch[i++];
  S.ch = res;
  S.length = k;

  /**************  end  *****************/
}
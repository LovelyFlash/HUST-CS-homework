void ShiftRightCircular(ElemType * A, int n, int k) {
    /************** begin *****************/
    k = k % n;
    if (k == 0) return;
    if (k > 0) {
      ElemType a[k];
      for (int i = 0; i < k; i++) {
        a[i] = A[n - k + i];
      }
      for (int i = n - 1; i >= k; i--) {
        A[i] = A[i - k];
      }
      for (int i = 0; i < k; i++) {
        A[i] = a[i];
      }
    } else {
      k = -k;
      ElemType a[k];
      for (int i = 0; i < k; i++) {
        a[i] = A[i];
      }
      for (int i = 0; i < n - k; i++) {
        A[i] = A[i + k];
      }
      for (int i = n - k; i < n; i++) {
        A[i] = a[i - n + k];
      }
    }
  
    /**************  end  *****************/
  }
  
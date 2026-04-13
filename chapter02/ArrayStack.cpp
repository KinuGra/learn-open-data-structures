#include <cassert>
#include <iostream>

template <typename T> class array {
  // メンバ変数
  T *a;       // T型の要素を格納する生の配列（ヒープ上）へのポインタ
  int length; // 配列の長さ

public:
  // コンストラクタ：配列の大きさは作成時に決まる
  array(int len) {
    length = len;
    a = new T[length]; // ヒープにT型×length個分のメモリを確保,
                       // 0で初期化されない
  }

  // operator[] : 添字アクセス（arr[i]で読み書きできるようにする）
  T &operator[](int i) {
    assert(i >= 0 && i < length); // 範囲外アクセスを防ぐ
    return a[i];                  // T型の参照を返す → 読み書き両方可能
  }

  // operator=：配列の代入（別のarrayの中身を奪う）
  array<T> &operator=(array<T> &b) {
    if (a != NULL)
      delete[] a; // 自分が持っている古い配列を解放
    a = b.a;      // bの配列ポインタをコピー（所有権の移動）
    b.a = NULL;   // bのポインタを無効化（二重解放を防ぐ）
    length = b.length;
    return *this; // 自分自身の参照を返す（a = b = cのような連鎖代入用）
  }
};

template <typename T> class ArrayStack {
  array<T> a; // backing array（さっきのarrayクラス）
  int n;      // 現在の有効な要素数

public:
  ArrayStack();
  int size() { return n; }
  // 配列はランダムアクセスO(1)なのでこれがArrayStackの強み
  T get(int i) { return a[i]; }
  T set(int i, T x) {
    T y = a[i]; // 古い値を退避
    a[i] = x;
    return y; // 古い値を返す（呼び出し元が知りたい場合のため）
  }
  void add(int i, T x) {
    // 容量チェック：一杯なら拡大
    if (n + 1 > a.length)
      resize();

    // a[i]〜a[n-1]を1つ右にずらす（後ろから）
    for (int j = n - 1; j >= i; j--) {
      a[j + 1] = a[j];
    }
  }
  T remove(int i);
  void resize();
};

// TODO: このコンストラクタについて調べている途中, add実装途中
template <class T> ArrayStack<T>::ArrayStack() : a(1) { n = 0; }

int main() {}

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

int main() {
  // 作成：int型の配列を10個分確保
  array<int> arr(10);

  // 書き込み：operator[] で添字アクセス
  arr[0] = 100;
  arr[1] = 11111;

  // 読み込み
  int x = arr[1];
  std::cout << x << std::endl;

  // 範囲外アクセス
  // arr[10] = 99;

  for (int i = 0; i < 10; i++) {
    std::cout << arr[i] << ", ";
  }
  std::cout << std::endl;

  // TODO: 自作arrayクラスを使う
}

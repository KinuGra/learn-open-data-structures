# ArrayStack

- 説明
  Listインターフェースを backing array（配列 a）で実装している
  連結リストじゃなく、要素は常に連続領域に並ぶ
  ArrayStackというデータ構造は末尾を使うことで、Stackインターフェースを実装する効率的な方法

- 計算量
  get(i)及びset(i,x)の実行時間はO(1)である
  add(i,x)及びremove(i)の実行時間は左右にシフトしないといけないのでO(1+n-i)

  Queueを実装しようとすると、enqueueかdequeueのどちらかの操作でArrayStackの先頭を触る必要がある。つまりadd(0, x)かremove(0)を呼び出さないといけないので、nに比例する実行時間がかかる

## 章全体（配列backingの共通）

- **強み**：連続メモリ → `get(i)/set(i,x)` が **O(1)**
- **弱み①**：真ん中の `add/remove` は **シフトが必要**（だから `i` に依存）
- **弱み②**：配列は固定長 → **resize は O(n) コピー**

## ArrayStack（動的配列の基本形）

- **不変条件**：要素は `a[0..n-1]`、常に `a.length ≥ n`
- **操作コスト（resize無視）**：`add/remove` は **O(n−i)**（後ろ側を動かす量）
- **resize方針**：容量不足→だいたい **2n に拡張**／要素少なすぎ→**縮小**（例：`a.length ≥ 3n` で縮小）
- **重要結論（償却解析）**：m回の操作で resize 合計 **O(m)** → 1回あたり **償却O(1)**
  → 特に **push=add(n,x), pop=remove(n-1)** は償却 **O(1)**

## FastArrayStack（最適化の意味）

- **やってることは同じ**（シフトとコピーは必須、漸近は変わらない）
- ただし `memmove/memcpy` や `std::copy(_backward)` で **定数倍が速い**（2〜3倍の可能性）

## 使い分けの一言

- 「末尾中心なら ArrayStack は強い（償却O(1)）。真ん中の挿入削除が多いと配列は不利」

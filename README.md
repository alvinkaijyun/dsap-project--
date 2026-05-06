# DreamCore 記憶系統：以每日回憶、夢境與遺忘為核心的多層記憶模擬

## 動機與目標
人類記憶並非靜態儲存，而是一個動態、選擇性且具有層次的系統。記憶會隨時間衰退，透過主動回憶而被強化，並在睡眠中經歷重組與鞏固。此外，部分記憶可能被壓抑而不易被意識提取，但仍可能在夢境或內在意識中浮現。

本專題結合記憶的心理學概念（如記憶衰退、鞏固、壓抑與分層結構）與 dreamcore 風格中模糊、片段與非線性的特性，設計一個以「每日」為單位運作的記憶模擬系統。

---

## 🚧 Prototype 現況（重要）
目前系統已完成核心「每日記憶模擬流程」的基本版本，包含：

### ✅ 已實作功能
- 新增記憶（設定 importance）
- 記憶強度（strength）與衰減（decay_rate）
- 每日時間推進（Next Day / Sleep）
- 記憶瀏覽（Memory Browser）
  - Recommended List
  - View（All / Layer / State）
  - Search
- 單筆記憶操作
  - Review（強化記憶）
  - Suppress（壓抑記憶，採用等級制）
- 記憶狀態轉換（Active / Suppressed / Faded）
- 記憶層級（Working / Long-term / Deep）

---

### 🔄 部分實作 / 簡化版本
- Dream Recall（已具基本隨機抽取概念）
- Inner Voice（以機率選取部分記憶）
- Suppression（由原本 boolean 改為等級系統）

---

### ⏳ 尚未完整實作（保留於設計）
- 完整 dream bias 模型
- 複雜權重推薦（heap / priority queue）
- 記憶干擾模型（大量新增記憶時）
- 高階心理模型（完整 unconscious interaction）

---

## 競品比較（保留原設計）

### 1. 一般筆記工具
偏靜態儲存，不具備記憶動態模擬

### 2. Anki
偏重學習效率，不模擬壓抑、夢境或深層記憶

### 3. Todo List
僅做提醒，不涉及記憶心理機制

### DreamCore 差異
- 記憶層級（Working / Long-term / Deep）
- 記憶狀態（Active / Suppressed / Faded）
- 主動 vs 被動回憶
- Dream / Inner Voice 模擬
- 模糊記憶輸出

---

## 系統架構（對應目前程式）

### 記憶層級（Layer）
- Working：初始記憶
- Long-term：經過回憶鞏固
- Deep：高重要性且穩定

---

### 記憶狀態（State）
- Active：可直接被存取
- Suppressed：被壓抑（以等級表示）
- Faded：強度過低

---

### 記憶屬性
- name
- day_created
- strength
- decay_rate
- importance
- review_count
- suppression_level（新增）
- layer / state

---

## 🧠 每日運作流程（對應目前程式）

### 使用者操作流程
Main Menu
│
├── Add Memory
├── Memory Browser
│ ├── Recommended List
│ ├── View
│ │ ├── All
│ │ ├── By Layer
│ │ └── By State
│ └── Search
│
└── Sleep (進入下一天)

---

### 每日變化（Sleep）
- 所有記憶 strength 減少
- 低於 threshold → 進入 faded
- suppression 記憶有機率浮現
- 進行簡化 dream recall

---

## 回憶機制（目前版本）

### Review
- 增加 strength
- 降低 decay_rate（逐次遞減）
- 增加 review_count
- 可解除 suppressed

---

### Suppress（新版）
- 不再是 yes/no
- 改為 suppression_level（累積）
- 等級越高：
  - 越難被選到
  - 但 inner voice / dream 機率上升

---

## 模糊記憶（Blurred Memory）
當記憶為 faded：
- 字串部分隱藏（但保留最後字母）
- 模擬記憶片段化

---

## 使用技術

- C++
- 分檔架構（.h / .cpp）
- Dynamic Array
- Sorting / Filtering
- 基本機率模型

---

## 未來改進方向（非常重要）

### 🔥 系統升級
- Priority Queue（推薦清單）
- 更真實 dream bias
- Emotional weighting
- Memory interference

---

### 🌐 產品化方向
- Web UI（記憶卡片）
- 點擊記憶 → review / suppress
- Dream 視覺化（dreamcore風格）

---

## 預期成果
本系統展示如何用資料結構與演算法模擬人類記憶的：

- 遺忘
- 壓抑
- 強化
- 潛意識浮現

並透過 DreamCore 風格呈現記憶的不完整性與非線性。

---

## 如何執行

```bash
g++ main.cpp Memory.cpp MemorySystem.cpp -o main
./main

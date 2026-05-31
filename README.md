# DreamCore 記憶系統：以每日回憶、夢境與遺忘為核心的多層記憶模擬

## 專案簡介

DreamCore 是一個結合認知心理學（Cognitive Psychology）與 Dreamcore 美學概念的記憶模擬系統。

不同於一般筆記軟體將資訊視為靜態資料，本系統將「記憶」視為會隨時間變化的動態物件。記憶可能因主動回憶而被強化，也可能因時間流逝而逐漸淡化；部分記憶甚至會被壓抑，但仍可能透過夢境或潛意識重新浮現。

本專題透過資料結構與演算法，模擬記憶在形成、遺忘、鞏固與重現過程中的變化。

---

# 專案目標

本系統希望模擬下列記憶現象：

* 記憶衰退（Forgetting）
* 主動回憶（Active Recall）
* 記憶鞏固（Consolidation）
* 記憶壓抑（Suppression）
* 夢境回憶（Dream Recall）
* 潛意識浮現（Inner Voice）
* 多層記憶結構（Memory Layers）

---

# 已完成功能

## 1. 記憶新增系統

### 預設記憶清單（Preset Memory Library）

系統內建常見的大學生生活事件，使用者可直接選擇：

* Going to class
* Studied for an exam
* Worked on a group project
* Performed on stage
* Went to the library
* Had a meal with friends
* Practiced for activity
* Met a new friend
* Achieved a personal goal
* Spent time alone
* Missed a deadline
* Stayed up late
* Felt stressed
* Talked with friends
* Talked with family
* Talked with someone I like
* Exercise
* Prepared for a presentation
* Had a meaningful conversation
* Felt lonely or disconnected
* Completed an assignment
* Skipped a class
* Listened to music
* Played a video game
* Remembered a childhood memory
* Thought about the future

使用者不需要每次重新輸入記憶內容，即可快速建立每日記憶。

---

### 自訂記憶（Custom Memory）

若預設清單中沒有符合的內容，使用者也可以自行輸入記憶名稱。

建立記憶時需設定：

- Importance（重要性）

系統會自動記錄記憶建立當天的日期（Day Created）。

---

## 2. 記憶瀏覽系統（Memory Browser）

Memory Browser 提供三種瀏覽方式：

### Recommended List

系統根據記憶的重要性與遺忘風險推薦需要回顧的記憶。

---

### View

可依照不同分類方式瀏覽：

#### View All

顯示所有記憶

#### View by Layer

依照記憶層級顯示

#### View by State

依照記憶狀態顯示

---

### Search

透過關鍵字搜尋特定記憶。

---

## 3. 單筆記憶操作

使用者可選擇特定記憶進行互動。

### Review（回憶）

模擬主動回憶。

效果：

* 提升 Strength
* 降低 Decay Rate
* 增加 Review Count
* 幫助記憶進入更高層級
* 逐步解除壓抑

Decay Rate 的改善採遞減設計：

* 第一次 Review：-2
* 第二次 Review：-1
* 後續逐漸減半

此設計參考心理學中的 Retrieval Practice 理論。

---

### Suppress（壓抑）

本系統採用 Suppression Level 設計。

不同於單純的 Yes / No 狀態，每次壓抑都會提高：

* Suppression Level

Suppression Level 越高：

* 越不容易被一般方式存取
* 但越容易透過夢境或潛意識重新浮現

此設計參考心理學中的 Thought Suppression 現象。

---

# 記憶層級（Memory Layer）

## Working Memory

新建立的記憶。

特性：

* 穩定度低
* 容易遺忘
* 衰退速度較快

---

## Long-Term Memory

經過多次回憶後形成。

特性：

* 較穩定
* 較不容易遺忘

---

## Deep Memory

高重要性且經過充分鞏固的記憶。

特性：

* 穩定度最高
* 不容易消失
* 更容易影響夢境與潛意識

---

# 記憶狀態（Memory State）

## Active

正常可被提取的記憶。

---

## Suppressed

被壓抑的記憶。

以 Suppression Level 表示壓抑程度。

---

## Faded

記憶強度過低。

此類記憶會以模糊方式顯示。

---

# 睡眠系統（Sleep Phase）

當使用者選擇 Sleep 時：

## 記憶衰退

所有記憶根據 Decay Rate 降低 Strength。

---

## 狀態更新

當 Strength 低於門檻：

* Active → Faded

---

## 記憶鞏固（Consolidation）

透過 Review Count：

* Working → Long-Term
* Long-Term → Deep

---

## Dream Recall

系統會從記憶庫中抽取部分記憶進入夢境。

目前版本已實作：

* 基本隨機抽取
* Layer 影響
* Suppression 影響

未來可加入更完整的 Dream Bias 模型。

---

## Inner Voice

從以下記憶中抽取：

* Deep Memory
* Suppressed Memory
* Faded Memory

抽中機率與 Importance 相關：

```text
Weight = Importance / 10
```

模擬潛意識中的記憶浮現。

---

# 模糊記憶（Blurred Memory）

當記憶進入 Faded 狀態：

* 偶數位置字元隱藏
* 最後一個字元保留

例如：

```text
Original:
Remembered a childhood memory

Blurred:
R*m*m*b*r*d * c*i*d*o*d *e*o*y
```

模擬記憶片段化與不完整回憶。

---

# 統計資訊（Statistics Dashboard）

系統提供統計頁面顯示：

* 記憶總數
* Layer 分布
* State 分布
* Suppression Level 分布

方便觀察記憶系統的變化。

---

# 系統架構

```text
Main Menu
│
├── Add Memory
│   ├── Preset Memory
│   └── Custom Memory
│
├── Memory Browser
│   ├── Recommended List
│   ├── View
│   │   ├── View All
│   │   ├── View by Layer
│   │   └── View by State
│   │
│   └── Search
│
├── Statistics
│
└── Sleep
```

---

# 使用到的資料結構與演算法

## Data Structures

* Array
* Class
* Multi-file Architecture (.h / .cpp)

---

## Algorithms

* Sorting
* Searching
* Filtering
* Probability-based Selection
* State Transition Logic

---

# 未來改進方向

## 演算法優化

* Priority Queue 推薦系統
* Dream Bias 權重模型
* 記憶干擾模型
* 情緒權重系統

---

## 產品化方向

* GUI 圖形介面
* Web Application
* 記憶卡片式介面
* Dreamcore 視覺化夢境系統
* 記憶關聯網路

---

# 編譯方式

```bash
g++ main.cpp Memory.cpp MemorySystem.cpp -o main
./main
```

---

# Release

目前版本：

**DreamCore Prototype v1.3.1 – Demo & Usability Update**

新增內容：

* Preset Memory Library
* Statistics Dashboard
* 改良 Memory Browser 架構
* 改良 CLI Dashboard
* 強化 Demo 體驗
* 更新 README 文件

---

# 結論

DreamCore 透過資料結構與演算法模擬記憶的形成、遺忘、壓抑與重現過程。

本專題展示了如何將心理學中的記憶概念轉化為可執行的系統模型，並透過多層記憶結構、壓抑機制、夢境回憶與潛意識浮現等設計，呈現記憶在時間中的動態變化。

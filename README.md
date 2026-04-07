# DreamCore 記憶系統：以每日回憶、夢境與遺忘為核心的多層記憶模擬

## 專題名稱
DreamCore Memory System: A Daily Simulation of Recall, Dreaming, and Forgetting

## 動機與目標
人類記憶並非靜態儲存，而是一個動態、選擇性且具有層次的系統。記憶會隨時間衰退，透過主動回憶而被強化，並在睡眠中經歷重組與鞏固。此外，部分記憶可能被壓抑而不易被意識提取，但仍可能在夢境或內在意識中浮現。

本專題結合記憶的心理學概念（如記憶衰退、鞏固、壓抑與分層結構）與 dreamcore 風格中模糊、片段與非線性的特性，設計一個以「每日」為單位運作的記憶模擬系統。

本系統的目標為：
- 模擬記憶隨時間的變化與遺忘機制
- 區分不同層級與狀態的記憶
- 建立主動回憶與被動回憶（夢境）的差異
- 模擬潛意識記憶的浮現（inner voice）
- 動態推薦使用者應回顧的記憶

## 系統架構概念

### 記憶層級（Layer）
表示記憶的穩定性與深度：
- Working Memory：短期、易衰退
- Long-term Memory：較穩定
- Deep Memory：深層、衰退慢、不易消失

### 記憶狀態（State）
表示記憶目前的可提取性：
- Active：正常可被提取
- Suppressed：被封印，不易在一般情況下出現
- Faded：強度過低，僅以模糊形式存在

### 記憶屬性（Attributes）
每筆記憶包含：
- 名稱（name）
- 建立日期（day_created）
- 強度（strength）
- 衰減率（decay_rate）
- 重要性（importance，於建立時設定，後續不改變）
- 回憶次數（review_count）

## 每日運作流程

### 白天（Awake Phase）
1. 使用者可新增多筆記憶
2. 若當天新增過多記憶，系統會加入干擾效果（降低初始強度或提高衰減）
3. 系統產生推薦回憶清單：
   - [URGENT]：理性推薦（重要但快遺忘）
   - [INNER VOICE]：非理性浮現（深層／封印／淡化記憶）
4. 使用者可選擇對記憶進行主動回憶

### 夜晚（Sleep Phase）
1. 系統進行夢境回憶（dream recall）
2. 所有記憶進行每日衰退
3. 執行記憶鞏固（consolidation）
4. 判斷是否進入 faded 狀態

## 回憶機制

### 主動回憶（Active Review）
- 大幅提升記憶強度
- 降低衰減率
- 增加回憶次數

若記憶為封印狀態：
- 主動回憶可解除封印
- 並使記憶強度小幅提升

### 夢境回憶（Dream Recall）
系統從所有記憶中以加權方式選取部分記憶進入夢境。

影響因素包括：
- 記憶距離當前時間
- 記憶強度
- 記憶重要性
- 記憶層級
- 是否為封印記憶

特性：
- 一般記憶在短時間內不易重複出現
- 深層記憶不受重複懲罰
- 封印記憶在夢中被喚起後更容易再次出現

### 內心聲音（Inner Voice）
系統在清醒狀態下，從 deep、suppressed 或 faded 記憶中選出一筆記憶片段浮現。

效果：
- 記憶強度小幅提升
- 提高其後續進入夢境的機率
- 作為推薦回憶清單的一部分

inner voice 不直接改變重要性，僅影響記憶的浮現性。

## 記憶鞏固（Consolidation）
系統依據主動回憶次數進行層級提升：
- review_count ≥ 2：working → long-term
- review_count ≥ 5 且重要性高：long-term → deep

此機制模擬睡眠中記憶的穩定化過程。

## 遺忘與淡化（Forgetting & Faded Memory）
當記憶強度低於某閾值時：
- 記憶進入 faded 狀態

特性：
- 不易被一般查詢提取
- 仍可能在 dream 或 inner voice 中出現
- 可透過主動回憶恢復

## 模糊輸出（Blurred Output）
對於 faded 記憶，系統採用模糊輸出：
- 保留部分字元
- 其餘以符號替代

此設計模擬記憶衰退後的片段與不完整性，並增強 dreamcore 表現。

## 資料結構與演算法

### 資料結構
- 動態陣列儲存記憶
- struct / class 表示記憶屬性

### 演算法
- 排序（Sorting）：產生 urgent 清單
- 搜尋（Searching）：查找記憶
- 篩選（Filtering）：排除 suppressed 記憶
- 加權隨機（Weighted Selection）：夢境記憶抽取
- 動態更新（Dynamic Update）：每日衰退與狀態轉換

## 開發環境
- 程式語言：C++
- 開發工具：Visual Studio Code
- 編譯器：g++
- 版本控制：GitHub
- 執行方式：Command-line

## 時程規劃
- 第1週：系統設計與資料結構規劃
- 第2週：基本資料儲存與新增功能
- 第3週：回憶與衰退機制
- 第4週：夢境與 inner voice 系統
- 第5週：consolidation 與優化
- 第6週：測試與最終整理

## 預期成果
本專題將展示如何透過資料結構與演算法，模擬人類記憶的動態行為。系統不僅具備功能性（查詢、排序、更新），也透過記憶層級、封印機制與模糊輸出等設計，呈現接近真實認知與夢境特性的模型。

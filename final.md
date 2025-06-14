# 國立臺北科技大學
# 2025 資工系物件導向程式設計實習 期末報告
# Author: Group 18, NTUT TataOwO

## 遊戲名稱
- Bloons Tower Defense 3

## 專案簡介

### 遊戲簡介

BTD是我近幾年都有在不斷接觸的遊戲系列，由於機制簡單好理解、畫風樸實無華，於是選擇了這款遊戲來重製。

這次重製的是BTD3，是一款塔防遊戲，場上會有各種顏色的氣球通過跑道，嘗試闖入猴子家，而玩家可以操控並配置各種猴子到場地上，使他們阻止氣球闖入家門。

遊戲提供了4張地圖、1張隱藏地圖，共5張地圖，氣球總共分60波分批出現。每張地圖都有自己的專屬特色 and/or 彩蛋。

### 組別分工

本專案是我自己獨力完成，沒有分工問題

## 遊戲介紹

### 遊戲規則

#### 地圖
進入遊戲時，可以看到畫面上有共4張地圖，由左至右分別是「青青草原」、「冰冰有蛙」、「犧牲、召喚！！！！」、和「我家的吸塵器會後空翻」。另外還有一張隱藏地圖，必須在地圖選擇的畫面中，依序按下"NTUTOOPL"，即可進入隱藏地圖。

#### 猴子
遊戲中提供了6種猴子(塔)用於抵禦氣球的進攻，由左至右、上至下分別是：  
Dart Monkey：最便宜、範圍中、可大量放置  
Super Monkey：價格高昂、但攻擊範圍極大、攻擊速度極快  
Ice Monkey：攻擊範圍小、攻擊速度慢、但被攻擊到的氣球會被暫停移動  
Bomb Shooter：價格中高、攻擊範圍中，擊中氣球後會產生爆炸，並造成大量傷害  
Tack Shooter：攻擊範圍小，每次攻擊會朝四面八方發射8個尖刺，造成多次傷害  
Boomerang Monkey：攻擊範圍中，投射物是迴力鏢，會繞一圈，可以擊中大量氣球

#### 氣球機制
氣球會分成60波出現，每一波都有不同類型的氣球。  
有些氣球會根據顏色有不同的血量，有些甚至有特殊能力，像是免疫爆炸、免疫冰凍、或是死亡時生成更多氣球等。  
每種氣球在進入家門後，就會根據擁有的血量對玩家造成相應的傷害。  
玩家會在打完全部60波時進入勝利畫面，相反的，若在打完60波前就用完血量，則會進入失敗畫面。

#### 按鍵
遊玩過程中，也有一些按鈕可以些微的更改遊戲的進行：  
按鈕A：讓遊戲的波次自動進行 -> **A**utoplay  
按鈕R：顯示跑道路徑 -> toggles **R**oute display  
按鈕W：在沒有氣球的時候，進入下一個波次 -> skip **W**ave  
按鈕M：獲得無限金錢 -> infinite **M**oney  
按鈕H：獲得無限血量 -> infinite **H**ealth  
按鈕D：將血量設為1 -> **D**eath  
按鈕P：顯示密技按鈕 -> hel**P**

#### 地圖彩蛋
「冰冰有蛙」：對地圖由下角的青蛙點擊多次後，會吵到他睡覺，接著他就會追著你的鼠標，在碰到後就會抓住鼠標  
「犧牲、召喚！！！！」：由上面開始順時鐘，按照順序放下以下猴子：Dart, Bomb, Boomerang, Ice, Super, Tack，就可以召喚猴子之神  
「我家的吸塵器會後空翻」：每一個波次，氣球都會根據吸塵器的轉向，而改變他們的路徑

### 遊戲畫面

![image_of_gameplay](https://preview.redd.it/btd3-remake-screenshots-posted-here-because-for-some-reason-v0-f002k968wu6f1.png?width=1080&crop=smart&auto=webp&s=c226031eb0ea02b23fa36c41b26c7d65f4e1fb8f)  
![image_of_the_frog](https://preview.redd.it/btd3-remake-screenshots-posted-here-because-for-some-reason-v0-vzh2cxe8wu6f1.png?width=1080&crop=smart&auto=webp&s=618f99b485f265d63b98ca741f3ca9b17ee7fa23)  
![image_of_the_teleporter](https://preview.redd.it/btd3-remake-screenshots-posted-here-because-for-some-reason-v0-1sl8wtfewu6f1.png?width=1080&crop=smart&auto=webp&s=618ec045401ba31b7b608566fcf70a20843ac875)  
![image_of_the_monking](https://preview.redd.it/btd3-remake-screenshots-posted-here-because-for-some-reason-v0-52t0iniowu6f1.png?width=1080&crop=smart&auto=webp&s=b9e628a2915c5888c23037c019b0af49181b7377)

## 程式設計

### 基本程式架構

![image_of_basic_interfaces_and_or_implementations](https://i.redd.it/mknmcgyg5v6f1.png)

### 程式技術

1. hitboxes  
在程式中，因為有許多物件會根據他的轉向而應有不同的碰撞箱，因此我設計了一組碰撞箱，其中包含圓形、橢圓、長方形、群組，以上四種碰撞箱。  
前三種碰撞箱皆可以自由伸縮、旋轉，使我在設計各類投射物、氣球、按鈕上有能夠減少大量的實作成本。  
而群組碰撞箱則是能任意將以上三種碰撞箱組合起來，變成一個物件，使得我能夠組合出更豐富更大量的形狀、圖形。
2. constants
在設計的過程中，我發現如果沒有統一管理的話，程式中會出現很多零散、不知所以的數字，因此我將大部分的參數一律統整到 `/include/CONSTANTS/` 裡面，並將他們根據類型、功能寫進對應的 `.hpp` 中。一方面是能夠統一管理，另一方面是可以減少使用 JSON 的runtime cost。
3. 狀態機

# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end
# end

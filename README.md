# music-island-B-QT-P
music-island但是QT插件

操作系统版本 deepin20.8

g++版本 8.3.0

C++11

QT版本 5.15.6

# 注意事项
### 使用GPL3.0
## 使用方法:
将so文件复制到 

/usr/lib/dde-dock/plugins(dde-dock)(由于dde-dock高度限制，InformationWidget会显示不全) 

~/.local/lib/dde-top-panel/plugins(dde-top-panel)
## so文件置于Releases
### music-island将创建文件夹(~/.local/lib/music-island-c++p)，用于存放储存数据与下载音乐
### music-island不会自动存储,请自行存储
## 谨慎使用删除文件，数据无价
### music-island.json仅用于使dde-dock/dde-top-panel认为兼容(不可缺少)
# 开始介绍
### 1.我将文件(3MB)放置于这里:
![1.png](show/1.png)
### 2.itemWidget
#### 右键菜单
![2.png](show/2.png)
#### 打开
![3.png](show/3.png)
#### 储存作用于此文件、读取使用此文件
![4.png](show/4.png)
#### 操作演示
![5.gif](show/5.gif)
#### 按下暂停时音量会匀速减小，按下播放时音量会匀速增大
### 3.itemTipsWidget
#### 暂停时
![6.png](show/6.png)
#### 播放时
![7.png](show/7.png)
### 4.itemPopupApplet
#### 外观
![8.png](show/8.png)
#### 音量 0%~100%
#### 进度条 0%~100%
#### 速度 10%~300%
#### 下载按钮
![9.png](show/9.png)
#### 下载按钮右端显示上次搜索的内容,下次搜索时引用
#### 若查找到
![10.png](show/10.png)
#### 若查找不到
![11.png](show/11.png)
#### 查找到后,若音乐有效,加入音乐列表
#### 若无效
![12.png](show/12.png)
#### 下载音乐储存位置
![13.png](show/13.png)
#### 左部右键菜单
![14.png](show/14.png)

播放方式
{

1.循环播放

2.单曲循环

3.随机播放

4.函数播放法(y=(p/q)x^n+b (x为当前播放的音乐在列表中的位置,y为下一首的目标))

}

#### 右部右键菜单
![15.png](show/15.png)
#### 上下移演示
![16.gif](show/16.gif)
#### 移除
![17.png](show/17.png)
#### 删除
![18.png](show/18.png)

## 2023/7/4更新
### 1.itemWidget
#### 右键菜单增加
![19.png](show/19.png)
### 2.新增data2.txt储存字体、颜色数据
![20.png](show/20.png)
### 3.设置后像这样
![21.png](show/new21.png)
### 4.修复itemPopupApplet播放方式UI bug

## 2023/7/9更新
### 修复bug(大概花了6h)
### 增加歌词支持|爬虫时会爬取歌词
#### so文件大小3.6MB
![22.png](show/22.png)
#### itemPopupApplet 拓展
![23.png](show/23.png)
#### 有歌词情况下
![24.png](show/24.png)

![25.png](show/25.png)
#### 无歌词情况下
![26.png](show/26.png)

![27.png](show/27.png)
#### 设置字体颜色与itemWidget原理相同
#### 在data2.txt中储存歌词字体颜色数据
#### 演示
![28.gif](show/28.gif)
## 2023/7/11更新(上次好像写了2024)
### 系统更新deepin20.8->deepin20.9|QT5.15.6->QT5.15.8
#### 1.修改lyric_main内容
![a1.png](show/a1.png)
#### 2.对itemPopupApplet UI进行修改
![a2.png](show/a2.png)
#### 3.针对dde-dock顶头与lyric_main的歌词显示不明显
![a3.gif](show/a3.gif)
#### 4.针对插件的使用与禁用
![a4.gif](show/a4.gif)
## 2023/7/12更新
### 修复爬虫bug&修改QListView与修改QPushButton外观
## 2023/7/13更新
### 在InformationLyric中添加 时长/总时长
![b1.png](show/b1.png)
### 对itemPopupApplet UI进行修改
![b2.png](show/b2.png)
### 首先声明，这不是由music-island引起的
![b3.gif](show/b3.gif)
### 针对dde-dock作出如下修改
![b4.gif](show/b4.gif)
### 修改为：在右键时无法触发InformationWidget中的按钮
### 关于V23Beta不能正常使用
#### 有些github上的dde-dock插件对V23Beta有独立的支持
#### dde-dock会禁用插件
#### QT6与QT5有很大区别，兼容应该不理想
#### 实践是检验真理的唯一标准,所以用V23Beta再编译一次(等我搞定硬件问题再说)
## 2023/8/12更新
### 1.修改判断方式，下载不再出现VIP音乐
### 2.增加试听功能
#### 在按下下载、输入字符后，显示界面
![c1.png](show/c1.png)

{

1.滑动条类似itemPopupApplet的滑动条

2.播放:try_to_listen.play();

![c2.png](show/c2.png)

3.暂停:try_to_listen.pause();

4.选中:下载音乐与歌词，成功后提示"pass"

5.取消:啥也没做

6.上:上一页(放心，不可能出现-1页)

7.下:下一页(若空，显示页码(多数情况是响应问题，等一等))

}
## 2023/8/27更新
### 1.对informationgetmusic增加仅下载音乐功能
![d1.png](show/d1.png)
### 2.对itemPopupApplet增加配置歌词功能
![d2.png](show/d2.png)

![d3.png](show/d3.png)
#### 点击"配置歌词"配置
![d4.png](show/d4.png)
### 3.增加等待执行
![d5.png](show/d5.png)
#### 演示
![d6.gif](show/d6.gif)
### 4.增加QTimer进行更新歌词,间隔10s,不会储存
### 5.将播放速度进行更改
{

原:qreal(int/100)

改:qreal(float/100)

}
### 6.修复下载后停止播放变成播放的bug

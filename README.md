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

项目地址

github: https://githubfast.com/3084793958/music-island-B-QT-P.git

githubfast: https://githubfast.com/3084793958/music-island-B-QT-P.git

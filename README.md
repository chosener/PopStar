# PopStar
消灭星星
		官网:www.isainttech.com
### 开发环境
xcode cocos2d-x 3.2
### 更新
		[2016.1.26]
		1.添加AdView广告.
		2.添加微博,微信,朋友圈,QQ分享功能.
		[2016.1.28]
		1.修改微信,朋友圈分享功能.使用签名包与平台md5一致.
### 备注
		1.重新编译后,assets/ShareSDK.xml,要重新拷贝.
		2.QQ空间,QQ为同一appid,secret.
		3.微信,朋友圈同一appid.
		必须导出带签名包,安装才能分享.原因是apk的md5必须与微信开放平台一致.直接安装为debug签名包.
		与平台md5不一致,点击微信,朋友圈分享不弹出界面.
/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.ds.popstar;

import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.amazon.device.ads.AdLayout;
import com.kyview.AdViewStream;
import com.kyview.AdViewTargeting;
import com.kyview.AdViewTargeting.InstlSwitcher;
import com.kyview.AdViewTargeting.RunMode;
import com.kyview.AdViewTargeting.UpdateMode;
import com.kyview.interfaces.AdInstlInterface;
import com.kyview.interfaces.AdViewInterface;
import com.kyview.screen.interstitial.AdInstlManager;
import com.umeng.analytics.MobclickAgent;
import com.umeng.analytics.game.UMGameAgent;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.Toast;
import cn.sharesdk.framework.ShareSDK;
import cn.sharesdk.onekeyshare.OnekeyShare;

public class AppActivity extends Cocos2dxActivity implements AdViewInterface, AdInstlInterface
{
	// 日志的tag
	public static String		LOG_NAME	= "PopStar";
	public static AppActivity	actInstance;

	// public static final String SDK_ADVIEW =
	// "SDK20111812070129bb9oj4n571faaka";
	public static final String SDK_ADVIEW = "SDK20161725050146nb3xxxufxx8g3sx";

	// public static final String SDK_ADVIEW =
	// "SDK2015141602014343br3teyj7otuyk";//测试

	/** Called when the activity is first created. */
	private AdViewStream	adStream;
	private LinearLayout	layout, layoutXml, layoutCustom;
	private AdLayout		adView	= null;

	static AdInstlManager adInstlManager;

	private static Handler mHandler;

	private static Handler mUIHandler;

	private static int m_enableAD = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		actInstance = this;
		
		mHandler = new Handler();

		ShareSDK.initSDK(actInstance);

		// 初始化友盟sdk
		this.initUMeng();

		// this.initAnySDK();
		this.initAdView();

		this.initInstl();

	}

	private void initUMeng()
	{
		UMGameAgent.setDebugMode(false);// 设置输出运行时日志
		UMGameAgent.init(this);

		MobclickAgent.updateOnlineConfig(actInstance);
	}

	private void initAdView()
	{
		AdViewTargeting.setUpdateMode(UpdateMode.EVERYTIME); // 每次都从服务器取配置

		AdViewTargeting.setAdSize(AdViewTargeting.AdSize.BANNER_AUTO_FILL);

		//AdViewTargeting.setRunMode(RunMode.TEST);

		this.AddBanner();
	}

	private void AddBanner()
	{
		if (adStream != null)
			adStream.setClosed(true);
		if (null != adStream)
		{
			ViewGroup rootView = (ViewGroup) findViewById(android.R.id.content);
			for (int i = 0; i < rootView.getChildCount(); i++)
			{
				if (rootView.getChildAt(i) == adStream)
				{
					rootView.removeView(adStream);
				}
			}
		}
		if (layout != null)
			layout.removeAllViews();
		adStream = new AdViewStream(this, SDK_ADVIEW);
		adStream.setAdViewInterface(this);
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
				FrameLayout.LayoutParams.WRAP_CONTENT);
		params.gravity = Gravity.BOTTOM;
		mFrameLayout.addView(adStream, params);
	}

	private void initInstl()
	{

		// 设置插屏可关闭
		AdViewTargeting.setInstlSwitcherMode(InstlSwitcher.CANCLOSED);
		AdViewTargeting.setInstlDisplayMode(AdViewTargeting.InstlDisplayMode.DIALOG_MODE);
		// 设置大小只支持多盟
		// AdViewTargeting.setAdWidthHeight(300, 250);
		// 设置易传媒是可用，0代表全屏，1代表插屏,默认为0。
		AdViewTargeting.setAdChinaView(0);
		adInstlManager = new AdInstlManager(actInstance, SDK_ADVIEW);
		adInstlManager.setAdInstlInterface(actInstance);

		adInstlManager.requestAd();
	}

	public static void setEnableAD(int enable)
	{
		m_enableAD = enable;
	}

	public static void showMyAD()
	{

		mHandler.post(showMyADi);

		// AnySDKShare.getInstance().share(DataManager.getInstance().getShareInfo());

	}

	private static Runnable showMyADi = new Runnable()
	{
		public void run()
		{

			/*
			 * if (mInterstitialAd.isInterstitialAdReady())
			 * {
			 * mInterstitialAd.showInterstitialAd(actInstance);
			 * }
			 * else
			 * {
			 * // Log.i(LOG_NAME, "Interstitial Ad is not ready");
			 * mInterstitialAd.loadInterstitialAd();
			 * }
			 */

			// 只请求广告，适用于预加载
			// adInstlManager.requestAd();
			// 需要请求广告成功后调用该方法，与requestAd()配合使用
			// adInstlManager.showInstal(actInstance);
			// 请求与展示广告,单独使用
			adInstlManager.requestAndshow();
			// Toast.makeText(actInstance, "调用插屏.", Toast.LENGTH_SHORT).show();

		}
	};

	public static void shareSelfGame()
	{
		mHandler.post(shareGame);
	}

	private static Runnable shareGame = new Runnable()
	{
		public void run()
		{
			showShare();
		}
	};

	private static void showShare()
	{
		ShareSDK.initSDK(actInstance);
		OnekeyShare oks = new OnekeyShare();
		// 关闭sso授权
		oks.disableSSOWhenAuthorize();
		// 分享时Notification的图标和文字 2.5.9以后的版本不调用此方法
		// oks.setNotification(R.drawable.ic_launcher,
		// getString(R.string.app_name));
		// title标题，印象笔记、邮箱、信息、微信、人人网和QQ空间使用
		oks.setTitle("分享Kylin游戏");
		// titleUrl是标题的网络链接，仅在人人网和QQ空间使用
		oks.setTitleUrl("http://www.isainttech.com/?post=58");
		// text是分享文本，所有平台都需要这个字段
		oks.setText("疯狂钻石2016,一起来疯狂吧!!! http://www.isainttech.com/?post=58");
		// imagePath是图片的本地路径，Linked-In以外的平台都支持此参数
		//oks.setImagePath("/sdcard/test.jpg");// 确保SDcard下面存在此张图片
		oks.setImageUrl("http://www.isainttech.com/content/uploadfile/201601/e5221453701250.png");
		// url仅在微信（包括好友和朋友圈）中使用
		oks.setUrl("http://www.isainttech.com/?post=58");
		// comment是我对这条分享的评论，仅在人人网和QQ空间使用
		//oks.setComment("我是测试评论文本");
		// site是分享此内容的网站名称，仅在QQ空间使用
		oks.setSite("Kylin's Games");
		// siteUrl是分享此内容的网站地址，仅在QQ空间使用
		oks.setSiteUrl("http://www.isainttech.com/?post=58");
		// 启动分享GUI
		oks.show(actInstance);
	}

	public void showDialog(String title, String msg)
	{
		final String curMsg = msg;
		final String curTitle = title;

		mUIHandler.post(new Runnable()
		{
			@Override
			public void run()
			{
				new AlertDialog.Builder(actInstance).setTitle(curTitle).setMessage(curMsg)
						.setPositiveButton("Ok", new DialogInterface.OnClickListener()
				{

					@Override
					public void onClick(DialogInterface dialog, int which)
					{

					}
				}).create().show();
			}
		});
	}

	public static void Exit()
	{
		actInstance.finish();
		System.exit(0);

	}

	@Override
	protected void onDestroy()
	{
		ShareSDK.stopSDK();
		super.onDestroy();
	}

	@Override
	protected void onPause()
	{

		UMGameAgent.onPause(actInstance);

		super.onPause();
	}

	@Override
	protected void onResume()
	{

		UMGameAgent.onResume(actInstance);
		super.onResume();
	}

	@Override
	protected void onStop()
	{

		super.onStop();
	}

	@Override
	protected void onRestart()
	{

		super.onRestart();
	}

	public boolean isAppOnForeground()
	{
		ActivityManager activityManager = (ActivityManager) getApplicationContext()
				.getSystemService(Context.ACTIVITY_SERVICE);
		String packageName = getApplicationContext().getPackageName();
		List<RunningAppProcessInfo> appProcesses = activityManager.getRunningAppProcesses();
		if (appProcesses == null)
			return false;
		for (RunningAppProcessInfo appProcess : appProcesses)
		{
			if (appProcess.processName.equals(packageName)
					&& appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND)
			{
				return true;
			}
		}
		return false;
	}

	private boolean isAppForeground = true;

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event)
	{
		if (keyCode == KeyEvent.KEYCODE_BACK)
		{

		}
		return super.onKeyDown(keyCode, event);
	}

	private static int getResourceId(String name, String type)
	{
		return actInstance.getResources().getIdentifier(name, type, actInstance.getPackageName());
	}

	private static LinearLayout myLayout;

	@Override
	public void onClickAd()
	{
		// TODO Auto-generated method stub
		//Log.i(LOG_NAME, "onClickAd");
	}

	@Override
	public void onClosedAd()
	{
		// 如果想立即关闭直接调用：
		// adStream.setClosed(true);

		// 弹出对话框，要求二次确认
		Dialog dialog = new AlertDialog.Builder(this).setTitle("确定要关闭广告？")
				.setNegativeButton("取消", new DialogInterface.OnClickListener()
				{

					@Override
					public void onClick(DialogInterface dialog, int which)
					{
						// 无论是否关闭广告，请务必调用下一行方法，否则广告将停止切换
						// 传入false，广告将不会关闭
						adStream.setClosed(false);
					}
				}).setPositiveButton("确定", new DialogInterface.OnClickListener()
				{

					@Override
					public void onClick(DialogInterface dialog, int which)
					{
						// 无论是否关闭广告，请务必调用下一行方法，否则广告将停止切换
						// 传入true，广告将关闭
						adStream.setClosed(true);
					}
				}).show();
		// 防止误点击关闭对话框，可能使 adStream.setClosed(boolean);不被调用
		dialog.setCanceledOnTouchOutside(false);

	}

	@Override
	public void onDisplayAd()
	{
		// TODO Auto-generated method stub
		//Log.i(LOG_NAME, "onDisplayAd");
	}

	@Override
	public void onAdDismiss()
	{
		// TODO Auto-generated method stub

	}

	@Override
	public void onReceivedAd(int arg0, View arg1)
	{
		// TODO Auto-generated method stub
		//Toast.makeText(actInstance, "ReceivedAd", Toast.LENGTH_SHORT).show();
	}

	@Override
	public void onReceivedAdFailed(String arg0)
	{
		// TODO Auto-generated method stub
		//Toast.makeText(actInstance, "onReceiveAdFailed", Toast.LENGTH_SHORT).show();
	}

}

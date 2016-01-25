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
package org.cocos2dx.cpp;

import java.util.ArrayList;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.anysdk.framework.AdsWrapper;
import com.anysdk.framework.IAPWrapper;
import com.anysdk.framework.PluginWrapper;
import com.anysdk.framework.PushWrapper;
import com.anysdk.framework.RECWrapper;
import com.anysdk.framework.ShareWrapper;
import com.anysdk.framework.SocialWrapper;
import com.anysdk.framework.UserWrapper;
import com.anysdk.framework.java.AnySDK;
import com.anysdk.framework.java.AnySDKAds;
import com.anysdk.framework.java.AnySDKAnalytics;
import com.anysdk.framework.java.AnySDKIAP;
import com.anysdk.framework.java.AnySDKListener;
import com.anysdk.framework.java.AnySDKPush;
import com.anysdk.framework.java.AnySDKREC;
import com.anysdk.framework.java.AnySDKShare;
import com.anysdk.framework.java.AnySDKSocial;
import com.anysdk.framework.java.AnySDKUser;
import com.ds.popstar.R;
import com.umeng.analytics.MobclickAgent;
import com.umeng.analytics.game.UMGameAgent;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import cn.domob.android.ads.AdEventListener;
import cn.domob.android.ads.AdManager.ErrorCode;
import cn.domob.android.ads.AdView;
import cn.domob.android.ads.InterstitialAd;
import cn.domob.android.ads.InterstitialAdListener;
import cn.domob.android.ads.Updater;

public class AppActivity extends Cocos2dxActivity
{
	// 日志的tag
	public static String		LOG_NAME	= "PopStar";
	public static AppActivity	actInstance;

	//56OJyM1ouMGoaSnvCK测试
	//56OJ2XRYuNwcx2AyJr正式
	public static final String	PUBLISHER_ID		= "56OJ2XRYuNwcx2AyJr";
	public static final String	InlinePPID			= "16TLP2daApS2SNUUxhyeI3tk";
	public static final String	InterstitialPPID	= "16TLP2daApS2SNUUsZByeJVk";
	
	//public static final String	PUBLISHER_ID		= "56OJyM1ouMGoaSnvCK";
	//public static final String	InlinePPID			= "16TLwebvAchksY6iO_8oSb-i";
	//public static final String	InterstitialPPID	= "16TLwebvAchksY6iOa7F4DXs";
	
	// public static final String SplashPPID = "16TLwebvAchksY6iOGe3xcik";

	private static Handler mHandler;

	private static Handler mUIHandler;

	AdView mAdview;

	static InterstitialAd mInterstitialAd;
	
	private static int m_enableAD = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		actInstance = this;

		Updater.checkUpdate(this, PUBLISHER_ID);

		this.initBannerAd();

		this.initPluginScreen();

		// 初始化友盟sdk
		this.initUMeng();

		//this.initAnySDK();

	}

	private void initAnySDK()
	{
		String appKey = "65C5083C-9F87-AAC0-AE02-779598C9EC68";
		String appSecret = "f8e7c879e6738361ab022fc23c464ecb";
		String privateKey = "B6E65B55DBB147D8C60C7C7A7FE4D856";
		String oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";
		AnySDK.getInstance().init(this, appKey, appSecret, privateKey, oauthLoginServer);

		/**
		 * 初始化完成后，必须立即为系统设置监听，否则无法即使监听到回调信息
		 */
		setListener();

	}

	private void initUMeng()
	{
		UMGameAgent.setDebugMode(false);// 设置输出运行时日志
		UMGameAgent.init(this);

		MobclickAgent.updateOnlineConfig(actInstance);
	}

	private void initBannerAd()
	{

		// Create ad view
		mAdview = new AdView(this, PUBLISHER_ID, InlinePPID);
		mAdview.setKeyword("game");
		mAdview.setUserGender("male");
		mAdview.setUserBirthdayStr("2000-08-08");
		mAdview.setUserPostcode("123456");
		

		mAdview.setAdEventListener(new AdEventListener()
		{
			@Override
			public void onAdOverlayPresented(AdView adView)
			{
				// Log.i(LOG_NAME, "overlayPresented");
			}

			@Override
			public void onAdOverlayDismissed(AdView adView)
			{
				// Log.i(LOG_NAME, "Overrided be dismissed");
			}

			@Override
			public void onAdClicked(AdView arg0)
			{
				// Log.i(LOG_NAME, "onDomobAdClicked");
			}

			@Override
			public void onLeaveApplication(AdView arg0)
			{
				// Log.i(LOG_NAME, "onDomobLeaveApplication");
			}

			@Override
			public Context onAdRequiresCurrentContext()
			{
				return actInstance;
			}

			@Override
			public void onAdFailed(AdView arg0, ErrorCode arg1)
			{
				// Log.i(LOG_NAME, "onDomobAdFailed");
			}

			@Override
			public void onEventAdReturned(AdView arg0)
			{
				// Log.i(LOG_NAME, "onDomobAdReturned");
			}
		});
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(1150, 150);

		params.gravity = Gravity.BOTTOM;

		mFrameLayout.addView(mAdview, params);

	}

	private void initPluginScreen()
	{
		mHandler = new Handler();

		mInterstitialAd = new InterstitialAd(this, PUBLISHER_ID, InterstitialPPID);

		mInterstitialAd.setInterstitialAdListener(new InterstitialAdListener()
		{
			@Override
			public void onInterstitialAdReady()
			{
				// Log.i(LOG_NAME, "onAdReady");
			}

			@Override
			public void onLandingPageOpen()
			{
				// Log.i(LOG_NAME, "onLandingPageOpen");
			}

			@Override
			public void onLandingPageClose()
			{
				// Log.i(LOG_NAME, "onLandingPageClose");
			}

			@Override
			public void onInterstitialAdPresent()
			{
				// Log.i(LOG_NAME, "onInterstitialAdPresent");
			}

			@Override
			public void onInterstitialAdDismiss()
			{
				// Request new ad when the previous interstitial ad was closed.
				mInterstitialAd.loadInterstitialAd();
				// Log.i(LOG_NAME, "onInterstitialAdDismiss");
			}

			@Override
			public void onInterstitialAdFailed(ErrorCode arg0)
			{
				// Log.i(LOG_NAME, "onInterstitialAdFailed");
			}

			@Override
			public void onInterstitialAdLeaveApplication()
			{
				// Log.i(LOG_NAME, "onInterstitialAdLeaveApplication");

			}

			@Override
			public void onInterstitialAdClicked(InterstitialAd arg0)
			{
				// Log.i(LOG_NAME, "onInterstitialAdClicked");
			}
		});

		mInterstitialAd.loadInterstitialAd();

	}
	
	public static void setEnableAD(int enable)
	{
		m_enableAD = enable;
	}

	public static void showMyAD()
	{

		mHandler.post(showMyADi);
		

		//AnySDKShare.getInstance().share(DataManager.getInstance().getShareInfo());

	}

	private static Runnable showMyADi = new Runnable()
	{
		public void run()
		{

			if (mInterstitialAd.isInterstitialAdReady())
			{
				mInterstitialAd.showInterstitialAd(actInstance);
			}
			else
			{
				// Log.i(LOG_NAME, "Interstitial Ad is not ready");
				mInterstitialAd.loadInterstitialAd();
			}
		}
	};

	public void setListener()
	{
		/**
		 * 为用户系统设置监听
		 */
		AnySDKUser.getInstance().setListener(new AnySDKListener()
		{

			@Override
			public void onCallBack(int arg0, String arg1)
			{
				Log.d(String.valueOf(arg0), arg1);
				switch (arg0)
				{
					case UserWrapper.ACTION_RET_INIT_SUCCESS:// 初始化SDK成功回调
						break;
					case UserWrapper.ACTION_RET_INIT_FAIL:// 初始化SDK失败回调
						Exit();
						break;
					case UserWrapper.ACTION_RET_LOGIN_SUCCESS:// 登陆成功回调
						showDialog(arg1, "User is  online");
						Log.d(LOG_NAME, String.valueOf(AnySDKUser.getInstance().isLogined()));
						break;
					case UserWrapper.ACTION_RET_LOGIN_NO_NEED:// 登陆失败回调
					case UserWrapper.ACTION_RET_LOGIN_TIMEOUT:// 登陆失败回调
					case UserWrapper.ACTION_RET_LOGIN_CANCEL:// 登陆取消回调
					case UserWrapper.ACTION_RET_LOGIN_FAIL:// 登陆失败回调
						showDialog(arg1, "fail");
						AnySDKAnalytics.getInstance().logError("login", "fail");
						break;
					case UserWrapper.ACTION_RET_LOGOUT_SUCCESS:// 登出成功回调
						break;
					case UserWrapper.ACTION_RET_LOGOUT_FAIL:// 登出失败回调
						showDialog(arg1, "登出失败");
						break;
					case UserWrapper.ACTION_RET_PLATFORM_ENTER:// 平台中心进入回调
						break;
					case UserWrapper.ACTION_RET_PLATFORM_BACK:// 平台中心退出回调
						break;
					case UserWrapper.ACTION_RET_PAUSE_PAGE:// 暂停界面回调
						break;
					case UserWrapper.ACTION_RET_EXIT_PAGE:// 退出游戏回调
						Exit();
						break;
					case UserWrapper.ACTION_RET_ANTIADDICTIONQUERY:// 防沉迷查询回调
						showDialog(arg1, "防沉迷查询回调");
						break;
					case UserWrapper.ACTION_RET_REALNAMEREGISTER:// 实名注册回调
						showDialog(arg1, "实名注册回调");
						break;
					case UserWrapper.ACTION_RET_ACCOUNTSWITCH_SUCCESS:// 切换账号成功回调
						break;
					case UserWrapper.ACTION_RET_ACCOUNTSWITCH_FAIL:// 切换账号失败回调
						break;
					case UserWrapper.ACTION_RET_OPENSHOP:// 打开游戏商店回调
						break;
					default:
						break;
				}
			}
		});

		/**
		 * 为支付系统设置监听
		 */
		AnySDKIAP.getInstance().setListener(new AnySDKListener()
		{

			@Override
			public void onCallBack(int arg0, String arg1)
			{
				Log.d(String.valueOf(arg0), arg1);
				String temp = "fail";
				switch (arg0)
				{
					case IAPWrapper.PAYRESULT_INIT_FAIL:// 支付初始化失败回调
						break;
					case IAPWrapper.PAYRESULT_INIT_SUCCESS:// 支付初始化成功回调
						break;
					case IAPWrapper.PAYRESULT_SUCCESS:// 支付成功回调
						temp = "Success";
						showDialog(temp, temp);
						break;
					case IAPWrapper.PAYRESULT_FAIL:// 支付失败回调
						showDialog(temp, temp);
						break;
					case IAPWrapper.PAYRESULT_CANCEL:// 支付取消回调
						showDialog(temp, "Cancel");
						break;
					case IAPWrapper.PAYRESULT_NETWORK_ERROR:// 支付超时回调
						showDialog(temp, "NetworkError");
						break;
					case IAPWrapper.PAYRESULT_PRODUCTIONINFOR_INCOMPLETE:// 支付超时回调
						showDialog(temp, "ProductionInforIncomplete");
						break;
					/**
					 * 新增加:正在进行中回调 支付过程中若SDK没有回调结果，就认为支付正在进行中
					 * 游戏开发商可让玩家去判断是否需要等待，若不等待则进行下一次的支付
					 */
					case IAPWrapper.PAYRESULT_NOW_PAYING:
						showTipDialog();
						break;
					case IAPWrapper.PAYRESULT_RECHARGE_SUCCESS:// 充值成功回调
						break;
					default:
						break;
				}
			}
		});

		/**
		 * 为广告系统设置监听
		 */
		AnySDKAds.getInstance().setListener(new AnySDKListener()
		{

			@Override
			public void onCallBack(int arg0, String arg1)
			{
				Log.d(String.valueOf(arg0), arg1);
				switch (arg0)
				{
					case AdsWrapper.RESULT_CODE_AdsDismissed:// 广告消失回调
						break;
					case AdsWrapper.RESULT_CODE_AdsReceived:// 接受到网络回调
						break;
					case AdsWrapper.RESULT_CODE_AdsShown:// 显示网络回调
						break;
					case AdsWrapper.RESULT_CODE_PointsSpendFailed:// 积分墙消费失败
						break;
					case AdsWrapper.RESULT_CODE_PointsSpendSucceed:// 积分墙消费成功
						break;
					case AdsWrapper.RESULT_CODE_OfferWallOnPointsChanged:// 积分墙积分改变
						break;
					case AdsWrapper.RESULT_CODE_NetworkError:// 网络出错
						break;

					default:
						break;
				}

			}
		});
		/**
		 * 为分享系统设置监听
		 */
		AnySDKShare.getInstance().setListener(new AnySDKListener()
		{

			@Override
			public void onCallBack(int arg0, String arg1)
			{
				Log.d(String.valueOf(arg0), arg1);
				switch (arg0)
				{
					case ShareWrapper.SHARERESULT_CANCEL:// 取消分享
						break;
					case ShareWrapper.SHARERESULT_FAIL:// 分享失败
						break;
					case ShareWrapper.SHARERESULT_NETWORK_ERROR:// 分享网络出错
						break;
					case ShareWrapper.SHARERESULT_SUCCESS:// 分享结果成功
						break;

					default:
						break;
				}

			}
		});
		/**
		 * 为社交系统设置监听
		 */
		AnySDKSocial.getInstance().setListener(new AnySDKListener()
		{

			@Override
			public void onCallBack(int arg0, String arg1)
			{
				Log.d(String.valueOf(arg0), arg1);
				switch (arg0)
				{
					case SocialWrapper.SOCIAL_SIGNIN_FAIL:// 社交登陆失败
						break;
					case SocialWrapper.SOCIAL_SIGNIN_SUCCEED:// 社交登陆成功
						break;
					case SocialWrapper.SOCIAL_SIGNOUT_FAIL:// 社交登出失败
						break;
					case SocialWrapper.SOCIAL_SIGNOUT_SUCCEED:// 社交登出成功
						break;
					case SocialWrapper.SOCIAL_SUBMITSCORE_FAIL:// 提交分数失败
						break;
					case SocialWrapper.SOCIAL_SUBMITSCORE_SUCCEED:// 提交分数成功
						break;
					default:
						break;
				}

			}
		});

		/**
		 * 为推送系统设置监听
		 */
		AnySDKPush.getInstance().setListener(new AnySDKListener()
		{

			@Override
			public void onCallBack(int arg0, String arg1)
			{
				Log.d(String.valueOf(arg0), arg1);
				switch (arg0)
				{
					case PushWrapper.ACTION_RET_RECEIVEMESSAGE:// 接受到推送消息

						break;

					default:
						break;
				}
			}
		});

		// 为录屏分享系统设置监听
		AnySDKREC.getInstance().setListener(new AnySDKListener()
		{

			@Override
			public void onCallBack(int arg0, String arg1)
			{
				Log.d(String.valueOf(arg0), arg1);
				switch (arg0)
				{
					case RECWrapper.RECRESULT_RECINITSUCCESSS:// 初始化成功
						Log.d(LOG_NAME, "RECRESULT_RECINITSUCCESSS\n");
						break;
					case RECWrapper.RECRESULT_RECINITFAIL:// 初始化失败
						Log.d(LOG_NAME, "RECRESULT_RECINITFAIL\n");
						break;
					case RECWrapper.RECRESULT_RECSTARTRECORDING:// 开始录制
						Log.d(LOG_NAME, "RECRESULT_RECSTARTRECORDING \n");
						break;
					case RECWrapper.RECRESULT_RECSTOPRECORDING:// 结束录制
						Log.d(LOG_NAME, "RECRESULT_RECSTOPRECORDING \n");
						break;
					case RECWrapper.RECRESULT_RECPAUSEECORDING:// 暂停录制
						Log.d(LOG_NAME, "RECRESULT_RECPAUSEECORDING \n");
						break;
					case RECWrapper.RECRESULT_RECRESUMERECORDING:// 恢复录制
						Log.d(LOG_NAME, "RECRESULT_RECRESUMERECORDING \n");
						break;
					case RECWrapper.RECRESULT_RECENTERSDKPAGE:// 进入SDK页面
						Log.d(LOG_NAME, "RECRESULT_RECENTERSDKPAGE \n");
						break;
					case RECWrapper.RECRESULT_RECOUTSDKPAGE:// 退出SDK页面
						Log.d(LOG_NAME, "RECRESULT_RECOUTSDKPAGE \n");
						break;
					case RECWrapper.RECRESULT_RECSHARESUCCESS:// 视频分享成功
						Log.d(LOG_NAME, "RECRESULT_RECSHARESUCCESS \n");
						break;
					case RECWrapper.RECRESULT_RECSHAREFAIL:// 视频分享失败
						Log.d(LOG_NAME, "RECRESULT_RECSHAREFAIL \n");
						break;
					default:
						break;
				}

			}
		});
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

	public void showTipDialog()
	{

		mUIHandler.post(new Runnable()
		{
			@Override
			public void run()
			{
				new AlertDialog.Builder(actInstance).setTitle(R.string.paying_title).setMessage(R.string.paying_message)
						.setPositiveButton("NO", new DialogInterface.OnClickListener()
				{

					@Override
					public void onClick(DialogInterface dialog, int which)
					{
						/**
						 * 重置支付状态
						 */
						AnySDKIAP.getInstance().resetPayState();
					}
				}).setNegativeButton("YES", new DialogInterface.OnClickListener()
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
		PluginWrapper.onDestroy();
		AnySDK.getInstance().release();
		super.onDestroy();
	}

	@Override
	protected void onPause()
	{

		UMGameAgent.onPause(this);
		PluginWrapper.onPause();
		super.onPause();
	}

	@Override
	protected void onResume()
	{

		UMGameAgent.onResume(this);
		PluginWrapper.onResume();
		super.onResume();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		PluginWrapper.onActivityResult(requestCode, resultCode, data);
		super.onActivityResult(requestCode, resultCode, data);
	}

	@Override
	protected void onNewIntent(Intent intent)
	{
		PluginWrapper.onNewIntent(intent);
		super.onNewIntent(intent);
	}

	@Override
	protected void onStop()
	{
		PluginWrapper.onStop();
		super.onStop();
	}

	@Override
	protected void onRestart()
	{
		PluginWrapper.onRestart();
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
			/**
			 * 判断是否支持调用退出界面的接口
			 */
			if (AnySDKUser.getInstance().isFunctionSupported("exit"))
			{
				AnySDKUser.getInstance().callFunction("exit");

				return true;
			}
		}
		return super.onKeyDown(keyCode, event);
	}

	private static int getResourceId(String name, String type)
	{
		return actInstance.getResources().getIdentifier(name, type, actInstance.getPackageName());
	}

	private static LinearLayout myLayout;

	/**
	 * 
	 * @Title: ChoosePayMode
	 * @Description: 多支付调用方法
	 * @param @param payMode
	 * @return void
	 * @throws
	 */
	public static void ChoosePayMode(ArrayList<String> payMode)
	{
		myLayout = new LinearLayout(actInstance);
		OnClickListener onclick = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				AnySDKIAP.getInstance().payForProduct((String) v.getTag(),
						DataManager.getInstance().getProductionInfo());
			}
		};
		for (int i = 0; i < payMode.size(); i++)
		{
			Button button = new Button(actInstance);
			String res = "Channel" + payMode.get(i);
			button.setText(getResourceId(res, "string"));
			button.setOnClickListener(onclick);
			button.setTag(payMode.get(i));
			myLayout.addView(button);
		}

		AlertDialog.Builder dialog02 = new AlertDialog.Builder(actInstance);
		dialog02.setView(myLayout);
		dialog02.setTitle("UI PAY");

		dialog02.show();
	}

}

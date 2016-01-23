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

import org.cocos2dx.lib.Cocos2dxActivity;

import com.umeng.analytics.MobclickAgent;
import com.umeng.analytics.game.UMGameAgent;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Gravity;
import android.widget.FrameLayout;
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

	public static final String	PUBLISHER_ID		= "56OJ2XRYuNwcx2AyJr";
	public static final String	InlinePPID			= "16TLP2daApS2SNUUxhyeI3tk";
	public static final String	InterstitialPPID	= "16TLP2daApS2SNUUsZByeJVk";
	// public static final String SplashPPID = "16TLwebvAchksY6iOGe3xcik";

	private static Handler mHandler;

	AdView mAdview;

	static InterstitialAd mInterstitialAd;

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
				//Log.i(LOG_NAME, "overlayPresented");
			}

			@Override
			public void onAdOverlayDismissed(AdView adView)
			{
				//Log.i(LOG_NAME, "Overrided be dismissed");
			}

			@Override
			public void onAdClicked(AdView arg0)
			{
				//Log.i(LOG_NAME, "onDomobAdClicked");
			}

			@Override
			public void onLeaveApplication(AdView arg0)
			{
				//Log.i(LOG_NAME, "onDomobLeaveApplication");
			}

			@Override
			public Context onAdRequiresCurrentContext()
			{
				return actInstance;
			}

			@Override
			public void onAdFailed(AdView arg0, ErrorCode arg1)
			{
				//Log.i(LOG_NAME, "onDomobAdFailed");
			}

			@Override
			public void onEventAdReturned(AdView arg0)
			{
				//Log.i(LOG_NAME, "onDomobAdReturned");
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
				//Log.i(LOG_NAME, "onAdReady");
			}

			@Override
			public void onLandingPageOpen()
			{
				//Log.i(LOG_NAME, "onLandingPageOpen");
			}

			@Override
			public void onLandingPageClose()
			{
				//Log.i(LOG_NAME, "onLandingPageClose");
			}

			@Override
			public void onInterstitialAdPresent()
			{
				//Log.i(LOG_NAME, "onInterstitialAdPresent");
			}

			@Override
			public void onInterstitialAdDismiss()
			{
				// Request new ad when the previous interstitial ad was closed.
				mInterstitialAd.loadInterstitialAd();
				//Log.i(LOG_NAME, "onInterstitialAdDismiss");
			}

			@Override
			public void onInterstitialAdFailed(ErrorCode arg0)
			{
				//Log.i(LOG_NAME, "onInterstitialAdFailed");
			}

			@Override
			public void onInterstitialAdLeaveApplication()
			{
				//Log.i(LOG_NAME, "onInterstitialAdLeaveApplication");

			}

			@Override
			public void onInterstitialAdClicked(InterstitialAd arg0)
			{
				//Log.i(LOG_NAME, "onInterstitialAdClicked");
			}
		});

		mInterstitialAd.loadInterstitialAd();

	}

	public static void showMyAD()
	{

		mHandler.post(showMyADi);

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
				//Log.i(LOG_NAME, "Interstitial Ad is not ready");
				mInterstitialAd.loadInterstitialAd();
			}
		}
	};
	
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		
		UMGameAgent.onResume(this);
	}
	
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		
		UMGameAgent.onPause(this);
	}
}

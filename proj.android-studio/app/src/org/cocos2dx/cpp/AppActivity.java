/****************************************************************************
Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.Toast;

import net.youmi.android.AdManager;
import net.youmi.android.normal.banner.BannerManager;
import net.youmi.android.normal.banner.BannerViewListener;
import org.cocos2dx.lib.Cocos2dxActivity;

public class AppActivity extends Cocos2dxActivity {

    private static Handler sHandler;

    private View mBannerView;

    private final static int SHOW_BANNER_AD = 103;

    private final static int HIDE_BANNER_AD = 104;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initSDK();
        initHandler();
    }

    private void initSDK() {
        // 初始化接口，应用启动的时候调用，参数：appId, appSecret, 是否开启调试模式, 是否开启有米日志
        AdManager.getInstance(this).init("c845d0d4fa076f16", "ae816683da281fa6", true, true);
    }

    /**
     * 展示广告条
     */
    private void internalShowBannerAd() {
        if (mBannerView == null) {
            // 获取广告条
            mBannerView = BannerManager.getInstance(this)
                    .getBannerView(this, new BannerViewListener() {
                        @Override
                        public void onRequestSuccess() {
                            showToastOnUiThread("请求广告条成功", Toast.LENGTH_SHORT);
                        }

                        @Override
                        public void onSwitchBanner() {
                            showToastOnUiThread("广告条切换", Toast.LENGTH_SHORT);
                        }

                        @Override
                        public void onRequestFailed() {
                            showToastOnUiThread("请求广告条失败", Toast.LENGTH_LONG);
                        }
                    });
            // 使用WindowManager来展示广告条
            WindowManager mWindowManager = (WindowManager) this.getSystemService(Context.WINDOW_SERVICE);
            WindowManager.LayoutParams mWmParams = new WindowManager.LayoutParams();
            mWmParams.flags = WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
            mWmParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
            mWmParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
            mWmParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_ATTACHED_DIALOG;
            mWmParams.alpha = 1.0F;
            mWmParams.format = 1;
            mWmParams.gravity = Gravity.BOTTOM | Gravity.RIGHT; // 这里示例为：在右下角展示广告条条
            mWindowManager.addView(mBannerView, mWmParams);
        }
    }

    /**
     * 隐藏广告条
     */
    private void internalHideBannerAd() {
        if (mBannerView != null) {
            ((WindowManager) this.getSystemService(Context.WINDOW_SERVICE)).removeView(mBannerView);
            mBannerView = null;
        }
    }

    private void initHandler() {
        sHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                switch (msg.what) {
                    case SHOW_BANNER_AD:
                        internalShowBannerAd();
                        break;
                    case HIDE_BANNER_AD:
                        internalHideBannerAd();
                        break;
                    default:
                        break;
                }
            }
        };
    }

    /**
     * 展示广告条
     */
    public static void showBannerAd() {
        sendMsgToHandler(SHOW_BANNER_AD);
    }

    /**
     * 隐藏广告条
     */
    public static void hideBannerAd() {
        sendMsgToHandler(HIDE_BANNER_AD);
    }

    /**
     * 退出应用
     */
    public static void exitApp() {
        // 如果无法保证应用主界面的 onDestroy() 方法被执行到，请移动以下接口到应用的退出逻辑里面调用

        // 展示广告条窗口的 onDestroy() 回调方法中调用
        BannerManager.getInstance(getContext()).onDestroy();
    }

    private synchronized static void sendMsgToHandler(int type) {
        Message msg = sHandler.obtainMessage();
        msg.what = type;
        msg.sendToTarget();
    }

    public static void showToastOnUiThread(final String str, final int duration) {
        if (Looper.myLooper() == Looper.getMainLooper()) {
            Toast.makeText(getContext(), str, duration).show();
        } else {
            sHandler.post(new Runnable() {

                @Override
                public void run() {
                    Toast.makeText(getContext(), str, duration).show();
                }
            });
        }
    }
}

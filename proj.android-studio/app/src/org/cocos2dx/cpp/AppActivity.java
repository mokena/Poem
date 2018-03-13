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
import net.youmi.android.normal.common.ErrorCode;
import net.youmi.android.normal.spot.SpotListener;
import net.youmi.android.normal.spot.SpotManager;

import org.cocos2dx.lib.Cocos2dxActivity;

public class AppActivity extends Cocos2dxActivity {

    private static Handler sHandler;

    private final static int SHOW_SPOT_AD = 100;

    private final static int HIDE_SPOT_AD = 101;

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

    private void initHandler() {
        sHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                switch (msg.what) {
                    case SHOW_SPOT_AD:
                        internalShowSpotAd();
                        break;
                    case HIDE_SPOT_AD:
                        internalHideSpotAd();
                        break;
                    default:
                        break;
                }
            }
        };
    }

    /**
     * 设置插屏广告
     */
    private void setupSpotAd() {
        // 设置插屏图片类型，默认竖图
        // 横图
        //SpotManager.getInstance(this).setImageType(SpotManager.IMAGE_TYPE_HORIZONTAL);
        // 竖图
        SpotManager.getInstance(this).setImageType(SpotManager.IMAGE_TYPE_VERTICAL);
        //
        // 设置动画类型，默认高级动画
        // 无动画
        // SpotManager.getInstance(this).setAnimationType(SpotManager.ANIMATION_TYPE_NONE);
        // 简单动画
        // SpotManager.getInstance(this).setAnimationType(SpotManager.ANIMATION_TYPE_SIMPLE);
        // 高级动画
        SpotManager.getInstance(this).setAnimationType(SpotManager.ANIMATION_TYPE_ADVANCED);
    }

    /**
     * 展示插屏广告
     */
    private void internalShowSpotAd() {
        SpotManager.getInstance(getContext()).showSpot(getContext(), new SpotListener() {
            @Override
            public void onShowSuccess() {
                showToastOnUiThread("插屏展示成功", Toast.LENGTH_SHORT);
            }

            @Override
            public void onShowFailed(int errorCode) {
                switch (errorCode) {
                    case ErrorCode.NON_NETWORK:
                        showToastOnUiThread("插屏展示失败 - 网络异常", Toast.LENGTH_LONG);
                        break;
                    case ErrorCode.NON_AD:
                        showToastOnUiThread("插屏展示失败 - 暂无插屏广告", Toast.LENGTH_LONG);
                        break;
                    case ErrorCode.RESOURCE_NOT_READY:
                        showToastOnUiThread("插屏展示失败 - 插屏资源还没准备好", Toast.LENGTH_LONG);
                        break;
                    case ErrorCode.SHOW_INTERVAL_LIMITED:
                        showToastOnUiThread("插屏展示失败 - 请勿频繁展示", Toast.LENGTH_LONG);
                        break;
                    case ErrorCode.WIDGET_NOT_IN_VISIBILITY_STATE:
                        showToastOnUiThread("插屏展示失败 - 请设置插屏为可见状态", Toast.LENGTH_LONG);
                        break;
                    default:
                        showToastOnUiThread("插屏展示失败 - 请稍后再试", Toast.LENGTH_LONG);
                        break;
                }
            }

            @Override
            public void onSpotClosed() {
                showToastOnUiThread("插屏被关闭", Toast.LENGTH_SHORT);
            }

            @Override
            public void onSpotClicked(boolean isWebPage) {
                showToastOnUiThread("插屏被点击", Toast.LENGTH_SHORT);
            }
        });
    }

    /**
     * 隐藏插屏广告
     */
    private void internalHideSpotAd() {
        SpotManager.getInstance(this).hideSpot();
    }

    /**
     * 展示插屏广告（这个方法在后续步骤中将会被C++通过JNI调用）
     */
    public static void showSpotAd() {
        Message msg = sHandler.obtainMessage();
        msg.what = SHOW_SPOT_AD;
        msg.sendToTarget();
    }

    /**
     * 隐藏插屏广告（这个方法在后续步骤中将会被C++通过JNI调用）
     *
     * @return 当插屏正在展示，而且隐藏插屏成功，返回 {@code true}；插屏没有展示，则返回 {@code false}
     */
    public static boolean hideSpotAd() {
        if (SpotManager.getInstance(getContext()).isSpotShowing()) {
            Message msg = sHandler.obtainMessage();
            msg.what = HIDE_SPOT_AD;
            msg.sendToTarget();
            return true;
        }
        return false;
    }

    /**
     * 退出应用
     */
    public static void exitApp() {
        // 退出应用时调用，用于释放资源
        // 如果无法保证应用主界面的 onDestroy() 方法被执行到，请移动以下接口到应用的退出逻辑里面调用

        // 插屏广告
        SpotManager.getInstance(getContext()).onDestroy();

        // 插屏广告（包括普通插屏广告、轮播插屏广告、原生插屏广告）
        SpotManager.getInstance(getContext()).onAppExit();
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


    @Override
    protected void onPause() {
        super.onPause();
        // 插屏广告
        SpotManager.getInstance(this).onPause();
    }

    @Override
    protected void onStop() {
        super.onStop();
        // 插屏广告
        SpotManager.getInstance(this).onStop();
    }
}

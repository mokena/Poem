/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
 
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

import net.youmi.android.AdManager;
import net.youmi.android.normal.common.ErrorCode;
import net.youmi.android.normal.spot.SpotListener;
import net.youmi.android.normal.spot.SpotManager;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.Toast;

public class AppActivity extends Cocos2dxActivity {
	
	static Handler sHandler;
	static final int SHOW_SPOT_AD = 0;
	static final int HIDE_SPOT_AD = 1;
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // ��ʼ��SDK
        initSDK();
        
        // ���ò������
        setupSpotAd();
        
        initHandler();
	}
	
	/**
	 * ��ʼ��SDK
	 */
	private void initSDK() {
	    // ��ʼ���ӿڣ�Ӧ��������ʱ����ã�������appId, appSecret, �Ƿ�������ģʽ, �Ƿ���������־
	    AdManager.getInstance(this).init("ccd5fc275d7acd38", "a2e23077aa3472fa", false, false);
	}
	
	/**
	 * ���ò������
	 */
	private void setupSpotAd() {
	    // ���ò���ͼƬ���ͣ�Ĭ����ͼ
	    // ��ͼ
	    SpotManager.getInstance(this).setImageType(SpotManager.IMAGE_TYPE_HORIZONTAL);
	    
	    SpotManager.getInstance(this).setAnimationType(SpotManager.ANIMATION_TYPE_ADVANCED);
	}
	
	@Override
    protected void onPause() {
        super.onPause();
        // �������
        SpotManager.getInstance(this).onPause();
    }

    @Override
    protected void onStop() {
        super.onStop();
        // �������
        SpotManager.getInstance(this).onStop();
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
     * չʾ������棨��������ں��������н��ᱻC++ͨ��JNI���ã�
     */
    public static void showSpotAd() {
        Message msg = sHandler.obtainMessage();
        msg.what = SHOW_SPOT_AD;
        msg.sendToTarget();
    }

    /**
     * ���ز�����棨��������ں��������н��ᱻC++ͨ��JNI���ã�
     *
     * @return ����������չʾ���������ز����ɹ������� {@code true}������û��չʾ���򷵻� {@code false}
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
     * �˳�Ӧ��
     */
    public static void exitApp() {
        // �˳�Ӧ��ʱ���ã������ͷ���Դ
        // ����޷���֤Ӧ��������� onDestroy() ������ִ�е������ƶ����½ӿڵ�Ӧ�õ��˳��߼��������

        // �������
        SpotManager.getInstance(getContext()).onDestroy();

        // ������棨������ͨ������桢�ֲ�������桢ԭ��������棩
        SpotManager.getInstance(getContext()).onAppExit();
    }
    
    /**
     * չʾ�������
     */
    private void internalShowSpotAd() {
        SpotManager.getInstance(getContext()).showSpot(getContext(), new SpotListener() {
            @Override
            public void onShowSuccess() {
                Toast.makeText(AppActivity.this, "����չʾ�ɹ�", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onShowFailed(int errorCode) {
                switch (errorCode) {
                case ErrorCode.NON_NETWORK:
                	Toast.makeText(AppActivity.this, "����չʾʧ�� - �����쳣", Toast.LENGTH_LONG).show();
                    break;
                case ErrorCode.NON_AD:
                	Toast.makeText(AppActivity.this, "����չʾʧ�� - ���޲������", Toast.LENGTH_LONG).show();
                    break;
                case ErrorCode.RESOURCE_NOT_READY:
                	Toast.makeText(AppActivity.this, "����չʾʧ�� - ������Դ��û׼����", Toast.LENGTH_LONG).show();
                    break;
                case ErrorCode.SHOW_INTERVAL_LIMITED:
                	Toast.makeText(AppActivity.this, "����չʾʧ�� - ����Ƶ��չʾ", Toast.LENGTH_LONG).show();
                    break;
                case ErrorCode.WIDGET_NOT_IN_VISIBILITY_STATE:
                	Toast.makeText(AppActivity.this, "����չʾʧ�� - �����ò���Ϊ�ɼ�״̬", Toast.LENGTH_LONG).show();
                    break;
                default:
                	Toast.makeText(AppActivity.this, "����չʾʧ�� - ���Ժ�����", Toast.LENGTH_LONG).show();
                    break;
                }
            }

            @Override
            public void onSpotClosed() {
            	Toast.makeText(AppActivity.this, "�������ر�", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onSpotClicked(boolean isWebPage) {
            	Toast.makeText(AppActivity.this, "���������", Toast.LENGTH_SHORT).show();
            }
        });
    }
    
    /**
     * ���ز������
     */
    private void internalHideSpotAd() {
        SpotManager.getInstance(this).hideSpot();
    }
    
}

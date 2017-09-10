package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import cn.immob.sdk.AdType;
import cn.immob.sdk.ImmobView;
import cn.immob.sdk.LMAdListener;

public class AdActivity extends Activity {
	
	protected FrameLayout mFrameLayout = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//�����µ�ImmobView �������123456abcdef �滻Ϊ������ƽ̨��������õĹ��λID��
		ImmobView lmView = new ImmobView(this, "301a428b05895df9a2e0ad85768af09f", AdType.FULLSCREEN);
		// ���ù�����,��ʵ�ּ����ӿڵķ���,�����¼��ص�����ο��±߹���¼��ص�����
		lmView.setAdListener(new LMAdListener(){

			@Override
			public void onAdReceived(ImmobView arg0) {
				Log.i("POEM", "ads load ok");
			}

			@Override
			public void onDismissScreen(ImmobView arg0) {
			}

			@Override
			public void onFailedToReceiveAd(ImmobView arg0, int arg1) {
				Log.i("POEM", "ads load failed");
			}

			@Override
			public void onLeaveApplication(ImmobView arg0) {
			}

			@Override
			public void onPresentScreen(ImmobView arg0) {
			}});
		//Ϊ���ImmobView ����ָ��һ�ֲ��ַ�ʽ
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT,
				FrameLayout.LayoutParams.WRAP_CONTENT);
		lmView.setLayoutParams(params);
		
		ViewGroup.LayoutParams framelayout_params =
	            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
	                                       ViewGroup.LayoutParams.MATCH_PARENT);

        mFrameLayout = new FrameLayout(this);

        mFrameLayout.setLayoutParams(framelayout_params);
        
        
		//��lmView ׷�ӵ���ָ���������С�
        mFrameLayout.addView(lmView, params);
		//��ʾlmView��
		lmView.display();
		setContentView(mFrameLayout);
		
		Thread thread=new Thread(new Runnable()  
        {  
            @Override  
            public void run()  
            {  
                try {
					Thread.sleep(3);
					
					Intent intent = new Intent(AdActivity.this, AppActivity.class);
		            AdActivity.this.startActivity(intent);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
            }  
        });  
        thread.start();  
	}
	
}

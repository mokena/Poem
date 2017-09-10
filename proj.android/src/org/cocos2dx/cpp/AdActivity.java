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
		//创建新的ImmobView 对象，请把123456abcdef 替换为从力美平台申请所获得的广告位ID。
		ImmobView lmView = new ImmobView(this, "301a428b05895df9a2e0ad85768af09f", AdType.FULLSCREEN);
		// 设置广告监听,并实现监听接口的方法,具体事件回调，请参考下边广告事件回调方法
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
		//为这个ImmobView 对象指派一种布局方式
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT,
				FrameLayout.LayoutParams.WRAP_CONTENT);
		lmView.setLayoutParams(params);
		
		ViewGroup.LayoutParams framelayout_params =
	            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
	                                       ViewGroup.LayoutParams.MATCH_PARENT);

        mFrameLayout = new FrameLayout(this);

        mFrameLayout.setLayoutParams(framelayout_params);
        
        
		//将lmView 追加到你指定的容器中。
        mFrameLayout.addView(lmView, params);
		//显示lmView，
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

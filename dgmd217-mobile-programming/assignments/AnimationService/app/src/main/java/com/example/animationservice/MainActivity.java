package com.example.animationservice;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    Messenger mService;
    boolean mBound = false;

    private final ServiceConnection mConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName className, IBinder service) {
            mService = new Messenger(service);
            mBound = true;
        }

        @Override
        public void onServiceDisconnected(ComponentName arg) {
            mService = null;
            mBound = false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void onStart() {
        super.onStart();

        Intent intent = new Intent(this, AnimationService.class);
        MyGLSurfaceView glView = findViewById(R.id.glView);
        Messenger angleReceiver = glView.getAngleReceiver();

        intent.putExtra("valueMessenger", angleReceiver);
        intent.putExtra("StartValue", 0.0f);
        intent.putExtra("EndValue", 360.0f);
        intent.putExtra("IncValue", 1.0f);
        intent.putExtra("UpdateTime", 10.0f);

        bindService(intent, mConnection, BIND_AUTO_CREATE);
    }

    @Override
    protected void onStop() {
        super.onStop();

        if (mBound) {
            unbindService(mConnection);
            mBound = false;
        }
    }

    public void onClickStart(View view) {
        if (mBound && mService != null) {
            try {
                Message msg = Message.obtain(null, AnimationService.MSG_START_ROTATING, 0, 0);
                mService.send(msg);
            } catch (Exception ignored) {
                // Do nothing
            }
        }
    }

    public void onClickStop(View view) {
        if (mBound && mService != null) {
            try {
                Message msg = Message.obtain(null, AnimationService.MSG_STOP_ROTATING, 0, 0);
                mService.send(msg);
            } catch (Exception ignored) {
                // Do nothing
            }
        }
    }
}

package com.example.animationservice;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Messenger;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onClickStart(View view) {
        Intent intent = new Intent(this, AnimationService.class);
        MyGLSurfaceView glView = (MyGLSurfaceView) findViewById(R.id.glView);
        Messenger angleReceiver = glView.getAngleReceiver();

        intent.putExtra("valueMessenger", angleReceiver);
        intent.putExtra("StartValue", 0.0f);
        intent.putExtra("EndValue", 360.0f);
        intent.putExtra("IncValue", 1.0f);
        intent.putExtra("UpdateTime", 100.0f);

        startService(intent);
    }
}

package com.example.lunarlander;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;


public class LunarLander extends AppCompatActivity {
    private LunarView mLunarView;
    private LanderAnimator animator;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.lunar_layout);
        mLunarView = (LunarView) findViewById(R.id.lunar);

        // Write here code to start LanderAnimator.
        animator = new LanderAnimator(mLunarView);
        animator.execute(mLunarView.getLanderX(), mLunarView.getLanderY());
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    public void onTouch(View view) {
        // Implement this callback method.
        // If the lander is moving, it should stop.
        // If the lander is not moving, it starts to go.
        animator.pauseAnimator();
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }

}

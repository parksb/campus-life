package com.example.lunarlander;

import android.animation.ValueAnimator;
import android.os.AsyncTask;
import android.view.animation.AccelerateDecelerateInterpolator;


public class LanderAnimator extends AsyncTask<Integer, Integer, Integer> {

    private LunarView mLanderView;
    private ValueAnimator animator;

    private boolean mPaused = false;
    private int mX, mY;

    // Define constructor..
    public LanderAnimator(LunarView lander) {
        mLanderView = lander;
    }

    protected Integer doInBackground(Integer... integers) {
        // Implement code to update the lander position in a loop
        // Use publishProgress() to update lander position.
        mX = integers[0];
        mY = integers[1];

        while (true) {
            if (!mPaused) {
                mX += 5;
                mY += 5;
                if (mX >= mLanderView.getWidth()) mX = 0;
                publishProgress(mX, mY);
            }

            try {
                Thread.sleep(100);
            } catch (Exception ignored) {}
        }
    }

    @Override
    protected void onProgressUpdate(Integer... values) {
        super.onProgressUpdate(values);

        // Put code to update the lander position with values.
        mLanderView.setLanderPos(values[0], values[1]);
        mLanderView.invalidate();
    }

    public void pauseAnimator() {
        mPaused = (!mPaused);
        if (animator != null && animator.isRunning()) animator.isPaused();
        else if (animator != null && animator.isPaused()) animator.resume();
    }

    public void fire() {
        if (animator != null && animator.isRunning()) return;

        animator = ValueAnimator.ofFloat(mY, mY - (mLanderView.getHeight() * (float)(1 / 10)));
        animator.setInterpolator(new AccelerateDecelerateInterpolator());
        animator.addUpdateListener(valueAnimator -> {
            mY -= 5;
            if (mY < 0) mY = 0;
        });

        animator.start();
    }

}

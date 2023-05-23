package com.example.lunarlander;

import android.os.AsyncTask;


public class LanderAnimator extends AsyncTask<Integer, Integer, Integer> {

    private LunarView mLanderView;
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

    private boolean mPaused = false;
    public void pauseAnimator() {
        mPaused = (!mPaused);
    }

}

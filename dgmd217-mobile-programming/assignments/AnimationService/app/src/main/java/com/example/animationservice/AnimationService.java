package com.example.animationservice;

import android.animation.ValueAnimator;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.view.animation.OvershootInterpolator;

import androidx.annotation.NonNull;

public class AnimationService extends Service {
    public static final int MSG_STOP_ROTATING = 0;
    public static final int MSG_START_ROTATING = 1;

    private Messenger valMessenger;
    private ValueAnimator animator;

    public void startRotating() {
        if (!animator.isStarted()) {
            animator.start();
        } else if (animator.isPaused()) {
            animator.resume();
        }
    }
    public void stopRotating() {
        if (animator.isRunning()) {
            animator.pause();
        }
    }

    static class IncomingHandler extends Handler {
        private final AnimationService service;

        IncomingHandler(Context ctx) {
            service = (AnimationService) ctx;
        }

        @Override
        public void handleMessage(@NonNull Message message) {
            switch (message.what) {
                case MSG_START_ROTATING:
                    service.startRotating();
                    break;
                case MSG_STOP_ROTATING:
                    service.stopRotating();
                    break;
                default:
                    super.handleMessage(message);
            }
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        Messenger mMessenger = new Messenger(new IncomingHandler(this));

        valMessenger = (Messenger) intent.getExtras().get("valueMessenger");
        float startAngle = intent.getFloatExtra("StartValue", 0);
        float endAngle = intent.getFloatExtra("EndValue", 0);
        long stepTime = intent.getLongExtra("UpdateTime", 3000);

        animator = ValueAnimator.ofFloat(startAngle, endAngle);
        animator.setDuration(stepTime);
        animator.setInterpolator(new OvershootInterpolator());
        animator.setRepeatCount(0);
        animator.addUpdateListener(valueAnimator -> {
            Message msg = Message.obtain();
            msg.obj = animator.getAnimatedValue();
            try {
                valMessenger.send(msg);
            } catch (RemoteException ignored) {
                // Do nothing
            }
        });

        return mMessenger.getBinder();
    }
}

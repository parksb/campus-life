package com.example.animationservice;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;

import androidx.annotation.NonNull;

public class AnimationService extends Service {
    public static final int MSG_STOP_ROTATING = 0;
    public static final int MSG_START_ROTATING = 1;

    private Messenger valMessenger;
    private float startAngle;
    private float endAngle;
    private float incAngle;
    private float stepTime;

    private boolean isRotating = false;

    public void startRotating() {
        isRotating = true;

        if (Float.compare(startAngle, endAngle) == 0) {
            startAngle = 0.0f;
        }

        while (startAngle < endAngle && isRotating) {
            Message msg = Message.obtain();
            msg.obj = startAngle;
            try {
                valMessenger.send(msg);
                Thread.sleep((long) stepTime);
            } catch (RemoteException | InterruptedException ignored) {
                // Do nothing
            }

            startAngle += incAngle;
        }

        isRotating = false;
    }
    public void stopRotating() {
        isRotating = false;
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
                    if (!service.isRotating) new Thread(service::startRotating).start();
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
        startAngle = intent.getFloatExtra("StartValue", 0);
        endAngle = intent.getFloatExtra("EndValue", 0);
        incAngle = intent.getFloatExtra("IncValue", 1);
        stepTime = intent.getFloatExtra("UpdateTime", 10);

        return mMessenger.getBinder();
    }
}

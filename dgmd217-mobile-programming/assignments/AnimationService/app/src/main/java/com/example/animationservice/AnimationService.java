package com.example.animationservice;

import android.app.IntentService;
import android.content.Intent;
import android.content.Context;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;

public class AnimationService extends IntentService {

    public AnimationService() {
        super("AnimationService");
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        Messenger valMessenger = (Messenger) intent.getExtras().get("valueMessenger");

        float startAngle = intent.getFloatExtra("StartValue", 0);
        float endAngle = intent.getFloatExtra("EndValue", 0);
        float incAngle = intent.getFloatExtra("IncValue", 1);
        float stepTime = intent.getFloatExtra("UpdateTime", 10);

        while (startAngle < endAngle) {
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
    }
}

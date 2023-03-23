package com.example.simpledrawing;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

import java.util.ArrayList;

public class SingleTouchView extends View {
    Paint paint = new Paint();
    Path path = new Path();

    private final ArrayList<Paint> paints = new ArrayList<>();
    private final ArrayList<Path> paths = new ArrayList<>();

    public SingleTouchView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initPaint(Color.BLACK);
    }

    private void initPaint(int color) {
        paint.setAntiAlias(true);
        paint.setStrokeWidth(10.0f);
        paint.setColor(color);
        paint.setStyle(Paint.Style.STROKE);
        paint.setStrokeJoin(Paint.Join.ROUND);
    }

    public void setColor(int c) {
        if (paint.getColor() != c) {
            paint = new Paint();
            initPaint(c);
        }
    }

    public void clearPath() {
        path.reset();
        paths.clear();
        paints.clear();
        invalidate();
    }

    protected void onDraw(Canvas canvas) {
        canvas.drawPath(path, paint);
        for (int i = 0; i < paths.size() && i < paints.size(); i++) {
            canvas.drawPath(paths.get(i), paints.get(i));
        }
    }

    public boolean onTouchEvent(MotionEvent event) {
        float eventX = event.getX();
        float eventY = event.getY();

        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                path = new Path();
                path.moveTo(eventX, eventY);
                break;
            case MotionEvent.ACTION_MOVE:
                path.lineTo(eventX, eventY);
                break;
            case MotionEvent.ACTION_UP:
                paths.add(path);
                paints.add(paint);
                break;
            default:
                return false;
        }

        invalidate();
        return true;
    }
}
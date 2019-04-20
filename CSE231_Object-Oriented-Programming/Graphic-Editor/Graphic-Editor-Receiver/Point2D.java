import java.io.Serializable;

public class Point2D implements Serializable {
    private float mX, mY;

    public Point2D(float x, float y) {
        mX = x;
        mY = y;
    }

    public float getX() {
        return mX;
    }

    public float getY() {
        return mY;
    }

    public void setX(float x) {
        mX = x;
    }

    public void setY(float y) {
        mY = y;
    }
}

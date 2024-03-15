import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.util.ArrayList;

public class Cannon {

    private double posX;
    private double angle;

    private ArrayList<ChangeListener> listeners = new ArrayList<ChangeListener>();

    /**
     * Initializes the x coordinate of the bomb.
     *
     * @return Initial bomb x coordinate
     */
    private double initialBombX() {
        double rad = Math.toRadians(this.angle);
        return (70 * Math.cos(rad) + 30 + this.posX);
    }

    /**
     * Initializes the y coordinate of the bomb.
     *
     * @return Initial bomb y coordinate
     */
    private double initialBombY() {
        double rad = Math.toRadians(this.angle);
        return (70 * Math.sin(rad) + 15);
    }

    /**
     * Updates the cannon angle.
     *
     * @param inc Angle change
     */
    public void changeAngle(double inc) {
        if (this.angle + inc >= 0 && this.angle + inc <= 50) {
            this.angle += inc;

            for (ChangeListener l : this.listeners) {
                l.stateChanged(new ChangeEvent(this));
            }
        }
    }

    /**
     * Updates X position of the cannon.
     *
     * @param dx X position change
     */
    public void takeXStep(double dx) {
        this.posX += dx;

        for (ChangeListener l : this.listeners) {
            l.stateChanged(new ChangeEvent(this));
        }
    }

    /**
     * Launches a new bomb thread.
     *
     * @param b  Bomb object
     * @param tg Target object
     */
    public void fire(Bomb b, Target tg) {
        b.initialize(this.initialBombX(), this.initialBombY(), this.angle, tg);
        Thread t = new Thread(b);
        t.start();
    }

    /**
     * Adds a change listener to the list.
     *
     * @param l ChangeListener object
     */
    public void addChangeListener(ChangeListener l) {
        this.listeners.add(l);
    }

    /**
     * Get angle of the cannon.
     *
     * @return Cannon angle
     */
    public double getAngle() {
        return this.angle;
    }

    /**
     * Get X position of the cannon.
     *
     * @return Cannon X position
     */
    public double getX() {
        return this.posX;
    }

}

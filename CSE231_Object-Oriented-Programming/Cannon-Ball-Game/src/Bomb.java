import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.util.ArrayList;

public class Bomb implements Runnable {

    private double posX;
    private double posY;
    private double velX;
    private double velY;
    private double acc;
    private final int diameter = 20;

    private Target mTarget;
    private ArrayList<ChangeListener> listeners = new ArrayList<ChangeListener>();

    /**
     * Initializes the position of the bomb, the target
     * and angle of the cannon. It should be called at start().
     *
     * @param x0    Initial bomb x coordinate
     * @param y0    Initial bomb y coordinate
     * @param angle Initial cannon angle
     */
    public void initialize(double x0, double y0, double angle, Target t) {
        double rad = Math.toRadians(angle);

        this.posX = x0;
        this.posY = y0;

        this.velX = 70 * Math.cos(rad);
        this.velY = 70 * Math.sin(rad);
        this.acc = -9.8;

        this.mTarget = t;
    }

    /**
     * Updates the position and acceleration of the bomb.
     *
     * @param timestep Tick
     */
    private void moveOneStep(double timestep) {
        this.posX += this.velX * timestep;
        this.posY += this.velY * timestep;
        this.velY += this.acc * timestep;

        for (ChangeListener l : this.listeners) {
            l.stateChanged(new ChangeEvent(this));
        }
    }

    /**
     * Checks whether the bomb is invalid.
     *
     * @return Whether the bomb is invalid
     */
    public boolean isInvalid() {
        return this.posY < -15 || this.isHitTarget();
    }

    /**
     * Checks whether the bomb hits the target.
     *
     * @return Whether the bomb hits the target
     */
    public boolean isHitTarget() {
        return mTarget.isCollided(this);
    }

    /**
     * Runs the thread.
     */
    public void run() {
        final double TICK = 0.05;
        final int DELAY = 5;

        while (!this.isInvalid()) {
            this.moveOneStep(TICK);

            try {
                Thread.sleep(DELAY);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
    }

    /**
     * Adds a change listener to the list.
     *
     * @param c ChangeListener object
     */
    public void addChangeListener(ChangeListener c) {
        this.listeners.add(c);
    }

    /**
     * Get X position of the bomb.
     *
     * @return Bomb X position
     */
    public double getX() {
        return this.posX;
    }

    /**
     * Get Y position of the bomb.
     *
     * @return Bomb Y position
     */
    public double getY() {
        return this.posY;
    }

    /**
     * Get diameter of the bomb.
     *
     * @return Bomb diameter
     */
    public int getDiameter() {
        return this.diameter;
    }

}
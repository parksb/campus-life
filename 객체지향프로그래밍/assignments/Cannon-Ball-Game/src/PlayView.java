import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.util.ArrayList;

public class PlayView extends JPanel implements ChangeListener {

    private Cannon mCannon;
    private Target mTarget;
    private ArrayList<Bomb> mBombs;

    public PlayView() {
        this.mCannon = new Cannon();
        this.mTarget = new Target();
        this.mBombs = new ArrayList<Bomb>();
        this.mCannon.addChangeListener(this);
    }

    /**
     * Clears PlayView and set right-handed coordinate system.
     * It should be called when before draw the elements.
     *
     * @param g Graphics object
     */
    private void clearAndSetTransform(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        int w = this.getWidth();
        int h = this.getHeight();

        g2d.setColor(Color.white);
        g2d.fillRect(0, 0, w, h);
        g2d.translate(0, h);
        g2d.scale(1, -1);
        g2d.translate(0, 100);
    }

    /**
     * Draws a target.
     *
     * @param g Graphics object
     */
    private void drawTarget(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;

        g2d.setColor(Color.red);
        g2d.fillOval((int) mTarget.getX(), -15, mTarget.getDiameter(), mTarget.getDiameter());
    }

    /**
     * Draws a background.
     *
     * @param g Graphics object
     */
    private void drawBackground(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;

        g2d.setColor(Color.black);
        g2d.drawRect(0, -15, this.getWidth(), this.getHeight());
    }

    /**
     * Draws a cannon.
     *
     * @param g     Graphics object
     * @param angle Cannon angle
     * @param posX  Cannon x coordinate
     */
    private void drawCannon(Graphics g, double angle, double posX) {
        Graphics2D g2d = (Graphics2D) g;

        g2d.translate(posX, 0);
        g2d.rotate(Math.toRadians(angle), 30, 15);
        g2d.setColor(Color.blue);
        g2d.drawRect(0, 0, 100, 30);

        g2d.rotate(Math.toRadians(-angle), 30, 15);
        g2d.setColor(Color.white);
        g2d.fillOval(10, -15, 40, 40);
        g2d.setColor(Color.blue);
        g2d.drawOval(10, -15, 40, 40);

        g2d.translate(-posX, 0);
    }

    /**
     * Draws each bomb which is valid.
     * If the bomb is invalid, skips drawing and removes it from the list.
     *
     * @param g Graphics object
     */
    private void drawBombs(Graphics g) {
        int bombX;
        int bombY;

        g.setColor(Color.black);

        for (Bomb b : this.mBombs) {
            bombX = (int) b.getX();
            bombY = (int) b.getY();

            // Removes the exploded bombs.
            if (b.isInvalid()) {
                this.mBombs.remove(b);

                if (b.isHitTarget()) {
                    this.mTarget.resetX();
                }

                break;
            }

            g.fillOval(bombX, bombY, b.getDiameter(), b.getDiameter());
        }
    }

    /**
     * Adds a bomb to the list and applies a change listener.
     *
     * @param b Bomb object
     */
    public void addBomb(Bomb b) {
        b.addChangeListener(this);
        this.mBombs.add(b);
    }

    /**
     * Get the cannon object.
     *
     * @return Cannon object
     */
    public Cannon getCannon() {
        return this.mCannon;
    }

    /**
     * Get the target object.
     *
     * @return Target object
     */
    public Target getTarget() {
        return this.mTarget;
    }

    @Override
    public void paintComponent(Graphics g) {
        this.clearAndSetTransform(g);
        this.drawBackground(g);
        this.drawTarget(g);
        this.drawCannon(g, this.mCannon.getAngle(), this.mCannon.getX());

        if (this.mBombs.size() > 0) {
            this.drawBombs(g);
        }
    }

    @Override
    public void stateChanged(ChangeEvent e) {
        this.repaint();
    }

}

public class Target {

    private int diameter = 30;
    private double posX = 200;

    /**
     * Checks whether the target is hit by a bomb.
     * It calculates a distance between the target and bomb,
     * and makes result.
     *
     * @param bomb Bomb object
     * @return Whether the bomb is collided with a bomb
     */
    public boolean isCollided(Bomb bomb) {
        double tRadius = this.diameter / 2;
        double bRadius = bomb.getDiameter() / 2;

        double bcX = bomb.getX();
        double bcY = bomb.getY();
        double tcX = this.posX + tRadius;
        double tcY = -15.0;

        double dist = Math.sqrt(Math.pow((bcX - tcX), 2) + Math.pow((bcY - tcY), 2));

        return dist <= bRadius + tRadius;
    }

    /**
     * Sets new X position of the target.
     * The value is set to random. (200 ~ 400)
     */
    public void resetX() {
        this.posX = (int) (Math.random() * 400) + 200;
    }

    /**
     * Get X position of the target
     * @return Target X position
     */
    public double getX() {
        return this.posX;
    }

    /**
     * Get diameter of the target
     * @return Target diameter
     */
    public int getDiameter() {
        return this.diameter;
    }

}

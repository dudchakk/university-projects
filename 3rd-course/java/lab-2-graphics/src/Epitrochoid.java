import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Path2D;
import java.util.Random;

public class Epitrochoid extends JPanel {

  private static final double A = 3;
  private static final double a = 1;
  private static final double l = 2;
  private static final double SCALE_BASE = 50;
  private Color graphColor = Color.RED;
  private Stroke graphStroke = new BasicStroke(2);
  private final Random random = new Random();

  public Epitrochoid() {
    addMouseListener(new MouseAdapter() {
      @Override
      public void mouseClicked(MouseEvent e) {
        randomizeGraphStyle();
        repaint();
      }
    });
  }

  @Override
  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    Graphics2D g2d = (Graphics2D) g;
    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

    g2d.translate(getWidth() / 2, getHeight() / 2);
    drawAxes(g2d);
    g2d.setColor(graphColor);
    g2d.setStroke(graphStroke);

    Path2D.Double path = new Path2D.Double();
    double scale = Math.min(getWidth(), getHeight()) / SCALE_BASE;
    boolean firstPoint = true;

    for (double t = 0; t <= 10 * Math.PI; t += 0.01) {
      double x = (A + a) * Math.cos(t) - l * a * Math.cos(A / a + 1) * t;
      double y = (A + a) * Math.sin(t) - l * a * Math.sin(A / a + 1) * t;

      x *= scale;
      y *= scale;

      if (firstPoint) {
        path.moveTo(x, y);
        firstPoint = false;
      } else {
        path.lineTo(x, y);
      }
    }

    g2d.draw(path);
    g2d.setColor(Color.BLACK);
    g2d.setFont(new Font("Calibri", Font.ITALIC, 18)); 
    g2d.drawString("Dudchak - Variant 3", -getWidth() / 2 + 15, -getHeight() / 2 + 40);
  }

  private void drawAxes(Graphics2D g2d) {
    g2d.setColor(Color.BLACK);
    g2d.drawLine(-getWidth() / 2, 0, getWidth() / 2, 0);
    g2d.drawLine(0, -getHeight() / 2, 0, getHeight() / 2);
  }

  private void randomizeGraphStyle() {
    graphColor = new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256));

    float thickness = 1 + random.nextFloat() * 4;

    int style = random.nextInt(3);
    switch (style) {
      case 0:
        graphStroke = new BasicStroke(thickness);
        break;
      case 1:
        float[] dash = { 10f, 10f };
        graphStroke = new BasicStroke(
            thickness, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10f, dash, 0f);
        break;
      default:
        float[] dashDot = { 15f, 5f, 5f, 5f };
        graphStroke = new BasicStroke(
            thickness, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10f, dashDot, 0f);
        break;
    }
  }

  public static void main(String[] args) {
    JFrame frame = new JFrame("Epitrochoid graph");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(600, 600);
    frame.add(new Epitrochoid());
    frame.setVisible(true);
  }
}

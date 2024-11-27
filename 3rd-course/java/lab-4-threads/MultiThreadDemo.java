import javax.swing.*;
import java.awt.*;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MultiThreadDemo extends JFrame {
    private final AnimationPanel animationPanel;
    private final JTextArea computationArea;
    private final JLabel floatingTextLabel;

    private Thread animationThread, computationThread, floatingTextThread;

    private final Lock lock = new ReentrantLock();
    private final Condition animationCondition = lock.newCondition();
    private final Condition computationCondition = lock.newCondition();

    private volatile boolean isAnimationPaused = false;
    private volatile boolean isComputationPaused = false;
    private volatile boolean isFloatingTextRunning = true;

    public MultiThreadDemo() {
        setTitle("Multi-Thread Demo");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        animationPanel = new AnimationPanel();
        add(animationPanel, BorderLayout.CENTER);

        computationArea = new JTextArea(10, 30);
        computationArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(computationArea);
        add(scrollPane, BorderLayout.EAST);

        floatingTextLabel = new JLabel("Floating Text", SwingConstants.CENTER);
        floatingTextLabel.setFont(new Font("Arial", Font.BOLD, 18));
        add(floatingTextLabel, BorderLayout.SOUTH);

        JPanel controlPanel = new JPanel(new GridLayout(1, 3));
        controlPanel.add(createAnimationControlPanel());
        controlPanel.add(createComputationControlPanel());
        controlPanel.add(createFloatingTextControlPanel());
        add(controlPanel, BorderLayout.NORTH);
    }

    private JPanel createAnimationControlPanel() {
        JPanel panel = new JPanel(new GridLayout(3, 1));
        panel.setBorder(BorderFactory.createTitledBorder("Animation Controls"));

        JButton startButton = new JButton("Start Animation");
        JButton pauseButton = new JButton("Pause Animation");
        JButton resumeButton = new JButton("Resume Animation");

        startButton.addActionListener(e -> startAnimationThread());
        pauseButton.addActionListener(e -> pauseAnimationThread());
        resumeButton.addActionListener(e -> resumeAnimationThread());

        panel.add(startButton);
        panel.add(pauseButton);
        panel.add(resumeButton);

        return panel;
    }

    private JPanel createComputationControlPanel() {
        JPanel panel = new JPanel(new GridLayout(3, 1));
        panel.setBorder(BorderFactory.createTitledBorder("Computation Controls"));

        JButton startButton = new JButton("Start Computation");
        JButton pauseButton = new JButton("Pause Computation");
        JButton resumeButton = new JButton("Resume Computation");

        startButton.addActionListener(e -> startComputationThread());
        pauseButton.addActionListener(e -> pauseComputationThread());
        resumeButton.addActionListener(e -> resumeComputationThread());

        panel.add(startButton);
        panel.add(pauseButton);
        panel.add(resumeButton);

        return panel;
    }

    private JPanel createFloatingTextControlPanel() {
        JPanel panel = new JPanel(new GridLayout(3, 1));
        panel.setBorder(BorderFactory.createTitledBorder("Floating Text Controls"));

        JButton startButton = new JButton("Start Floating Text");
        JButton pauseButton = new JButton("Pause Floating Text");
        JButton resumeButton = new JButton("Resume Floating Text");

        startButton.addActionListener(e -> startFloatingTextThread());
        pauseButton.addActionListener(e -> pauseFloatingTextThread());
        resumeButton.addActionListener(e -> resumeFloatingTextThread());

        panel.add(startButton);
        panel.add(pauseButton);
        panel.add(resumeButton);

        return panel;
    }

    private void startAnimationThread() {
        if (animationThread == null || !animationThread.isAlive()) {
            animationThread = new Thread(() -> {
                try {
                    while (true) {
                        lock.lock();
                        try {
                            while (isAnimationPaused) {
                                animationCondition.await();
                            }
                            if (isAnimationPaused) break;
                            animationPanel.updateAnimation();
                        } finally {
                            lock.unlock();
                        }
                        Thread.sleep(50);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
            animationThread.setPriority(Thread.MIN_PRIORITY);
            animationThread.start();
        }
    }

    private void pauseAnimationThread() {
        lock.lock();
        try {
            isAnimationPaused = true;
        } finally {
            lock.unlock();
        }
    }

    private void resumeAnimationThread() {
        lock.lock();
        try {
            isAnimationPaused = false;
            animationCondition.signal();
        } finally {
            lock.unlock();
        }
    }

    private void startComputationThread() {
        if (computationThread == null || !computationThread.isAlive()) {
            computationThread = new Thread(() -> {
                try {
                    for (int i = 1; i <= 100; i++) {
                        lock.lock();
                        try {
                            while (isComputationPaused) {
                                computationCondition.await();
                            }
                            computationArea.append("Step " + i + ": " + (i * i) + "\n");
                        } finally {
                            lock.unlock();
                        }
                        Thread.sleep(100);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
            computationThread.setPriority(Thread.NORM_PRIORITY);
            computationThread.start();
        }
    }

    private void pauseComputationThread() {
        lock.lock();
        try {
            isComputationPaused = true;
        } finally {
            lock.unlock();
        }
    }

    private void resumeComputationThread() {
        lock.lock();
        try {
            isComputationPaused = false;
            computationCondition.signal();
        } finally {
            lock.unlock();
        }
    }

    private void startFloatingTextThread() {
        if (floatingTextThread == null || !floatingTextThread.isAlive()) {
            floatingTextThread = new Thread(() -> {
                try {
                    while (isFloatingTextRunning) {
                        String text = floatingTextLabel.getText();
                        floatingTextLabel.setText(text.substring(1) + text.charAt(0));
                        Thread.sleep(200);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
            floatingTextThread.setPriority(Thread.MAX_PRIORITY);
            floatingTextThread.start();
        }
    }

    private void pauseFloatingTextThread() {
        isFloatingTextRunning = false;
    }

    private void resumeFloatingTextThread() {
        isFloatingTextRunning = true;
        if (floatingTextThread == null || !floatingTextThread.isAlive()) {
            startFloatingTextThread();
        }
    }

    private class AnimationPanel extends JPanel {
        private int x = 0;

        public void updateAnimation() {
            x = (x + 5) % getWidth();
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.setColor(Color.BLUE);
            g.drawLine(0, getHeight() / 2, x, getHeight() / 2);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MultiThreadDemo frame = new MultiThreadDemo();
            frame.setVisible(true);
        });
    }
}

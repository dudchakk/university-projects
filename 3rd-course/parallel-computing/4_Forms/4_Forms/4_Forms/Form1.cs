using System;
using System.Collections.Generic;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace _4_Forms
{
    public partial class Form1 : Form
    {
        private List<Thread> threads;
        private List<ManualResetEvent> pauseEvents;
        private ManualResetEvent stopEvent = new ManualResetEvent(false);
        private List<bool> isRunning;

        public Form1()
        {
            InitializeComponent();

            buttonStart1.Click += new EventHandler(Start_1);
            buttonStop1.Click += new EventHandler(Stop_1);
            buttonStart2.Click += new EventHandler(Start_2);
            buttonStop2.Click += new EventHandler(Stop_2);
            buttonStart3.Click += new EventHandler(Start_3);
            buttonStop3.Click += new EventHandler(Stop_3);
            buttonStart4.Click += new EventHandler(Start_4);
            buttonStop4.Click += new EventHandler(Stop_4);

            threads = new List<Thread>();
            pauseEvents = new List<ManualResetEvent>
            {
                new ManualResetEvent(true),
                new ManualResetEvent(true),
                new ManualResetEvent(true),
                new ManualResetEvent(true)
            };
            isRunning = new List<bool>
            {
                true,
                true,
                true,
                true
            };
            buttonStart1.Enabled = false;
            buttonStart2.Enabled = false;
            buttonStart2.Enabled = false;
            buttonStart4.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            threads.Add(new Thread(Section_1Draw));
            threads.Add(new Thread(Section_2Draw));
            threads.Add(new Thread(Section_3Draw));
            threads.Add(new Thread(Section_4Draw));
            threads.ForEach(p => p.Start());
        }

        public void Section_1Draw()
        {
            Graphics g = panel1.CreateGraphics();
            var size = 50;
            var maxSize = 150;
            var minSize = 50;
            var increment = 5;
            var growing = true;

            while (!stopEvent.WaitOne(0))
            {
                pauseEvents[0].WaitOne();
                g.Clear(panel1.BackColor);

                var x = (panel1.Width - size) / 2;
                var y = (panel1.Height - size) / 2;

                g.FillRectangle(Brushes.Orange, x, y, size, size);

                if (growing)
                {
                    size += increment;
                    if (size >= maxSize)
                        growing = false;
                }
                else
                {
                    size -= increment;
                    if (size <= minSize)
                        growing = true;
                }

                Thread.Sleep(200);
            }
        }

        private void Start_1(object sender, EventArgs e)
        {
            if (!isRunning[0])
            {
                pauseEvents[0].Set();
                isRunning[0] = true;
            }
            buttonStop1.Enabled = true;
            buttonStart1.Enabled = false;
        }

        private void Stop_1(object sender, EventArgs e)
        {
            if (isRunning[0])
            {
                pauseEvents[0].Reset();
                isRunning[0] = false;
            }
            buttonStart1.Enabled = true;
            buttonStop1.Enabled = false;

        }

        public bool IsInScopes(ref double X, ref double Y, ref double dX, ref double dY, int radius, int width, int height)
        {
            if (X <= radius && dX < 0)
            {
                dX = -dX;
                X += dX;
                Y += dY;
                return false;
            }
            else if (X >= width - radius && dX > 0)
            {
                dX = -dX;
                X += dX;
                Y += dY;
                return false;
            }
            else if (Y <= radius && dY < 0)
            {
                dY = -dY;
                X += dX;
                Y += dY;
                return false;
            }
            else if (Y >= height - radius && dY > 0)
            {
                dY = -dY;
                X += dX;
                Y += dY;
                return false;
            }
            else
            {
                X += dX;
                Y += dY;
                return true;
            }
        }

        public void Section_2Draw()
        {
            Graphics g = panel2.CreateGraphics();
            Pen pen = new Pen(Color.Black, 2F);

            float x1 = 0, y1 = 0, x = 0;
            float y2;
            float yEx = 100;
            float eF = 25;

            g.Clear(panel2.BackColor);

            while (!stopEvent.WaitOne(0))
            {
                pauseEvents[1].WaitOne();
                y2 = (float)Math.Sin(x);
                g.DrawLine(pen, x1 * eF, y1 * eF + yEx, x * eF, y2 * eF + yEx);

                x1 = x;
                y1 = y2;
                x += 0.2f;

                if (x * eF >= 350)
                {
                    x = x1 = y1 = 0;
                    g.Clear(panel2.BackColor);
                }
                Thread.Sleep(10);
            }


        }

        private void Start_2(object sender, EventArgs e)
        {
            if (!isRunning[1])
            {
                pauseEvents[1].Set();
                isRunning[1] = true;
            }
            buttonStop2.Enabled = true;
            buttonStart2.Enabled = false;
        }

        private void Stop_2(object sender, EventArgs e)
        {
            if (isRunning[1])
            {
                pauseEvents[1].Reset();
                isRunning[1] = false;
            }
            buttonStart2.Enabled = true;
            buttonStop2.Enabled = false;
        }

        public void Section_3Draw()
        {
            Bitmap bitmap = new Bitmap(panel3.Width, panel3.Height);
            Graphics gImg = Graphics.FromImage(bitmap);
            Graphics graphics = panel3.CreateGraphics();
            PointF img = new PointF(0, 0);
            Random rand = new Random();

            double X, Y, dX, dY;
            int radius = 25;
            X = rand.Next(radius, panel3.Width - radius);
            Y = rand.Next(radius, panel3.Height - radius);
            dX = (rand.Next(1, 5)) * 0.1;
            dY = (rand.Next(1, 5)) * 0.1;

            while (!stopEvent.WaitOne(0))
            {
                pauseEvents[2].WaitOne();
                gImg.Clear(panel3.BackColor);
                gImg.FillEllipse(new SolidBrush(Color.Pink), (float)X - radius, (float)Y - radius, radius * 2, radius * 2);
                IsInScopes(ref X, ref Y, ref dX, ref dY, radius, panel3.Width, panel3.Height);
                graphics.DrawImage(bitmap, img);
            }
        }

        private void Start_3(object sender, EventArgs e)
        {
            if (!isRunning[2])
            {
                pauseEvents[2].Set();
                isRunning[2] = true;
            }
            buttonStop3.Enabled = true;
            buttonStart2.Enabled = false;
        }

        private void Stop_3(object sender, EventArgs e)
        {
            if (isRunning[2])
            {
                pauseEvents[2].Reset();
                isRunning[2] = false;
            }
            buttonStart2.Enabled = true;
            buttonStop3.Enabled = false;
        }

        public void Section_4Draw()
        {
            Graphics g = panel4.CreateGraphics();
            int sideLength = 100;
            float angle = 0;
            PointF center = new PointF(panel4.Width / 2, panel4.Height / 2);

            while (!stopEvent.WaitOne(0))
            {
                pauseEvents[3].WaitOne();
                g.Clear(panel4.BackColor);

                PointF[] triangle = GetRotatedTriangle(center, sideLength, angle);

                g.FillPolygon(Brushes.Black, triangle);

                angle += 2;
                if (angle >= 360)
                {
                    angle = 0;
                }

                Thread.Sleep(100);
            }
        }

        private PointF[] GetRotatedTriangle(PointF center, int sideLength, float angle)
        {
            float height = (float)(Math.Sqrt(3) / 2 * sideLength);

            PointF[] triangle = new PointF[3];
            triangle[0] = new PointF(center.X, center.Y - height / 2);
            triangle[1] = new PointF(center.X - sideLength / 2, center.Y + height / 2);
            triangle[2] = new PointF(center.X + sideLength / 2, center.Y + height / 2);

            for (int i = 0; i < 3; i++)
            {
                triangle[i] = RotatePoint(triangle[i], center, angle);
            }

            return triangle;
        }

        private PointF RotatePoint(PointF point, PointF center, float angle)
        {
            float radians = angle * (float)Math.PI / 180;

            float cos = (float)Math.Cos(radians);
            float sin = (float)Math.Sin(radians);

            float dx = point.X - center.X;
            float dy = point.Y - center.Y;

            float newX = center.X + (dx * cos - dy * sin);
            float newY = center.Y + (dx * sin + dy * cos);

            return new PointF(newX, newY);
        }

        private void Start_4(object sender, EventArgs e)
        {
            if (!isRunning[3])
            {
                pauseEvents[3].Set();
                isRunning[3] = true;
            }
            buttonStop4.Enabled = true;
            buttonStart4.Enabled = false;
        }

        private void Stop_4(object sender, EventArgs e)
        {
            if (isRunning[3])
            {
                pauseEvents[3].Reset();
                isRunning[3] = false;
            }
            buttonStart4.Enabled = true;
            buttonStop4.Enabled = false;
        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            stopEvent.Set();
            threads.ForEach(p => p.Join());
        }
    }
}

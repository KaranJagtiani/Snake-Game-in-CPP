// DDA Line Drawing Implementation

void dda(int x0, int y0, int x1, int y1, int color)
{
	int i;
	float x, y, dx, dy, steps;
	dx = (float)(x1 - x0);
	dy = (float)(y1 - y0);
	if ( abs(dx) >= abs(dy) )
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	dx = dx / steps;
	dy = dy / steps;

	x = x0;
	y = y0;
	i = 1;
	while (i <= steps)
	{
		putpixel(x, y, color);
		x += dx;
		y += dy;
		i = i + 1;
	}
}
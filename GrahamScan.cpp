// A C++ program to find convex hull of a set of points. Refer
// Time Complexity : O(nLogn)
#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point
{
	int x, y;
};

Point p0;

Point nextToTop(stack<Point> &S)
{
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

void swap(Point &p1, Point &p2)
{
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

int distSq(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // collinear
	return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
Point *p1 = (Point *)vp1;
Point *p2 = (Point *)vp2;

// Find orientation
int o = orientation(p0, *p1, *p2);
if (o == 0)
	return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{
// Find the bottommost point
int ymin = points[0].y, min = 0;
for (int i = 1; i < n; i++)
{
	int y = points[i].y;

	// Pick the bottom-most or choose the left
	// most point in case of tie
	if ((y < ymin) || (ymin == y &&
		points[i].x < points[min].x))
		ymin = points[i].y, min = i;
}

// Place the bottom-most point at first position
swap(points[0], points[min]);

p0 = points[0];
qsort(&points[1], n-1, sizeof(Point), compare);


int m = 1; 
for (int i=1; i<n; i++)
{
	while (i < n-1 && orientation(p0, points[i],
									points[i+1]) == 0)
		i++;
	points[m] = points[i];
	m++; 
}

if (m < 3) return;

stack<Point> S;
S.push(points[0]);
S.push(points[1]);
S.push(points[2]);

for (int i = 3; i < m; i++)
{
	while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
		S.pop();
	S.push(points[i]);
}

while (!S.empty())
{
	Point p = S.top();
	cout << "(" << p.x << ", " << p.y <<")" << endl;
	S.pop();
}
}

int main()
{
	Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
					{0, 0}, {1, 2}, {3, 1}, {3, 3}};
	int n = sizeof(points)/sizeof(points[0]);
	convexHull(points, n);
	return 0;
}

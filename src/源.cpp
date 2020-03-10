#include<iostream>
#include<math.h>
#include<vector>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

class dot {
public:
	double x;
	double y;

	dot(double x, double y);

	void dotinsert(dot d);
};

class line {
public:
	double a;
	double b;
	double c;
	line(int x1, int x2, int y1, int y2);

	line(double a, double b, double c);

	void lintersrctl(int _a, int _b, int _c);

	dot lintersrctl(line l);

	bool _lintersrctl(line l);

	void lineinsert(line l);
};

class cycle {
public:
	int x;
	int y;
	int r;

	cycle(int x, int y, int r);

	void cintersectl(line l);

	bool cintersectc(int x, int y, int r);

	void cycleinsert(cycle c);
};

vector<dot> dots;
vector<line> lines;
vector<cycle> cycles;

void solve();

using namespace std;

void line::lineinsert(line l) {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].a == l.a && lines[i].b == l.b && lines[i].c == l.c)
			return;
	}
	lines.push_back(l);
}

void cycle::cycleinsert(cycle c) {
	for (int i = 0; i < cycles.size(); i++) {
		if (cycles[i].x == c.x && cycles[i].y == c.y && cycles[i].r == c.r)
			return;
	}
	cycles.push_back(c);
}

dot::dot(double _x, double _y) {
	x = _x;
	y = _y;
}

void dot::dotinsert(dot d) {
	for (int i = 0; i < dots.size(); i++) {
		if (fabs(dots[i].x - d.x) < 0.00000001 && fabs(dots[i].y - d.y) < 0.00000001)
			//if (dots[i].x == d.x && dots[i].y == d.y)
			return;
	}
	dots.push_back(d);
}

cycle::cycle(int _x, int _y, int _r) {
	x = _x;
	y = _y;
	r = _r;
}

line::line(int x1, int x2, int y1, int y2) {
	if (x1 == x2) {
		b = 0.0;
		a = 1.0;
		c = (double)x1;
		return;
	}
	double t1 = (double)y2 - (double)y1;
	double t2 = (double)x1 - (double)x2;
	a = t1 / t2;
	b = 1.0;
	c = a * x1 + b * y1;
}

line::line(double a, double b, double c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

void line::lintersrctl(int _a, int _b, int _c) {
	if (b == 0 && _b == 0)
		return;
	if (b != 0 && _b != 0 && a / b == _a / _b)
		return;
	double t1 = (double)(this->a * _c - _a * this->c);
	double t2 = (double)(this->a * _b - _a * this->b);
	double t3 = (double)(_b * this->c - this->b * _c);
	double t4 = (double)(this->a * _b - _a * this->b);
	double x = t3 / t4;
	double y = t1 / t2;
	dot d = dot::dot(x, y);
	d.dotinsert(d);
}

bool line::_lintersrctl(line l) {
	if (b == 0 && l.b == 0)
		return false;
	if (b != 0 && l.b != 0 && a / b == l.a / l.b)
		return false;
	return true;
}

dot line::lintersrctl(line l) {
	double t1 = fabs(a * l.b - l.a * b);
	double t2 = fabs(c * l.b - b * l.c);
	double t3 = fabs(c * l.a - a * l.c);
	double x = t2 / t1;
	double y = t3 / t1;
	dot d = dot::dot(x, y);
	return d;
}

void cycle::cintersectl(line l) {
	double k = 1 / l.a;
	double c = -k * this->x + this->y;
	line _l = line(-k, 1.0, c);
	dot d = l.lintersrctl(_l);
	double dis = sqrt(pow((double)x - d.x, 2) + pow((double)y - d.y, 2));
	if (dis > r)
		return;
	if (dis == r) {
		d.dotinsert(d);
		return;
	}
	double n = sqrt(((double)this->r * (double)this->r) - dis * dis);
	double dx = n / sqrt(l.a * l.a + 1);
	double dy = sqrt(n * n - dx * dx);
	if (l.a > 0) dy = -dy;
	dot d1 = dot(d.x + dx, d.y + dy);
	dot d2 = dot(d.x - dx, d.y - dy);
	d1.dotinsert(d1);
	d2.dotinsert(d2);
}

bool cycle::cintersectc(int x, int y, int r) {
	double dis = sqrt(pow(((double)this->x - (double)x), 2) + pow(((double)this->y - (double)y), 2));
	if (dis > ((double)this->r + (double)r))
		return false;
	if (this->r > r && (dis + (double)r) < (double)this->r)
		return false;
	if (this->r < r && (dis + (double)this->r) < (double)r)
		return false;
	double a = ((double)this->x - (double)x) / ((double)this->y - (double)y);
	double c = ((double)(pow((double)this->r, 2) - pow((double)r, 2) - pow((double)this->x, 2) + pow((double)x, 2) - pow((double)this->y, 2) + pow((double)y, 2))) / (((double)y - (double)this->y) * 2);
	line l = line(a, 1.0, c);
	cintersectl(l);
	return true;
}

void solve() {
	for (int i = 0; i < lines.size(); i++) {
		line l = lines[i];
		for (int j = i + 1; j < lines.size(); j++) {
			l.lintersrctl(lines[j].a, lines[j].b, lines[j].c);
		}
	}
	for (int i = 0; i < cycles.size(); i++) {
		cycle c = cycles[i];
		for (int j = i + 1; j < cycles.size(); j++) {
			c.cintersectc(cycles[j].x, cycles[j].y, cycles[j].r);
		}
		for (int j = 0; j < lines.size(); j++) {
			c.cintersectl(lines[j]);
		}
	}
}

int main(int argc, char* argv[]) {
	int n;
	ifstream infile;
	infile.open(argv[2]);
	if (infile) {
		cout << "endless.txt open scessful" << endl;
		string str;
		int i = 0;
		while (getline(infile, str)) {
			if (i == 0) {
				n = 0;
				int j = 0;
				while (str[j] >= 48 && str[j] <= 57) {
					int temp = (int)(str[j] - 48);
					n = 10 * n + temp;
					j++;
				}
			}
			else if (i <= n) {
				char c = str[0];
				if (c == 'L') {
					int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
					int j = 2;
					int sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						x1 = 10 * x1 + temp;
						j++;
					}
					if (sym == 1) x1 = -x1;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						y1 = 10 * y1 + temp;
						j++;
					}
					if (sym == 1) y1 = -y1;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						x2 = 10 * x2 + temp;
						j++;
					}
					if (sym == 1) x2 = -x2;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						y2 = 10 * y2 + temp;
						j++;
					}
					if (sym == 1) y2 = -y2;
					line l = line(x1, x2, y1, y2);
					l.lineinsert(l);
				}
				else if (c == 'C') {
					int x = 0, y = 0, r = 0;
					int j = 2;
					int sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						x = 10 * x + temp;
						j++;
					}
					if (sym == 1) x = -x;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						y = 10 * y + temp;
						j++;
					}
					if (sym == 1) y = -y;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						r = 10 * r + temp;
						j++;
					}
					if (sym == 1) r = -r;
					cycle cy = cycle(x, y, r);
					cy.cycleinsert(cy);
				}
			}
			else break;
			i++;
		}//°´ÐÐÏÔÊ¾
		infile.close();
	}
	solve();
	ofstream outfile;
	outfile.open(argv[4]);
	outfile << dots.size();
	/*	for (int i = 0; i < dots.size(); i++) {
			cout << dots[i].x << " " << dots[i].y << endl;
		}*/
	cout << dots.size();
	return 0;
}
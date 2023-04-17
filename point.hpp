#ifndef POINT_HPP
#define POINT_HPP

#define UP 0, -1
#define DOWN 0, 1
#define LEFT -1, 0
#define RIGHT 1, 0

class Point {
  private:
    int _x;
    int _y;

  public:
    int X();
    void X(int);
    int Y();
    void Y(int);

    Point(int, int);
    Point();
    ~Point();

    void MvUp();
    void MvDown();
    void MvLeft();
    void MvRight();
    void Mv(int, int);
};

#endif

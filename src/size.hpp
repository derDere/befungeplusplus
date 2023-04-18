#ifndef SIZE_HPP
#define SIZE_HPP

class Size {
  private:
    int _width;
    int _height;

  public:
    int Width();
    void Width(int);
    int Height();
    void Height(int);

    Size(int, int);
    Size();
    ~Size();
};

#endif

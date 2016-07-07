#ifndef SQUARE_H
#define SQUARE_H

struct Square
{
  bool top, bottom, left, right;
  Square() : top(false), bottom(false), left(false), right(false) { }

  bool full_square() const { return top && bottom && left && right; }
};

#endif

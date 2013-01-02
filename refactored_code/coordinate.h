#ifndef _Coordinate_h
#define _Coordinate_h

class Coordinate {
    public:
        int x;
        int y;
        Coordinate(int x, int y) { this->x = x; this->y = y; }
        bool isXAt(int x) { return (this->x == x); }
        bool isYAt(int y) { return (this->y == y); }
        bool operator==(Coordinate aCoor) { return (aCoor.x == x && aCoor.y == y); }
        bool isAt(int x, int y) { return (this->x == x && this->y == y); }
};

#endif

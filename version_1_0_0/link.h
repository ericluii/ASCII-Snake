#ifndef __LINK_H__
#define __LINK_H__

class Link {
	public:
		Link(int x, int y, char direction);
		void moveLink(char direction);
		void changeDirection(char direction);
		bool operator==(const Link &link) const;
		Link &operator=(const Link &link);
		int getX() const;
		int getY() const;
		char getDirection() const;
		char getLastDirection() const;
	private:
		int x;
		int y;
		char direction;
		char lastDirection;
};

#endif

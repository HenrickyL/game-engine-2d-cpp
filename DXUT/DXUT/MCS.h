#ifndef _MCS_H
#define _MCS_H

//Solution (0,0,0)
struct MCS {
	//missionaries in origin side
	int missionaries = 0;
	//cannibals in origin side
	int cannibals = 0;
	bool boatOnRight = true;

	MCS(int _m, int _c) {
		missionaries = _m;
		cannibals = _c;
		boatOnRight = true;
	}
};
#endif
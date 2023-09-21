#ifndef DXUT_AI_SEARCH_BASE_H
#define DXUT_AI_SEARCH_BASE_H
//------------------------------------------
#include "Node.h"
#include "State.h"
//------------------------------------------

//------------------------------------------

class SearchBase {
private:
public:
	/**breadth - first search
	 * Use Queue to search result
	 *
	 */
	Node* Search(State* initial, State* final)
	{
		State* state = initial;
		Node* node = new Node();
	}
};
#endif
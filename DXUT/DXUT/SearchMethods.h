#ifndef DXUT_AI_SEARCH_METHODS_H
#define DXUT_AI_SEARCH_METHODS_H
//------------------------------------------
#include "INode.h"
#include "IState.h"
//------------------------------------------

//------------------------------------------

class SearchMethods {
private:
public:
	/**breadth - first search
	 * Use Queue to search result
	 *
	 */
	INode* BFS(IState* initial, IState* final)
	{
		IState* state = initial;
		INode* node = new INode();

	}
};
#endif
/*
 * Nodesets.h
 *
 *  Created on: Aug 18, 2018
 *      Author: saman
 */

#ifndef NODESETS_H_
#define NODESETS_H_

#include "Node.h"

namespace FSDE
{
class Nodesets {

public:

	Nodesets(vector<Node>, int);
    virtual ~Nodesets();
    int GetID();
    vector<Node> GetNodes();

private:

    int _ID;
    int _size;

    vector<Node> _nodes;

};

}


#endif /* NODESETS_H_ */

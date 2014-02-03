#include "lengthnode.h"

LengthNode::LengthNode()
{
	shortNode = 0;
	longNode = 0;
}


void LengthNode::razeTree()
{
	razeTree(this);
}

void LengthNode::razeTree(LengthNode *root)
{
	if(root->shortNode)
	{
		razeTree(root->shortNode);
	}
	if(root->longNode)
	{
		razeTree(root->longNode);
	}
	delete root;

}

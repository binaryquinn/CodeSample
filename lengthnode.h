#ifndef LENGTHNODE_H
#define LENGTHNODE_H

class LengthNode
{
public:
   LengthNode();

   LengthNode *shortNode;
   LengthNode *longNode;
   void razeTree();
 private:
   void razeTree(LengthNode *);

};

#endif // LENGTHNODE_H

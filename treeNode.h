#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

template <class T>
class TreeNode {
public:
  TreeNode() : left_(nullptr), right_(nullptr) {}
  TreeNode(T k) : left_(nullptr), right_(nullptr), key_(k) {}
  virtual ~TreeNode() {}
  // getters and setters
  T key() const { return key_; }
  TreeNode*  left() const { return left_; }
  TreeNode* right() const { return right_; }
  TreeNode*  setLeft(TreeNode* node) { left_ = node; }
  TreeNode* setRight(TreeNode* node) { right_ = node; }
private:
  T key_;
  TreeNode* left_;
  TreeNode* right_;
};

#endif

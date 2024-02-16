#include "btree.h"

void addValueToTree(Node *, Node *);
bool deleteNodes(Node *);
int findValue(Node *, int);
void deleteNode(Node *&, int);
//Node * findMinimum(Node *);
//Node * findMaximum(Node *);
//Node * findLowestLeft(Node *);
//Node * findLowestRight(Node *);
Node * findLowest(Node *);
void printItem(Node *);
int abs(int);

Tree::Tree() {
  root = nullptr;
  balanced = true;
}

Tree::~Tree() {
  std::cout << "root: " << root->value << '\n';
  deleteNodes(root);
}

void Tree::insert(int val) {
  Node * n = new Node;
  n->value = val;
  n->left = nullptr;
  n->right = nullptr;

  if (root == nullptr) {
    root = n;
  } else {
    addValueToTree(n, root);
  }


  balanced = false;
  while (!balanced) {
    balanced = true;
    calculateBalanceFactor(root);
    checkBalanceFactor(root, nullptr);
  }
}

void Tree::rightRotation(Node *& prev, Node * curr) {
  if (curr == root) {
    Node * temp{ curr->left };
    curr->left = temp->right;
    temp->right = curr;
    root = temp;
  } else {
    Node * temp{ curr->left };
    curr->left = curr->right;
    temp->right = curr;
    prev = temp;
  }
}

void Tree::leftRotation(Node *& prev, Node * curr) {
  if (curr == root) {
    Node * temp{ curr->right };
    curr->right = temp->left;
    temp->left = curr;
    root = temp;
  } else {
    Node * temp{ curr->right };
    curr->right = temp->left;
    temp->left = curr;
    prev = temp;
  }
}

void Tree::rightLeftRotation(Node *& prev, Node * curr) {
  if (curr == root) {
    Node * temp{ curr->right };
    Node * secondTemp{ curr->right->left };

    temp->left = secondTemp->right;
    curr->right = secondTemp;
    secondTemp->right = temp;

    curr->right = nullptr;
    secondTemp->left = curr;
    root = secondTemp;
  } else {
    Node * temp{ curr->right };
    Node * secondTemp{ curr->right->left };

    temp->left = secondTemp->right;
    curr->right = secondTemp;
    secondTemp->right = temp;

    curr->right = nullptr;
    secondTemp->left = curr;
    prev = secondTemp;
  }
}

void Tree::leftRightRotation(Node *& prev, Node * curr)  {
  if (curr == root) {
    Node * temp{ curr->left };
    Node * secondTemp{ curr->left->right };

    temp->right = secondTemp->left;
    secondTemp->left = temp;
    curr->left = secondTemp;

    curr->left = nullptr;
    secondTemp->right = curr;
    root = secondTemp;
  } else {
    Node * temp{ curr->left };
    Node * secondTemp{ curr->left->right };

    temp->right = secondTemp->left;
    secondTemp->left = temp;
    curr->left = secondTemp;

    curr->left = nullptr;
    secondTemp->right = curr;
    prev = secondTemp;
  }
}

void Tree::rebalance(Node * curr, Node * prev) {
  if (curr) {
    if (curr->bf > 1) { // right heavy
      if (abs(curr->bf) <= abs(curr->right->bf)) {
        rebalance(curr->right, curr);
      } else if (curr->right->bf >= 0) { // Balance factor signs match, left rotation
        if (curr == root) {
          leftRotation(curr, curr);
        } else {
          leftRotation(prev->right, curr);
        }
      } else if (curr->right->bf < 0) { // Balance factors mismatch, right left rotation
        if (curr == root) {
          rightLeftRotation(curr, curr);
        } else {
          rightLeftRotation(prev->right, curr);
        }
      }
    } else if (curr->bf < -1) { // left heavy
      if (abs(curr->bf) <= abs(curr->left->bf)) {
        rebalance(curr->left, curr);
      } else if (curr->left->bf < 0) { // Balance factors match, right rotation
        if (curr == root) {
          rightRotation(curr, curr);
        } else {
          rightRotation(prev->left, curr);
        }
      } else if (curr->left->bf >= 0) { // Balance factors mismatch, left right rotation
        if (curr == root) {
          leftRightRotation(curr, curr);
        } else {
          leftRightRotation(prev->left, curr);
        }
      }
    }
  }
}

void Tree::print() {
  printItem(root);
}

void printItem(Node * curr) {
  if (curr == nullptr) {
    return;
  } else {
    printItem(curr->left);
    std::cout << curr->value << " " << curr->bf << '\n';
    printItem(curr->right);
  }
}

int Tree::find(int val) {
  return findValue(root, val);
}

void Tree::del(int val) {
  std::cout << "Attempting to delete node with value: " << val << '\n';
  if (root != nullptr) {
    deleteNode(root, val);
  }

  balanced = false;
  while (!balanced) {
    balanced = true;
    calculateBalanceFactor(root);
    checkBalanceFactor(root, nullptr);
  }
}

void Tree::checkBalanceFactor(Node * curr, Node * prev) {
  if (curr) {
    if (curr == root) {
      if (curr->bf < -1 || curr->bf > 1) {
        balanced = false;
        rebalance(curr, nullptr);
      } else {
        checkBalanceFactor(curr->left, curr);
        checkBalanceFactor(curr->right, curr);
      }
    } else {
      if (curr->bf < -1 || curr->bf > 1) {
        balanced = false;
        rebalance(curr, prev);
      } else {
        checkBalanceFactor(curr->left, curr);
        checkBalanceFactor(curr->right, curr);
      }
    }
  }
}

int Tree::calculateHeight(Node * curr, int height) {
  if (curr) {
    height++;
    if (!curr->left && !curr->right) {
      return height;
    } else {
      int l{}, r{};

      if (curr->left) {
        l = calculateHeight(curr->left, height);
      }
      if (curr->right) {
        r = calculateHeight(curr->right, height);
      }

      return (l >= r) ? l : r;
    }
  }
  return height;
}

void Tree::calculateBalanceFactor(Node * curr) {
  if (curr) {
    curr->bf = calculateHeight(curr->right, 0) - calculateHeight(curr->left, 0);

    calculateBalanceFactor(curr->left);
    calculateBalanceFactor(curr->right);
  }
}

Node * findLowest(Node * curr) {
  if (curr->left) {
    findLowest(curr->left);
  } else {
    return curr;
  }
}

// third attempt at delete, from data structures class
void deleteNode(Node *& curr, int val) {
  if (curr) {
    if (val < curr->value && curr->left) {
      deleteNode(curr->left, val);
    } else if (val > curr->value && curr->right) {
      deleteNode(curr->right, val);
    } else {
      Node * temp{ nullptr };
      if (curr->left && curr->right) {
        temp = findLowest(curr->right);
        curr->value = temp->value;
        deleteNode(curr->right, val);
      } else {
        temp = curr;
        if (!curr->left) {
          curr = curr->right;
        } else if (!curr->right) {
          curr = curr->left;
        }
        delete temp;
        temp = nullptr;
      }
    }
  }
}

/* was used for second delete
Node * findMinimum(Node * curr) {
    if (curr->left != nullptr) {
        if (curr->left->left == nullptr) {
            Node * temp{ curr->left };
            curr->left = nullptr;
            return temp;
        } else {
            findMinimum(curr->left);
        }
    } else {
        return curr;
    }
}
 */

/*
Node * findMaximum(Node * curr) {
    if (curr->right != nullptr) {
      if (curr->right->right == nullptr) {
        Node * temp{ curr->right };
        curr->right = nullptr;
        return temp;
      } else {
        findMaximum(curr->right);
      }
    } else {
      return curr;
    }
}
 */

/* was used for second delete
Node * findLowestLeft(Node * curr) {
  if (curr->left == nullptr) {
    return curr;
  } else {
    findLowestLeft(curr->left);
  }
}
 */

/* was used for second delete
Node * findLowestRight(Node * curr) {
  if (curr->right == nullptr) {
    return curr;
  } else {
    findLowestRight(curr->right);
  }
}
 */

int findValue(Node * curr, int val) {
  if (val == curr->value) {
    return val;
  } else if (val < curr->value) {
    if (curr->left) {
      return findValue(curr->left, val);
    }
  } else {
    if (curr->right) {
      return findValue(curr->right, val);
    }
  }
  return -1;
}

void addValueToTree(Node * toAdd, Node * curr) {
  if (toAdd->value < curr->value) {
    if (curr->left == nullptr) {
      curr->left = toAdd;
    } else {
      addValueToTree(toAdd, curr->left);
    }
  } else {
    if (curr->right == nullptr) {
      curr->right = toAdd;
    } else {
      addValueToTree(toAdd, curr->right);
    }
  }
}

bool deleteNodes(Node * curr) {
  if (curr == nullptr) {
    return true;
  } else if (deleteNodes(curr->left) && deleteNodes(curr->right)) {
    //std::cout << curr->value << '\n';
    delete curr;
    curr = nullptr;
  }
  return true;
}

int abs(int num) {
  if (num < 0) {
    return num * -1;
  } else {
    return num;
  }
}

// second attempt below at AVL Tree balance

/*

void Tree::rebalance(Node * curr, Node * prev) {
  if (curr) {
    if (curr->bf > 1) {
      if (abs(curr->bf) <= abs(curr->right->bf)) {
        rebalance(curr->right, curr);
      }
      else if (curr->right->bf >= 0) { // Balance factor values are same sign, left rotation
        if (curr == root) {
          Node * temp{ curr->right };
          curr->right = nullptr;
          temp->left = curr;
          root = temp;
        } else {
          Node * temp{ curr->right };
          curr->right = nullptr;
          temp->left = curr;
          prev->right = temp;
        }
      } else { // Balance factor values mismatch, right left rotation
        if (curr == root) {
          Node * temp{ curr->right };
          Node * secondTemp{ curr->right->left };

          temp->left = nullptr;
          secondTemp->right = temp;
          curr->right = secondTemp;

          curr->right = nullptr;
          secondTemp->left = curr;
          root = secondTemp;
        } else {
          Node * temp{ curr->right };
          Node * secondTemp{ curr->right->left };

          temp->left = nullptr;
          secondTemp->right = temp;
          curr->right = secondTemp;

          curr->right = nullptr;
          secondTemp->left = curr;
          prev->right = secondTemp;
        }
      }
    }
    if (curr->bf < -1) {
      if (abs(curr->bf) <= abs(curr->left->bf)) {
        rebalance(curr->left, curr);
      } else if (curr->left->bf < 0) { // matching signs, right rotation
        if (curr == root) {
          Node * temp{curr->left};
          curr->left = nullptr;
          temp->right = curr;
          root = temp;
        } else {
          Node * temp{curr->left};
          curr->left = nullptr;
          temp->right = curr;
          prev->left = temp;
        }
      } else { // mismatched signs, left right rotation
        if (curr == root) {
          Node * temp{curr->left};
          Node * secondTemp{curr->left->right};
          curr->left = secondTemp;
          temp->right = nullptr;
          secondTemp->left = temp;

          secondTemp->right = curr;
          curr->left = nullptr;
          root = secondTemp;
        } else {
          Node * temp{curr->left};
          Node * secondTemp{curr->left->right};
          curr->left = secondTemp;
          temp->right = nullptr;
          secondTemp->left = temp;

          curr->left = nullptr;
          secondTemp->right = curr;
          prev->left = secondTemp;
        }
      }
    }
  }
}
*/

// first attempt below at AVL tree balance

/*
void Tree::rebalance(Node * curr, Node * prev) {
  if (curr) {
    if (curr->bf > 1) { // right heavy
      if (curr->right) {
        if (curr->right->bf >= 0) { // matching signs, L rot.
          if (curr == root) { // check if we are at root node
            Node * temp{curr->right};

            if (curr->right->left) {
              curr->right = curr->right->left;
              curr->right->left = nullptr;
            } else {
              curr->right = nullptr;
            }

            temp->left = curr;
            root = temp;
          } else {
            Node * temp{curr->right};

            if (curr->right->left) {
              curr->right = curr->right->left;
              curr->right->left = nullptr;
            } else {
              curr->right = nullptr;
            }

            prev->right = temp;
            temp->left = curr;
          }
        } else { // mismatch signs, RL rot.
          if (curr == root) {
            Node * temp{curr->right};
            Node * secondTemp{curr->right->left};

            if (curr->right->left->left) {
              curr->right = curr->right->left->left;
              curr->right->left->left = nullptr;
            } else {
              curr->right = nullptr;
            }

            temp->left = nullptr;

            if (secondTemp->right) {
              Node * lowestTempRight = findLowest(secondTemp->right);
              lowestTempRight->right = temp;
            } else {
              secondTemp->right = temp;
            }

            secondTemp->left = curr;
            root = secondTemp;
          } else {
            Node * temp{curr->right};
            Node * secondTemp{curr->right->left};

            if (curr->right->left->left) {
              curr->right = curr->right->left->left;
              curr->right->left->left = nullptr;
            } else {
              curr->right = nullptr;
            }

            temp->left = nullptr;

            if (secondTemp->right) {
              Node * lowestTempRight = findLowest(secondTemp->right);
              lowestTempRight->right = temp;
            } else {
              secondTemp->right = temp;
            }

            secondTemp->left = curr;
            prev->right = secondTemp;
          }
        }
      }
    } else if (curr->bf < -1) { // left heavy
      if (curr->left) {
        if (curr->left->bf <= 0) { // signs match, R rotation
          if (curr == root) {
            Node * temp{curr->left};

            if (curr->left->right) {
              curr->left = curr->left->right;
              curr->left->right = nullptr;
            } else {
              curr->left = nullptr;
            }

            temp->right = curr;
            root = temp;
          } else {
            Node * temp{curr->left};

            if (curr->left->right) {
              curr->left = curr->left->right;
              curr->left->right = nullptr;
            } else {
              curr->left = nullptr;
            }

            temp->right = curr;
            prev->left = temp;
          }
        } else { // signs don't match, LR rotation
          if (curr == root) {
            Node * temp{curr->left};
            Node * secondTemp{curr->left->right};

            if (curr->left->right->right) {
              curr->left = curr->left->right->right;
              curr->left->right->right = nullptr;
            } else {
              curr->left = nullptr;
            }

            temp->right = nullptr;
            secondTemp->left = temp;

            secondTemp->right = curr;
            root = secondTemp;
          } else {
            Node * temp{curr->left};
            Node * secondTemp{curr->left->right};

            if (curr->left->right->right) {
              curr->left = curr->left->right->right;
              curr->left->right->right = nullptr;
            } else {
              curr->left = nullptr;
            }

            temp->right = nullptr;
            secondTemp->left = temp;

            secondTemp->right = curr;
            prev->left = secondTemp;
          }
        }
      }
    }
  }
}
*/

/*
 *  second deleteNode attempt, not sure what I was thinking
 *
void deleteNode(Node * curr, int val) {
  if (curr) {
    if (val < curr->value) {
      if (curr->left != nullptr) {
        if (curr->left->value == val) {
          if (curr->left->left == nullptr && curr->left->right == nullptr) {
            // case 1 - no nodes
            noNodesDelete(curr, curr->left);
          } else if (curr->left->left != nullptr && curr->left->right != nullptr) {
            // case 3 - both nodes
            bothNodesDelete(curr, curr->left);
          } else {
            // case 2 - one node
            oneNodeDelete(curr, curr->left);
          }
        } else {
          deleteNode(curr->left, val);
        }
      }
    } else if (val > curr->value) {
      if (curr->right != nullptr) {
        if (curr->right->value == val) {
          if (curr->right->left == nullptr && curr->right->right == nullptr) {
            // case 1 - no nodes
            noNodesDelete(curr, curr->right);
          } else if (curr->right->left != nullptr && curr->right->right != nullptr) {
            // case 3 - both nodes
            bothNodesDelete(curr, curr->right);
          } else {
            // case 2 - one node
            oneNodeDelete(curr, curr->right);
          }
        } else {
          deleteNode(curr->right, val);
        }
      }
    }
  }
}
 */

/*
 *  second attempt at delete, what was I doing?, the case where there is one node is implemented incorrectly
 *
void noNodesDelete(Node * prev, Node * curr) {
  if (curr->value < prev->value) { // left side
    prev->left = nullptr;
    delete curr;
  } else { // right side
    prev->right = nullptr;
    delete curr;
  }
}

void oneNodeDelete(Node * prev, Node * curr) {
  if (curr->value < prev->value) { // left side
    if (curr->left) { // left node present
      prev->left = curr->left;
      curr->left = nullptr;
      delete curr;
    } else { // right node present - revise
      Node * temp {findMinimum(curr->right)};
      if (temp == curr->right) {
        curr->right = nullptr;
        prev->left = temp;
        delete curr;
      } else {
        if (temp->right == nullptr) {
          temp->right = curr->right;
          prev->left = temp;
          curr->right = nullptr;
          delete curr;
        } else {
          Node * secondTemp{findLowestRight(temp->right)};
          secondTemp->right = curr->right;
          curr->right = nullptr;
          prev->left = temp;
          delete curr;
        }
      }
    }
  } else { // right side
    if (curr->left) { // left node present
      Node * temp {findMaximum(curr->left)};
      if (temp == curr->left) {
        curr->left = nullptr;
        prev->right = temp;
        delete curr;
      } else {
        if (temp->left == nullptr) {
          prev->right = temp;
          prev->left = curr->left;
          curr->left = nullptr;
          delete curr;
        } else {
          Node * secondTemp{findLowestLeft(temp->left)};
          secondTemp->left = curr->left;
          curr->left = nullptr;
          prev->right = temp;
          delete curr;
        }
      }
    } else { // right node present
      prev->right = curr->right;
      curr->right = nullptr;
      delete curr;
    }
  }
}

void bothNodesDelete(Node * prev, Node * curr) {
  if (curr->value < prev->value) { // left side
    Node * temp{ findMinimum(curr->right) };
    if (temp == curr->right) {
      curr->right = nullptr;
      prev->left = temp;
      temp->left = curr->left;
      curr->left = nullptr;
      delete curr;
    } else {
      if (temp->right == nullptr) {
        temp->right = curr->right;
        temp->left = curr->left;
        curr->right = nullptr;
        curr->left = nullptr;
        prev->left = temp;
        delete curr;
      } else {
        Node * secondTemp{ findLowestRight(temp->right) };
        secondTemp->right = curr->right;
        temp->left = curr->left;
        curr->right = nullptr;
        curr->left = nullptr;
        prev->left = temp;
        delete curr;
      }
    }
  } else { // right side
    Node * temp{findMaximum(curr->left)};
    if (temp == curr->left) {
      curr->left = nullptr;
      temp->right = curr->right;
      curr->right = nullptr;
      prev->right = temp;
      delete curr;
    } else {
      if (temp->left == nullptr) {
        temp->left = curr->left;
        temp->right = curr->right;
        curr->left = nullptr;
        curr->right = nullptr;
        prev->right = temp;
        delete curr;
      } else {
        Node * secondTemp{ findLowestLeft(temp->left) };
        secondTemp->left = curr->left;
        temp->right = curr->right;
        curr->left = nullptr;
        curr->right = nullptr;
        prev->right = temp;
        delete curr;
      }
    }
  }
}

*/

/*
 *  first attempt, messed it up because there's a case where it would end up pointing back to itself
 *
void deleteNode(Node * curr, int val) {

 // 3 cases
 //  case 1: no children nodes
 //  case 2: 1 child node
 //  case 3: 2 child nodes

    if (val < curr->value) {
        if (curr->left != nullptr) {
            if (curr->left->value == val) {
                if (curr->left->left == nullptr && curr->left->right == nullptr) {
                    delete curr->left;
                    curr->left = nullptr;
                } else if (curr->left->left != nullptr && curr->left->right != nullptr) {
                    Node * temp{ findMinimum(curr->left->right) };
                    if (temp->right == nullptr) {
                        temp->left = curr->left->left; // this makes sense
                        temp->right = curr->left->right; // wat
                        delete curr->left;
                        curr->left = temp;
                    } else {
                        Node * lowestLevelTemp{ findLowest(temp) };
                        lowestLevelTemp->right = curr->left->right;
                        temp->left = curr->left->left;
                        delete curr->left;
                        curr->left = temp;
                    }
                } else {
                    Node * temp{ nullptr };
                    if (curr->left->left != nullptr) {
                        temp = curr->left->left;
                    } else {
                        temp = curr->left->right;
                    }
                    delete curr->left;
                    curr->left = temp;
                }
            } else {
                deleteNode(curr->left, val);
            }
        } else {
            std::cout << "Could not find node with value: " << val << '\n';
        }
    } else if (val > curr->value) {
        if (curr->right != nullptr) {
            if (curr->right->value == val) {
                if (curr->right->left == nullptr && curr->right->right == nullptr) {
                    delete curr->right;
                    curr->right = nullptr;
                } else if (curr->right->left != nullptr && curr->right->right != nullptr) {
                    Node * temp{ findMinimum(curr->right->right) };
                    if (temp->right == nullptr) {
                        temp->left = curr->right->left;
                        temp->right = curr->right->right;
                        delete curr->right;
                        curr->right = temp;
                    } else {
                        Node * lowestLevelTemp{ findLowest(temp) };
                        lowestLevelTemp->right = curr->right->right;
                        temp->left = curr->right->left;
                        delete curr->right;
                        curr->right = temp;
                    }
                } else {
                    Node * temp { nullptr };
                    if (curr->right->left != nullptr) {
                        temp = curr->right->left;
                    } else {
                        temp = curr->right->right;
                    }
                    delete curr->right;
                    curr->right = temp;
                }
            } else {
                deleteNode(curr->right, val);
            }
        } else {
            std::cout << "Could not find node with value: " << val << '\n';
        }
    }
}
*/
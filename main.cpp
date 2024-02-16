#include <iostream>
#include "btree.h"

int main() {
  {
    // Right rotation at root with additional node
    std::cout << "Right rotation at root with additional node\n";
    Tree t{};

    t.insert(10);
    t.insert(15);
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(1);
    t.del(5);
    t.print();
  }
  {
    std::cout << "Deleting test\n";
    Tree t{};

    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(3);

    t.del(15); // rebalance after this

    t.print();
  }
  {
    std::cout << "Complex deleting test\n";
    Tree t{};

    t.insert(15);
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(13);
    t.insert(25);
    t.insert(3);

    t.del(25); // rebalance after this

    t.print();
  }
  {
    std::cout << "Left rotation not at root\n";
    Tree t{};

    t.insert(10);
    t.insert(5);
    t.insert(20);
    t.insert(2);
    t.insert(6);
    t.insert(30);
    t.insert(40);
    t.insert(45);
    t.insert(41);

    t.print();
  }
  {
    // Left rotation at root
    std::cout << "Left rotation at root\n";
    Tree t{};
    t.insert(10);
    t.insert(15);
    t.insert(20);

    t.print();
  }
  {
    // Right Left Rotation at root
    std::cout << "Right left rotation at root\n";
    Tree t{};
    t.insert(10);
    t.insert(15);
    t.insert(13);

    t.print();
  }
  {
    // Left rotation, not at root
    std::cout << "Left rotation not at root\n";
    Tree t{};
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(20);
    t.insert(25);

    t.print();
  }
  {
    // Right Left rotation, not at root
    std::cout << "Right left rotation not at root\n";
    Tree t{};

    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(20);
    t.insert(17);

    t.print();
  }
  {
    // Right rotation at root
    std::cout << "Right rotation at root\n";
    Tree t{};

    t.insert(10);
    t.insert(8);
    t.insert(5);

    t.print();
  }
  {
    // Left right rotation at root
    std::cout << "Left right rotation at root\n";
    Tree t{};

    t.insert(10);
    t.insert(5);
    t.insert(8);

    t.print();
  }
  {
    // Left rotation not at root
    std::cout << "Left rotation not at root\n";
    Tree t{};

    t.insert(10);
    t.insert(12);
    t.insert(8);
    t.insert(5);
    t.insert(3);

    t.print();
  }
  {
    // Left right rotation not at root
    std::cout << "Left right rotation not at root\n";
    Tree t{};

    t.insert(10);
    t.insert(12);
    t.insert(5);
    t.insert(2);
    t.insert(4);

    t.print();
  }
  {
    std::cout << "Edge case where there is an extra node to be taken care of (13 in this case)\n";
    Tree t{};

    t.insert(20);
    t.insert(25);
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(13);

    t.print();
  }
}
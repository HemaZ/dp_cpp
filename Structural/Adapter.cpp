#include <iostream>
#include <string>
using namespace std;

class SpecialClass {
public:
  virtual string ReturnMagicNumber() { return "One"; }
};

// Assume we have a special library
// Which interface only supports a certain type of classes (SpecialClass)
void CoolLibrary(SpecialClass &input) {
  std::cout << "Cool Library Magic " << std::endl;
  std::cout << input.ReturnMagicNumber() << std::endl;
}

// But we also have OurClass which we want to use with the special library.
class OurClass {
public:
  int ReturnNumber() { return 1; }
};

// Then we create an Adapter class which inherit from SpecialClass

class AdapterClass : public SpecialClass {
  OurClass *ourclass;

public:
  AdapterClass() { ourclass = new OurClass; }
  ~AdapterClass() { delete ourclass; }
  string ReturnMagicNumber() override {
    return to_string(ourclass->ReturnNumber());
  }
};

int main(int argc, char const *argv[]) {
  AdapterClass adapter;
  CoolLibrary(adapter);
  return 0;
}

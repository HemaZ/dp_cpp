#include <iostream>
#include <memory>
#include <string>
class RobotBase {
private:
  std::string description;
  double cost;

public:
  virtual std::string getDescription() const = 0;
  virtual double getCost() const = 0;
  virtual ~RobotBase() {}
};

class FourWDRobot : public RobotBase {
public:
  virtual std::string getDescription() const {
    return "Four Wheeled Drive Robot ";
  }
  virtual double getCost() const { return 10.0; }
};

class TwoWDRobot : public RobotBase {
public:
  virtual std::string getDescription() const {
    return "two Wheeled Drive Robot with a castor wheel for balance ";
  }
  virtual double getCost() const { return 8.0; }
};

class CustomizedRobot : public RobotBase {
protected:
  std::shared_ptr<RobotBase> base;

public:
  CustomizedRobot(std::shared_ptr<RobotBase> &basePtr) : base(basePtr) {}
  virtual std::string getDescription() const = 0;
  virtual double getCost() const = 0;
};

class RobotWithLidar : public CustomizedRobot {
public:
  RobotWithLidar(std::shared_ptr<RobotBase> &basePtr)
      : CustomizedRobot(basePtr) {}
  virtual std::string getDescription() const override {
    return base->getDescription() + " Plus a Lidar";
  }
  virtual double getCost() const override { return base->getCost() + 10.0; }
};

class RobotWithCamera : public CustomizedRobot {
public:
  RobotWithCamera(std::shared_ptr<RobotBase> &basePtr)
      : CustomizedRobot(basePtr) {}
  virtual std::string getDescription() const override {
    return base->getDescription() + " Plus a Camera";
  }
  virtual double getCost() const override { return base->getCost() + 5.0; }
};

int main(int argc, char const *argv[]) {
  std::shared_ptr<RobotBase> customizedRobot;
  int c;
  std::cout << "==== Customize Your Robot ====" << std::endl;
  std::cout << "==== Enter 1 For 4WD or 2 For 2WD ====" << std::endl;

  std::cin >> c;
  if (c == 1) {
    customizedRobot = std::make_shared<FourWDRobot>();
  } else if (c == 2) {
    customizedRobot = std::make_shared<TwoWDRobot>();
  } else {
    std::cerr << "ERROR: Unknown Choice " << c << std::endl;
    exit(1);
  }

  std::cout << "==== Enter 1 To add a Lidar or any other key to skip ===="
            << std::endl;
  std::cin >> c;
  if (c == 1)
    customizedRobot = std::make_shared<RobotWithLidar>(customizedRobot);

  std::cout << "==== Enter 1 To add a Camera or any other key to skip ===="
            << std::endl;
  std::cin >> c;
  if (c == 1)
    customizedRobot = std::make_shared<RobotWithCamera>(customizedRobot);

  std::cout << customizedRobot->getDescription() << std::endl;
  std::cout << " Total Cost: " << customizedRobot->getCost() << std::endl;
}

#include <iostream>
#include <string>

// These classes represent the products
class CalibFile {
public:
  CalibFile(const std::string &filePath) {}
  virtual void GetData(const std::string &field) = 0;
};

class JsonFile : public CalibFile {
public:
  JsonFile(const std::string &filePath) : CalibFile(filePath) {}
  void GetData(const std::string &field) {
    std::cout << "Reading Cool Json Data from field" << field << std::endl;
  }
};

class YamlFile : public CalibFile {
public:
  YamlFile(const std::string &filePath) : CalibFile(filePath) {}
  void GetData(const std::string &field) {
    std::cout << "Reading Cool Yaml Data from field" << field << std::endl;
  }
};

// These classes represent the factory

class CalibFileParser {
protected:
  const std::string &filePath_;

public:
  CalibFileParser(const std::string &filePath) : filePath_(filePath) {}
  virtual CalibFile *CreateParser() const = 0;
  virtual void ParseData(const std::string &field) const {
    CalibFile *calibfile = CreateParser();
    calibfile->GetData(field);
  }
};

class JsonFileParser : public CalibFileParser {

public:
  JsonFileParser(const std::string &filePath) : CalibFileParser(filePath) {}
  CalibFile *CreateParser() const override { return new JsonFile(filePath_); }
};

class YamlFileParser : public CalibFileParser {
public:
  YamlFileParser(const std::string &filePath) : CalibFileParser(filePath) {}
  CalibFile *CreateParser() const override { return new YamlFile(filePath_); }
};

void CalibrationParsing(const CalibFileParser &parser) {
  parser.ParseData("field1");
}

int main(int argc, char const *argv[]) {
  JsonFileParser jsonfile("file.json");
  YamlFileParser yamlfile("file.yaml");
  CalibrationParsing(jsonfile);
  CalibrationParsing(yamlfile);

  return 0;
}

#include <ostream>
#include <string>

#ifndef CS2420_CUSTOMLIBRARIES_JSONWRITER_H_
#define CS2420_CUSTOMLIBRARIES_JSONWRITER_H_

namespace rose {

// Provides a user-friendly interface to write JSON data to a std::ostream.
class JsonWriter {
 public:
  explicit JsonWriter(std::ostream &out) : out_(out) {}

  // Writes an opening curly bracket.
  void BeginObject();
  // Begins an object property named `name`.
  void BeginObject(const std::string &name);
  // Writes an opening square bracket.
  void BeginArray();
  // Begins an array property named `name`.
  void BeginArray(const std::string &name);
  // Writes an int item with value `value`.
  void CreateInt(int value);
  // Writes an int property named `name` with value `value`.
  void CreateInt(const std::string &name, int value);
  // Writes a float item with value `value`.
  void CreateFloat(float value);
  // Writes a float property named `name` with value `value`.
  void CreateFloat(const std::string &name, float value);
  // Writes a double item with value `value`.
  void CreateDouble(double value);
  // Writes a double property named `name` with value `value`.
  void CreateDouble(const std::string &name, double value);
  // Writes a string item with value `value`.
  void CreateString(const std::string &value);
  // Writes a string property named `name` with value `value`.
  void CreateString(const std::string &name, const std::string &value);
  // Writes a bool item with value `value`.
  void CreateBool(bool value);
  // Writes a bool property named `name` with value `value`.
  void CreateBool(const std::string &name, bool value);
  // Writes a null item.
  void CreateNull();
  // Writes a null property named `name`.
  void CreateNull(const std::string &name);
  // Writes a closing curly bracket.
  void EndObject();
  // Writes a closing square bracket.
  void EndArray();

 private:
  // Begins a new level with the string `beginner`.
  void BeginLevel(const std::string &beginner);
  // Ends a level with the char `ender`.
  void EndLevel(char ender);
  // Writes an item with its value represented as a string.
  void CreateItem(const std::string &value);
  // Writes a property with its value represented as a string.
  void CreateProperty(const std::string &name, const std::string &value);
  // Inserts two spaces per level.
  void Indent();

  // The output stream being written to.
  std::ostream &out_;
  // The indentation level.
  int level_ = 0;
  bool level_empty_ = true;
};

}  // namespace rose

#include "custom_libraries/json_writer.cc"

#endif  // CS2420_CUSTOMLIBRARIES_JSONWRITER_H_

#include "json_writer.h"

#include <ostream>
#include <sstream>
#include <string>

namespace rose {

JsonWriter::JsonWriter(std::ostream &out) : out_(out) {
  level_ = 0;
  level_empty_ = true;
}

void JsonWriter::BeginObject() { BeginLevel("{"); }

void JsonWriter::BeginObject(const std::string &name) {
  std::stringstream beginner;
  beginner << '"' << name << "\": {";
  BeginLevel(beginner.str());
}

void JsonWriter::BeginArray() { BeginLevel("["); }

void JsonWriter::BeginArray(const std::string &name) {
  std::stringstream beginner;
  beginner << '"' << name << "\": [";
  BeginLevel(beginner.str());
}

void JsonWriter::CreateInt(int value) { CreateItem(std::to_string(value)); }

void JsonWriter::CreateInt(const std::string &name, int value) {
  CreateProperty(name, std::to_string(value));
}

void JsonWriter::CreateFloat(float value) { CreateItem(std::to_string(value)); }

void JsonWriter::CreateFloat(const std::string &name, float value) {
  CreateProperty(name, std::to_string(value));
}

void JsonWriter::CreateDouble(double value) {
  CreateItem(std::to_string(value));
}

void JsonWriter::CreateDouble(const std::string &name, double value) {
  CreateProperty(name, std::to_string(value));
}

void JsonWriter::CreateString(const std::string &value) {
  std::stringstream sout;
  sout << '"';
  for (char c : value) {
    if (c == '\0') break;
    if (c == '"') {
      sout << "\\\"";
    } else {
      sout << c;
    }
  }
  sout << '"';
  CreateItem(sout.str());
}

void JsonWriter::CreateString(const std::string &name,
                              const std::string &value) {
  std::stringstream sout;
  sout << '"';
  for (char c : value) {
    if (c == '\0') break;
    if (c == '"') {
      sout << "\\\"";
    } else {
      sout << c;
    }
  }
  sout << '"';
  CreateProperty(name, sout.str());
}

void JsonWriter::CreateBool(bool value) {
  CreateItem(value ? "true" : "false");
}

void JsonWriter::CreateBool(const std::string &name, bool value) {
  CreateProperty(name, value ? "true" : "false");
}

void JsonWriter::CreateNull() { CreateItem("null"); }

void JsonWriter::CreateNull(const std::string &name) {
  CreateProperty(name, "null");
}

void JsonWriter::EndObject() { EndLevel('}'); }

void JsonWriter::EndArray() { EndLevel(']'); }

void JsonWriter::BeginLevel(const std::string &beginner) {
  if (!level_empty_) out_ << ',';
  if (level_) out_ << '\n';  // Prevents writing a newline as the first char.
  Indent();
  out_ << beginner;
  ++level_;
  level_empty_ = true;
}

void JsonWriter::EndLevel(char ender) {
  --level_;
  if (!level_empty_) {
    out_ << '\n';
    Indent();
  }
  out_ << ender;
  level_empty_ = false;
}

void JsonWriter::CreateItem(const std::string &value) {
  if (!level_empty_) out_ << ',';
  out_ << '\n';
  Indent();
  out_ << value;
  level_empty_ = false;
}

void JsonWriter::CreateProperty(const std::string &name,
                                const std::string &value) {
  if (!level_empty_) out_ << ',';
  out_ << '\n';
  Indent();
  out_ << '"' << name << "\": " << value;
  level_empty_ = false;
}

void JsonWriter::Indent() { out_ << std::string((level_ << 1), ' '); }

}  // namespace rose

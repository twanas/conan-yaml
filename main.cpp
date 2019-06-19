#include "yaml-cpp/yaml.h"
#include <iostream>

struct Connection {
  std::string name;
  std::string type;
  std::string host1;

  friend std::ostream &operator<<(std::ostream &os,
                                  const Connection &connection) {
    os << connection.name << "[" << connection.type
       << "] : " << connection.host1;
    return os;
  }
};

namespace YAML {
template <> struct convert<Connection> {
  static Node encode(const Connection &rhs) {
    Node node;
    node["name"] = rhs.name;
    node["type"] = rhs.type;
    node["host1"] = rhs.host1;
    return node;
  }

  static bool decode(const Node &node, Connection &rhs) {
    if (!node.IsMap()) {
      return false;
    }

    rhs.name = node["name"].as<std::string>();
    rhs.type = node["type"].as<std::string>();
    rhs.host1 = node["host1"].as<std::string>();
    return true;
  }
};
} // namespace YAML

int main() {
  YAML::Node nodes = YAML::LoadFile("../../sample.yml");
  for (YAML::const_iterator it = nodes["connections"].begin();
       it != nodes["connections"].end(); ++it) {
    std::cout << it->as<Connection>() << '\n';
  }
}

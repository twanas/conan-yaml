# Build

```
$ git clone && cd conan-yaml
$ mkdir build && cd build
$ conan install ..
$ cmake -G "Ninja" ..
$ cmake --build . --config=Release
```

## Sample

The sample file contains a list of connections, each with a `name`, `type` and `host1` attribute. 

```
//sample.yml

connections:
  - name: "cme-ilink"
    type: "cme"
    host1: "xxx.xxx.xxx.xxx"
  - name: "tt-fix"
    type: "tt"
    host1: "xxx.xxx.xxx.xxx"
```

The sample iterates all items in the `connections` list, converting the list item to a `Connection` object:

```
struct Connection {
  std::string name;
  std::string type;
  std::string host1;
};


...

YAML::Node nodes = YAML::LoadFile("../../sample.yml");
for (YAML::const_iterator it = nodes["connections"].begin();
     it != nodes["connections"].end(); ++it) {
  auto conn = it->as<Connection>();
}
```

#ifndef GALAXY_INS_SNAPSHOT_H_
#define GALAXY_INS_SNAPSHOT_H_

#include "proto/ins_node.pb.h"

namespace galaxy {
namespace ins {

class InsNodeImpl;
class Meta;

class SnapshotManager {
public:
  SnapshotManager();
  bool AddSnapshot();
  bool LoadSnapshot();
private:
  bool DeleteSnapshot();

};

} // ins
} // galaxy

#endif // GALAXY_INS_SNAPSHOT_H_

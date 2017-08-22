#ifndef GALAXY_INS_SNAPSHOT_H_
#define GALAXY_INS_SNAPSHOT_H_

#include "leveldb/db.h"
#include "proto/ins_node.pb.h"

namespace galaxy {
namespace ins {

class InsNodeImpl;
class Meta;

class SnapshotManager {
public:
  SnapshotManager(const std::string& snapshot_dir);
  ~SnapshotManager();
  bool AddSnapshot();
  bool LoadSnapshot();
  bool GetSnapshotMeta(SnapshotMeta* meta);
  bool ApplySnapshot();
private:
  bool DeleteSnapshot();
private:
  leveldb::DB* db_;
  std::string snapshot_dir_;
};

} // ins
} // galaxy

#endif // GALAXY_INS_SNAPSHOT_H_

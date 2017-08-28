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
  bool CloseSnapshot();
  bool GetSnapshotMeta(SnapshotMeta* meta);
  bool ApplySnapshot();
  bool AddUserDataRecord(const std::string& key, const std::string& val);
  bool AddMetaDataRecord(const SnapshotMeta& meta);
  bool GetNextUserDataRecord(std::string* key, std::string* val);
  bool GetMetaDataRecord(std::string* val);
  //TODO merge with AddSnapshot
  bool DeleteSnapshot();
  const std::string& GetMetaDataPrefix();
  const std::string& GetUserDataPrefix();
private:
  leveldb::DB* db_;
  leveldb::Iterator* it_;
  std::string snapshot_dir_;
};

} // ins
} // galaxy

#endif // GALAXY_INS_SNAPSHOT_H_

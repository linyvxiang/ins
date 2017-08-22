#include "common/logging.h"
#include "snapshot.h"
#include "utils.h"

namespace galaxy {
namespace ins {

static const std::string kMetaPrefix = "#M";
static const std::string kDataPrefix = "#D";

SnapshotManager::SnapshotManager(const std::string& snapshot_dir) :
  db_(NULL),
  snapshot_dir_(snapshot_dir) { }

SnapshotManager::~SnapshotManager() {
  delete db_;
  db_ = NULL;
}

bool SnapshotManager::AddSnapshot() { return true; }

bool SnapshotManager::LoadSnapshot() { return true; }

bool SnapshotManager::DeleteSnapshot() { return true; }

bool SnapshotManager::GetSnapshotMeta(SnapshotMeta* meta) {
    bool ok = ins_common::Mkdirs(snapshot_dir_.c_str());
    if (!ok) {
        LOG(FATAL, "failed to create dir :%s", snapshot_dir_.c_str());
        abort();
    }
    leveldb::Options options;
    options.create_if_missing = false;
    leveldb::Status status = leveldb::DB::Open(options, snapshot_dir_, &db_);
    if (!status.ok()) {
      LOG(INFO, "don't have snapshot db in dir %s", snapshot_dir_.c_str());
      return false;
    }
    assert(db_);
    std::string meta_value;
    status = db_->Get(leveldb::ReadOptions(), kMetaPrefix, &meta_value);
    if (!status.ok()) {
      return false;
    }
    meta->ParseFromString(meta_value);
    return true;
}

bool SnapshotManager::ApplySnapshot() { return true; }


} // ins
} // galaxy

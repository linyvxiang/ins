#include "common/logging.h"
#include "snapshot.h"
#include "utils.h"

namespace galaxy {
namespace ins {

static const std::string kMetaPrefix = "#M";
static const std::string kDataPrefix = "#D";

SnapshotManager::SnapshotManager(const std::string& snapshot_dir) :
  db_(NULL),
  it_(NULL),
  snapshot_dir_(snapshot_dir) { }

SnapshotManager::~SnapshotManager() {
  delete db_;
  db_ = NULL;
}

bool SnapshotManager::AddSnapshot() {
  leveldb::Options options;
  options.create_if_missing = false;
  leveldb::Status status = leveldb::DB::Open(options, snapshot_dir_, &db_);
  if (!status.ok()) {
    LOG(WARNING, "create new snapshot in %s fail", snapshot_dir_.c_str());
    return false;
  }
  return true;
}

bool SnapshotManager::LoadSnapshot() { return true; }

bool SnapshotManager::CloseSnapshot() {
  if (db_) {
    delete db_;
    db_ = NULL;
  }
  return true;
}

bool SnapshotManager::DeleteSnapshot() {
  if (db_) {
    delete db_;
    db_ = NULL;
  }
  leveldb::Status status = leveldb::DestroyDB(snapshot_dir_, leveldb::Options());
  return status.ok();
}

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
  if (meta) {
    meta->ParseFromString(meta_value);
  }
  return true;
}

bool SnapshotManager::ApplySnapshot() { return true; }

bool SnapshotManager::AddUserDataRecord(const std::string& key, const std::string& val) {
  assert(db_);
  std::string snapshot_key = kDataPrefix + key;
  leveldb::Status s = db_->Put(leveldb::WriteOptions(), snapshot_key, val);
  return s.ok();
}

bool SnapshotManager::AddMetaDataRecord(const SnapshotMeta& meta) {
  assert(db_);
  std::string val;
  meta.SerializeToString(&val);
  leveldb::Status s = db_->Put(leveldb::WriteOptions(), kMetaPrefix, val);
  return s.ok();
}

bool SnapshotManager::GetNextUserDataRecord(std::string* key, std::string* val) {
  if (!it_) {
    it_ = db_->NewIterator(leveldb::ReadOptions());
    it_->Seek(kDataPrefix);
  }
  if (it_->Valid()) {
    leveldb::Slice slice = it_->key();
    *key = std::string(slice.data(), slice.size());
    slice = it_->value();
    *val = std::string(slice.data(), slice.size());
    it_->Next();
    return true;
  } else {
    delete it_;
    return false;
  }
}

bool SnapshotManager::GetMetaDataRecord(std::string* val) {
  leveldb::Status s = db_->Get(leveldb::ReadOptions(), kMetaPrefix, val);
  return s.ok();
}

} // ins
} // galaxy

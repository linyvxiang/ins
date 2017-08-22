#include "snapshot.h"

namespace galaxy {
namespace ins {

SnapshotManager::SnapshotManager(const std::string& snapshot_dir) :
  db_(NULL),
  snapshot_dir_(snapshot_dir) { }

bool SnapshotManager::AddSnapshot() { return true; }

bool SnapshotManager::LoadSnapshot() { return true; }

bool SnapshotManager::DeleteSnapshot() { return true; }

bool SnapshotManager::GetSnapshotMeta(SnapshotMeta* meta) { return true; }

bool SnapshotManager::ApplySnapshot() { return true; }


} // ins
} // galaxy

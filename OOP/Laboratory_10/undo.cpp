#include "undo.h"
#include "repository.h"
#include "domain.h"
#include <iostream>

// UndoAdd
UndoAdd::UndoAdd(Repository& repo, Travel_Package* undo_package)
    : undo_package(undo_package), repo(repo) {
}

void UndoAdd::doUndo() {
    repo.remove_from_repository_container(undo_package->get_id());
}

UndoAction* UndoAdd::clone() const {
    return new UndoAdd(repo, new Travel_Package(*undo_package));
}

UndoAdd::~UndoAdd() {
    delete undo_package;
}

// UndoRemove
UndoRemove::UndoRemove(Repository& repo, Travel_Package* undo_package)
    : undo_package(undo_package), repo(repo) {
}

void UndoRemove::doUndo() {
    repo.add_to_repository_container(new Travel_Package(*undo_package));
}

UndoAction* UndoRemove::clone() const {
    return new UndoRemove(repo, new Travel_Package(*undo_package));
}

UndoRemove::~UndoRemove() {
    delete undo_package;
}

// UndoUpdate
UndoUpdate::UndoUpdate(Repository& repo, Travel_Package* undo_package)
    :undo_package(undo_package), repo(repo) {
}

void UndoUpdate::doUndo() {
    repo.update_package_from_repository_container(
        undo_package->get_id(),
        undo_package->get_name(),
        undo_package->get_destination(),
        undo_package->get_type(),
        undo_package->get_price()
    );
}

UndoAction* UndoUpdate::clone() const {
    return new UndoUpdate(repo, new Travel_Package(*undo_package));
}

UndoUpdate::~UndoUpdate() {
    delete undo_package;
}

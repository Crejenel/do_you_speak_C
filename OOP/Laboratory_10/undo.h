#pragma once
#include <iostream>
class Repository;
class Travel_Package;
template <typename T>
class Inventory;

class UndoAction {
public:
    virtual void doUndo() = 0;

    virtual UndoAction* clone() const = 0;

    virtual ~UndoAction() {}
};

class UndoAdd : public UndoAction {
private:
    Travel_Package* undo_package;
    Repository& repo;

public:
    UndoAdd(Repository& repo, Travel_Package* undo_package);

    void doUndo() override;

    UndoAction* clone() const override;

    ~UndoAdd() override;
};

class UndoRemove : public UndoAction {
private:
    Travel_Package* undo_package;
    Repository& repo;

public:
    UndoRemove(Repository& repo, Travel_Package* undo_package);

    void doUndo() override;

    UndoAction* clone() const override;

    ~UndoRemove() override;
};

class UndoUpdate : public UndoAction {
private:
    Travel_Package* undo_package;
    Repository& repo;

public:
    UndoUpdate(Repository& repo, Travel_Package* undo_package);

    void doUndo() override;

    UndoAction* clone() const override;

    ~UndoUpdate() override;
};

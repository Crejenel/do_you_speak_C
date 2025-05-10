#pragma once
#include <iostream>
#include "container.h"
#include "domain.h"
#include "repository.h"


class UndoAction {

public :

	virtual void doUndo() = 0;
	virtual ~UndoAction() {}

};

class UndoAdd : public UndoAction {

private:

	Travel_Package* undo_package;
	Repository& repo;

public :

	UndoAdd(Repository& repo, Travel_Package* undo_package);

	void doUndo() override;

	~UndoAdd() override;

};

class UndoRemove : public UndoAction {

private :

	Travel_Package* undo_package;
	Repository& repo;

public:

	UndoRemove(Repository& repo, Travel_Package* undo_package);

	void doUndo() override;

	~UndoRemove() override;

};

class UndoUpdate : public UndoAction {


private:

	Travel_Package* undo_package;
	Repository& repo;

public:

	UndoUpdate(Repository& repo, Travel_Package* undo_package);

	void doUndo() override;

	~UndoUpdate() override;

};
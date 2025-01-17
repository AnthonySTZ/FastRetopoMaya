#pragma once

#include "MeshOperation.h"


class Retopo
{

public: 
	static MStatus RetopoMeshes();

private:

	static MStatus GetSelection(MSelectionList* selection);
	static MStatus GetMeshFromSelection(Mesh* mesh, MSelectionList selection, unsigned int index);

};
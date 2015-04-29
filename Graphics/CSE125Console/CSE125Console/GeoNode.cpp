#include "stdafx.h"
#include "GeoNode.h"


GeoNode::GeoNode()
{
	textureType = 0;
	damageStat = 0;
	healthStat = 0;
	speedStat = 0;
}


GeoNode::~GeoNode()
{
}

bool GeoNode::intersect(Vector3 pos) {
	return pos.equals(localTransform.position);
}
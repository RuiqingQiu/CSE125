#include "stdafx.h"
#include "GeoNode.h"


GeoNode::GeoNode()
{
	textureType = 0;
	damageStat = 0;
	healthStat = 0;
	speedStat = 0;

	clearConstraints();
}


GeoNode::~GeoNode()
{
}

bool GeoNode::intersect(Vector3 pos) {
	return pos.equals(localTransform.position);
}

void GeoNode::clearConstraints() {
	below_id = -1;
	left_id = -1;
	right_id = -1;
	front_id = -1;
	back_id = -1;
}

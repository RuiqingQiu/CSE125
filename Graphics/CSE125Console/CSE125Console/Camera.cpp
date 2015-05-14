#include "stdafx.h"
#include "Camera.h"
#include <math.h>
Camera::Camera()
{
	//localTransform = Transform();
	rotation = new Vector3(-30, 0, 0);
	IsFollowingEnabled = true;
}


Camera::~Camera()
{
}

void Camera::setUpCamera(){
	//this->drawLines();

	if (IsFollowingEnabled&&FollowingTarget != nullptr)
	{
		UpdateCamera();
		//printf("Euler Angle for camera:  %f %f %f\n", rotation->x, rotation->y, rotation->z);

	}
	else{
	}
	glRotatef(rotation->x, 1, 0, 0);
	glRotatef(rotation->y, 0, 1, 0);
	glRotatef(rotation->z, 0, 0, 1);
	glTranslatef(position->x, position->y, position->z);


	this->setCamDef(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));


	//this->setCamDef(Vector3(0,0,10), Vector3(0,0,0), Vector3(0,1,0));
	//this->drawNormals();
	//this->drawPlanes();
}


void  Camera::setUpCameraWithGL(float position_x, float position_y, float position_z, float lookAt_x, float lookAt_y, float lookAt_z){
	if (IsFollowingEnabled&&FollowingTarget != nullptr)
	{
		UpdateCamera();

	}
	else{
	}
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, width / height, 10, 40000);*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position_x, position_y, position_z, lookAt_x, lookAt_y, lookAt_z, 0, 1, 0);
}

void Camera::UpdateCamera()
{
	Matrix4 trans = FollowingTarget->localTransform.GetRotMatrix4();
	Vector4 forward = Vector4(0, 0, -1, 0);
	Vector4 direction_temp = trans*forward;
	Vector3 direction = Vector3(direction_temp.get_x(), direction_temp.get_y(), direction_temp.get_z());
	//direction.y = 0;
	direction.normalize();
	float distanceToPlayer = 10;
	Vector3* newposition = new Vector3(FollowingTarget->localTransform.position.x - direction.x*distanceToPlayer, FollowingTarget->localTransform.position.y - direction.y*distanceToPlayer + 3, FollowingTarget->localTransform.position.z - direction.z*distanceToPlayer);
	Vector3* newrotation = new Vector3(FollowingTarget->localTransform.rotation.x, FollowingTarget->localTransform.rotation.y, FollowingTarget->localTransform.rotation.z);//FollowingTarget->localTransform.rotation.z);

	this->position->negate();
	this->rotation->negate();

	*this->position = VectorLerp(position, newposition, 0.05, false);
	*this->rotation = VectorLerp(rotation, newrotation, 0.1, true);

	this->position->negate();
	this->rotation->negate();
	//newposition->negate();
	//newrotation->negate();
}


float mymode(float a, float b)
{
	float ret = fmod(a, b);
	if (ret < 0)
	{
		ret = -ret;
	}

	return ret;
}


Vector3 Camera::VectorLerp(Vector3* v1, Vector3* v2, float t, bool isangle)
{

	float v1x = fmod(v1->x, 360); //((int)v1->x) % 360;
	float v1y = fmod(v1->y, 360); //((int)v1->y) % 360;
	float v1z = fmod(v1->z, 360); //((int)v1->z) % 360;

	float v2x = fmod(v2->x, 360); //((int)v2->x) % 360;
	float v2y = fmod(v2->y, 360); //((int)v2->y) % 360;
	float v2z = fmod(v2->z, 360); //((int)v2->z) % 360;

	while (v1x < 0){
		v1x = v1x + 360;
	}
	while (v1x >= 360)
	{
		v1x = v1x - 360;
	}

	while (v1y < 0){
		v1y = v1y + 360;
	}
	while (v1y >= 360)
	{
		v1y = v1y - 360;
	}

	while (v1z < 0){
		v1z = v1z + 360;
	}
	while (v1z >= 360)
	{
		v1z = v1z - 360;
	}

	while (v2x < 0){
		v2x = v2x + 360;
	}
	while (v2x >= 360)
	{
		v2x = v2x - 360;
	}

	while (v2y < 0){
		v2y = v2y + 360;
	}
	while (v2y >= 360)
	{
		v2y = v2y - 360;
	}

	while (v2z < 0){
		v2z = v2z + 360;
	}
	while (v2z >= 360)
	{
		v2z = v2z - 360;
	}
	/*
	float v1x = fmod(v1->x, 1000); //((int)v1->x) % 360;
	float v1y = fmod(v1->y, 1000); //((int)v1->y) % 360;
	float v1z = fmod(v2->z, 1000); //((int)v1->z) % 360;
	float v2x = fmod(v2->x, 1000); //((int)v2->x) % 360;
	float v2y = fmod(v2->y, 1000); //((int)v2->y) % 360;
	float v2z = fmod(v2->z, 1000); //((int)v2->z) % 360;
	*/
	if (!isangle)
	{
		return Vector3(((1 - t)*v1->x + t*v2->x), ((1 - t)*v1->y + t*v2->y), ((1 - t)*v1->z + t*v2->z));
	}

	float retx, rety, retz;

	if (mymode(v2x - v1x, 360) < 180)
	{
		retx = ((1 - t)*v1x + t*v2x);
	}
	else{
		if (v2x>v1x){
			retx = ((1 - t)*(v1x + 360) + t*(v2x));

		}
		else{
			retx = ((1 - t)*v1x + t*(v2x + 360));

		}
	}


	if (mymode(v2y - v1y, 360) < 180)
	{
		rety = ((1 - t)*v1y + t*v2y);
	}
	else{
		if (v2y>v1y){
			rety = ((1 - t)*(v1y + 360) + t*(v2y));

		}
		else{
			rety = ((1 - t)*v1y + t*(v2y + 360));

		}
	}


	if (mymode(v2z - v1z, 360) < 180)
	{
		retz = ((1 - t)*v1z + t*v2z);

		//printf("camera: %f %f %f\n",v1z,v2z, retz);

	}
	else{
		if (v2z>v1z){
			retz = ((1 - t)*(v1z + 360) + t*(v2z));

		}
		else{
			retz = ((1 - t)*v1z + t*(v2z + 360));

		}
	}



	float rangeZero = 360;


	if (retx >= 0 && retx < 360)
	{
		retx = retx;
	}
	else{
		while (retx < 0){
			retx = retx + 360;
		}
		while (retx >= 360)
		{
			retx = retx - 360;
		}
	}

	if (rety >= 0 && rety < 360)
	{
		rety = rety;
	}
	else{
		while (rety < 0)
		{
			rety = rety + 360;
		}
		while (rety >= 360)
		{
			rety = rety - 360;
		}
	}

	if (retz >= 0 && retz < 360)
	{
		retz = retz;
	}
	else{
		while (retz < 0)
		{
			retz = retz + 360;
		}
		while (retz >= 360)
		{
			retz = retz - 360;
		}
	}


	return Vector3(retx, rety, retz);
}

#define ANG2RAD 3.14159265358979323846/180.0


void Camera::setCamInternals(float angle, float ratio, float nearD, float farD) {

	this->ratio = ratio;
	this->angle = angle;
	this->nearD = nearD;
	this->farD = farD;

	tang = (float)tan(angle* ANG2RAD * 0.5);
	nh = nearD * tang;
	nw = nh * ratio;
	fh = farD  * tang;
	fw = fh * ratio;


}


void Camera::setCamDef(Vector3 &p, Vector3 &l, Vector3 &u) {

	Vector3 dir, nc, fc, X, Y, Z;

	Z = p - l;
	Z.normalize();

	X = u.cross(u, Z);
	X.normalize();

	Y = Z.cross(Z, X);

	Vector3 Ztemp = Vector3(Z.x, Z.y, Z.z);
	Ztemp.scale(nearD);
	nc = p - Ztemp;

	Ztemp = Vector3(Z.x, Z.y, Z.z);
	Ztemp.scale(farD);
	fc = p - Ztemp;

	Vector3 Ytemp = Vector3(Y.x, Y.y, Y.z);
	Ytemp.scale(nh);
	Vector3 Xtemp = Vector3(X.x, X.y, X.z);
	Xtemp.scale(nw);

	ntl = nc + Ytemp - Xtemp;
	ntr = nc + Ytemp + Xtemp;
	nbl = nc - Ytemp - Xtemp;
	nbr = nc - Ytemp + Xtemp;

	Ytemp = Vector3(Y.x, Y.y, Y.z);
	Ytemp.scale(fh);
	Xtemp = Vector3(X.x, X.y, X.z);
	Xtemp.scale(fw);

	ftl = fc + Ytemp - Xtemp;
	ftr = fc + Ytemp + Xtemp;
	fbl = fc - Ytemp - Xtemp;
	fbr = fc - Ytemp + Xtemp;

	pl[TOP].set3Points(ntr, ntl, ftl);
	pl[BOTTOM].set3Points(nbl, nbr, fbr);
	pl[LEFT].set3Points(ntl, nbl, fbl);
	pl[RIGHT].set3Points(nbr, ntr, fbr);
	pl[NEARP].set3Points(ntl, ntr, nbr);
	pl[FARP].set3Points(ftr, ftl, fbl);
}


int Camera::pointInFrustum(Vector3 &p) {

	int result = INSIDE;
	for (int i = 0; i < 6; i++) {

		if (pl[i].distance(p) < 0)
			return OUTSIDE;
	}
	return(result);

}


int Camera::sphereInFrustum(Vector3 &p, float raio) {


	Matrix4 ret;
	ret.identity();
	Matrix4 m4_pos;
	m4_pos.identity();
	m4_pos.makeTranslate(position->x, position->y, position->z);
	Matrix4 m4_rotx;
	m4_rotx.makeRotateX(rotation->x);
	Matrix4 m4_roty;
	m4_roty.makeRotateY(rotation->y);
	Matrix4 m4_rotz;
	m4_rotz.makeRotateZ(rotation->z);
	Matrix4 m4_rot;
	m4_rot = m4_rotx*m4_roty*m4_rotz;
	ret = ret*m4_rot*m4_pos;
	Vector4 pos = ret*Vector4(p.x, p.y, p.z, 1);
	Vector3 posv3 = Vector3(pos.x, pos.y, pos.z);

	//printf("%f %f %f\n", posv3.x, posv3.y, posv3.z);
	int result = INSIDE;
	float distance;

	for (int i = 0; i < 6; i++) {
		distance = pl[i].distance(posv3);
		if (distance < -raio){
			//printf("out\n");
			return OUTSIDE;
		}
		else if (distance < raio){
			result = INTERSECT;
		}
		else{
		}
	}
	return(result);

}


int Camera::boxInFrustum(Vector3 &b) {
	/*
	int result = INSIDE;
	for (int i = 0; i < 6; i++) {

	if (pl[i].distance(b.getVertexP(pl[i].normal)) < 0)
	return OUTSIDE;
	else if (pl[i].distance(b.getVertexN(pl[i].normal)) < 0)
	result = INTERSECT;
	}
	return(result);
	*/
	return 1;
}





void Camera::drawPoints() {


	glBegin(GL_POINTS);

	glVertex3f(ntl.x, ntl.y, ntl.z);
	glVertex3f(ntr.x, ntr.y, ntr.z);
	glVertex3f(nbl.x, nbl.y, nbl.z);
	glVertex3f(nbr.x, nbr.y, nbr.z);

	glVertex3f(ftl.x, ftl.y, ftl.z);
	glVertex3f(ftr.x, ftr.y, ftr.z);
	glVertex3f(fbl.x, fbl.y, fbl.z);
	glVertex3f(fbr.x, fbr.y, fbr.z);

	glEnd();
}


void Camera::drawLines() {

	glBegin(GL_LINE_LOOP);
	//near plane
	glVertex3f(ntl.x, ntl.y, ntl.z);
	glVertex3f(ntr.x, ntr.y, ntr.z);
	glVertex3f(nbr.x, nbr.y, nbr.z);
	glVertex3f(nbl.x, nbl.y, nbl.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//far plane
	glVertex3f(ftr.x, ftr.y, ftr.z);
	glVertex3f(ftl.x, ftl.y, ftl.z);
	glVertex3f(fbl.x, fbl.y, fbl.z);
	glVertex3f(fbr.x, fbr.y, fbr.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//bottom plane
	glVertex3f(nbl.x, nbl.y, nbl.z);
	glVertex3f(nbr.x, nbr.y, nbr.z);
	glVertex3f(fbr.x, fbr.y, fbr.z);
	glVertex3f(fbl.x, fbl.y, fbl.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//top plane
	glVertex3f(ntr.x, ntr.y, ntr.z);
	glVertex3f(ntl.x, ntl.y, ntl.z);
	glVertex3f(ftl.x, ftl.y, ftl.z);
	glVertex3f(ftr.x, ftr.y, ftr.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//left plane
	glVertex3f(ntl.x, ntl.y, ntl.z);
	glVertex3f(nbl.x, nbl.y, nbl.z);
	glVertex3f(fbl.x, fbl.y, fbl.z);
	glVertex3f(ftl.x, ftl.y, ftl.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// right plane
	glVertex3f(nbr.x, nbr.y, nbr.z);
	glVertex3f(ntr.x, ntr.y, ntr.z);
	glVertex3f(ftr.x, ftr.y, ftr.z);
	glVertex3f(fbr.x, fbr.y, fbr.z);

	glEnd();
}


void Camera::drawPlanes() {

	glBegin(GL_QUADS);

	//near plane
	glVertex3f(ntl.x, ntl.y, ntl.z);
	glVertex3f(ntr.x, ntr.y, ntr.z);
	glVertex3f(nbr.x, nbr.y, nbr.z);
	glVertex3f(nbl.x, nbl.y, nbl.z);

	//far plane
	glVertex3f(ftr.x, ftr.y, ftr.z);
	glVertex3f(ftl.x, ftl.y, ftl.z);
	glVertex3f(fbl.x, fbl.y, fbl.z);
	glVertex3f(fbr.x, fbr.y, fbr.z);

	//bottom plane
	glVertex3f(nbl.x, nbl.y, nbl.z);
	glVertex3f(nbr.x, nbr.y, nbr.z);
	glVertex3f(fbr.x, fbr.y, fbr.z);
	glVertex3f(fbl.x, fbl.y, fbl.z);

	//top plane
	glVertex3f(ntr.x, ntr.y, ntr.z);
	glVertex3f(ntl.x, ntl.y, ntl.z);
	glVertex3f(ftl.x, ftl.y, ftl.z);
	glVertex3f(ftr.x, ftr.y, ftr.z);

	//left plane

	glVertex3f(ntl.x, ntl.y, ntl.z);
	glVertex3f(nbl.x, nbl.y, nbl.z);
	glVertex3f(fbl.x, fbl.y, fbl.z);
	glVertex3f(ftl.x, ftl.y, ftl.z);

	// right plane
	glVertex3f(nbr.x, nbr.y, nbr.z);
	glVertex3f(ntr.x, ntr.y, ntr.z);
	glVertex3f(ftr.x, ftr.y, ftr.z);
	glVertex3f(fbr.x, fbr.y, fbr.z);

	glEnd();

}

void Camera::drawNormals() {

	Vector3 a, b;

	glBegin(GL_LINES);

	// near
	a = (ntr + ntl + nbr + nbl);
	a.scale(0.25);
	b = a + pl[NEARP].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// far
	a = (ftr + ftl + fbr + fbl);
	a.scale(0.25);
	b = a + pl[FARP].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// left
	a = (ftl + fbl + nbl + ntl);
	a.scale(0.25);
	b = a + pl[LEFT].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// right
	a = (ftr + nbr + fbr + ntr);
	a.scale(0.25);
	b = a + pl[RIGHT].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// top
	a = (ftr + ftl + ntr + ntl);
	a.scale(0.25);
	b = a + pl[TOP].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// bottom
	a = (fbr + fbl + nbr + nbl);
	a.scale(0.25);
	b = a + pl[BOTTOM].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	glEnd();


}
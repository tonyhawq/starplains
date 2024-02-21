#include "BoundingBox.h"

#include <stdio.h>

OBB::OBB(maf::fvec2 pos, maf::fvec2 dim, float dir)
	: pos(pos), dim(dim), dir(dir)
{
	this->calculateCorners();
	this->radiusSqr = this->dim.x * this->dim.x + this->dim.y * this->dim.y;
}

void OBB::calculateCorners()
{
	float sine = sinf(this->dir);
	float cosine = cosf(this->dir);
	float halfWidth = this->dim.x / 2;
	float halfHeight = this->dim.y / 2;
	this->corners = {
		// top left
		{-halfWidth, -halfHeight},
		// top right
		{ halfWidth, -halfHeight},
		// bottom right
		{ halfWidth,  halfHeight},
		// bottom left
		{-halfWidth,  halfHeight},
	};
	this->corners.a = this->corners.a.rotate_c(sine, cosine) + this->pos;
	this->corners.b = this->corners.b.rotate_c(sine, cosine) + this->pos;
	this->corners.c = this->corners.c.rotate_c(sine, cosine) + this->pos;
	this->corners.d = this->corners.d.rotate_c(sine, cosine) + this->pos;
}

void OBB::move(maf::fvec2 vel)
{
	this->setPos(this->pos + vel);
}

void OBB::setPos(maf::fvec2 pos)
{
	this->pos = pos;
	this->calculateCorners();
}

void OBB::resize(maf::fvec2 dim)
{
	this->dim = dim;
	this->radiusSqr = this->dim.x * this->dim.x + this->dim.y * this->dim.y;
	this->calculateCorners();
}

void OBB::rotate(float rads)
{
	this->dir += rads;
	this->dir = fmodf(this->dir, maf::one_turn);
	this->calculateCorners();
}

void OBB::setDir(float rads)
{
	this->dir = rads;
	this->dir = fmodf(this->dir, maf::one_turn);
	this->calculateCorners();
}

/// <summary>
/// axis is a normalized vector b t dubs.
/// </summary>
/// <returns>the minimum and maximum bounds of projection (min: x, max:y)</returns>
inline OBB::minmax projectOnAxis(const OBB& box, maf::fvec2 axis)
{
	const maf::point4& corners = box.getCorners();
	float projection = corners.a.dot(axis);
	float min = projection;
	float max = projection;
	// do this once per corner (4 times)
	projection = corners.b.dot(axis);
	if (min > projection) { min = projection; }
	if (max < projection) { max = projection; }
	// do this once per corner (4 times)
	projection = corners.c.dot(axis);
	if (min > projection) { min = projection; }
	if (max < projection) { max = projection; }
	// do this once per corner (4 times)
	projection = corners.d.dot(axis);
	if (min > projection) { min = projection; }
	if (max < projection) { max = projection; }
	return { min, max };
}

const maf::point4& OBB::getCorners() const
{
	return this->corners;
}

maf::fvec2 OBB::topLeft() const
{
	return this->corners.a;
}

maf::fvec2 OBB::topRight() const
{
	return this->corners.b;
}

maf::fvec2 OBB::bottomLeft() const
{
	return this->corners.d;
}

maf::fvec2 OBB::bottomRight() const
{
	return this->corners.c;
}

bool OBB::_AABB(const OBB& other) const
{
	float hW = this->dim.x / 2;
	float hH = this->dim.y / 2;
	float bHW = other.dim.x / 2;
	float bHH = other.dim.y / 2;
	return {
		this->pos.x - hW < other.pos.x + other.dim.x / 2
		&&
		this->pos.x + this->dim.x / 2 > other.pos.x - bHW
		&&
		this->pos.y - hH < other.pos.y + other.dim.y / 2
		&&
		this->pos.y + this->dim.y / 2 > other.pos.y - bHH
	};
}

bool OBB::collides(const OBB& other) const
{
	float distSqr = this->pos.distSqr(other.pos);
	if (distSqr > this->radiusSqr && distSqr > other.radiusSqr)
	{
		return false;
	}
	// im just gonna copy the code eat my ass
	float calculatedSin = sinf(this->dir);
	float calculatedCos = cosf(this->dir);
	// clockwise starting at top
	maf::fvec2 faces[4] = {
		maf::fvec2{ 0,  -1},
		maf::fvec2{ 1,  0},
		maf::fvec2{ 0,  1},
		maf::fvec2{-1,  0}
	};
	for (const auto& face : faces)
	{
		maf::fvec2 normal = {
			calculatedSin * face.x - calculatedCos * face.y,
			calculatedCos * face.x + calculatedSin * face.y
		};
		OBB::minmax A = projectOnAxis(*this, normal);
		OBB::minmax B = projectOnAxis(other, normal);
		// min x max y
		if (!(A.min < B.max && A.max > B.min)) { return false; }
	}
	calculatedSin = sinf(other.dir);
	calculatedCos = cosf(other.dir);
	for (const auto& face : faces)
	{
		maf::fvec2 normal = {
			calculatedSin * face.x - calculatedCos * face.y,
			calculatedCos * face.x + calculatedSin * face.y
		};
		OBB::minmax A = projectOnAxis(*this, normal);
		OBB::minmax B = projectOnAxis(other, normal);
		// min x max y
		if (!(A.min < B.max && A.max > B.min)) { return false; }
	}
	return true;
}

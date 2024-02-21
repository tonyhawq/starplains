#pragma once

#include "../maf.h"

/// <summary>
/// a rotateable box
/// </summary>
class OBB
{
public:
	OBB(maf::fvec2 pos, maf::fvec2 dim, float dir);

	/// <summary>
	/// gets the positions of the corners (used for collision) (should cache this) (did cache this)
	/// </summary>
	/// <returns>this is 64 bytes so eat my reference boy</returns>
	const maf::point4& getCorners() const;

	maf::fvec2 topLeft() const;
	maf::fvec2 topRight() const;
	maf::fvec2 bottomLeft() const;
	maf::fvec2 bottomRight() const;

	inline maf::fvec2 getPos() const { return this->pos; }
	inline maf::fvec2 getDim() const { return this->dim; }
	inline float getDir() const { return this->dir; }
	
	void move(maf::fvec2 vel);
	void setPos(maf::fvec2 pos);
	void resize(maf::fvec2 dim);
	void rotate(float rads);
	void setDir(float rads);

	bool collides(const OBB& other) const;

	struct minmax
	{
		float min = 0;
		float max = 0;
	};
private:
	/// <summary>
	/// middle
	/// </summary>
	maf::fvec2 pos;
	/// <summary>
	/// width and height
	/// </summary>
	maf::fvec2 dim;
	/// <summary>
	/// make sure to update this !
	/// </summary>
	maf::point4 corners;
	/// <summary>
	/// radians
	/// </summary>
	float dir;
	/// <summary>
	/// radius of the bounding circle
	/// </summary>
	float radiusSqr;
	/// <summary>
	/// AABB collision for when the angles aren't an issue (faster :) )
	/// </summary>
	bool _AABB(const OBB& other) const;
	/// <summary>
	/// call this after moves, rotates etc.
	/// </summary>
	void calculateCorners();
};
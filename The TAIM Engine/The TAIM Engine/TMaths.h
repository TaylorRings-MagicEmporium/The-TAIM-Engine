#pragma once

struct TVec3 {
	TVec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float x, y, z;
};

struct TQuat {
	TQuat(float w, float x, float y, float z) {
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float w, x, y, z;
};

struct TMat4 {
	float value[4][4];
};
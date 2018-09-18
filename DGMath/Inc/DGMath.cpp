#include "DGMath_stdafx.h"
#include "DGMath.h"

using namespace DG::Math;

Vector2 const Vector2::Zero = { 0.f, 0.f };
Vector2 const Vector2::One = { 1.f, 1.f };
Vector2 const Vector2::UnitX = { 1.f, 0.f };
Vector2 const Vector2::UnitY = { 0.f, 1.f };

inline Vector2& Vector2::operator+=(Vector2 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(this), XMVectorAdd(v1, v2));
	return *this;
}

inline Vector2& Vector2::operator-=(Vector2 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(this), XMVectorSubtract(v1, v2));
	return *this;
}

inline Vector2& Vector2::operator*=(Vector2 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(this), XMVectorMultiply(v1, v2));
	return *this;
}

inline Vector2& Vector2::operator*=(float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(this), XMVectorScale(v, _s));
	return *this;
}

inline Vector2& Vector2::operator/=(Vector2 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(this), XMVectorDivide(v1, v2));
	return *this;
}

inline Vector2& Vector2::operator/=(float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(this), XMVectorScale(v, 1.f / _s));
	return *this;
}

inline bool Vector2::operator==(Vector2 const& _v) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	return XMVector2Equal(v1, v2);
}

inline bool Vector2::operator!=(Vector2 const& _v) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	return XMVector2NotEqual(v1, v2);
}

inline float Vector2::Distance(Vector2 const& _v1, Vector2 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	return XMVectorGetX(XMVector2Length(XMVectorSubtract(v2, v1)));
}

inline float Vector2::DistanceSquared(Vector2 const& _v1, Vector2 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	return XMVectorGetX(XMVector2LengthSq(XMVectorSubtract(v2, v1)));
}

inline void Vector2::Min(Vector2 const& _v1, Vector2 const& _v2, Vector2& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVectorMin(v1, v2));
}

inline Vector2 Vector2::Min(Vector2 const& _v1, Vector2 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorMin(v1, v2));
	return R;
}

inline void Vector2::Max(Vector2 const& _v1, Vector2 const& _v2, Vector2& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVectorMax(v1, v2));
}

inline Vector2 Vector2::Max(Vector2 const& _v1, Vector2 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorMax(v1, v2));
	return R;
}

inline void Vector2::Lerp(Vector2 const& _v1, Vector2 const& _v2, float _t, Vector2& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVectorLerp(v1, v2, _t));
}

inline Vector2 Vector2::Lerp(Vector2 const& _v1, Vector2 const& _v2, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorLerp(v1, v2, _t));
	return R;
}

inline void Vector2::SmoothStep(const Vector2& _v1, const Vector2& _v2, float _t, Vector2& _r)
{
	using namespace DirectX;
	_t = std::clamp(_t, 0.f, 1.f);
	_t = _t * _t * (3.f - 2.f * _t);
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVectorLerp(v1, v2, _t));
}

inline Vector2 Vector2::SmoothStep(Vector2 const& _v1, Vector2 const& _v2, float _t)
{
	using namespace DirectX;
	_t = std::clamp(_t, 0.f, 1.f);
	_t = _t * _t * (3.f - 2.f * _t);
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorLerp(v1, v2, _t));
	return R;
}

inline void Vector2::Barycentric(Vector2 const& _v1, Vector2 const& _v2, Vector2 const& _v3, float _f, float _g, Vector2& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v3));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVectorBaryCentric(v1, v2, v3, _f, _g));
}

inline Vector2 Vector2::Barycentric(Vector2 const& _v1, Vector2 const& _v2, Vector2 const& _v3, float _f, float _g)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v3));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorBaryCentric(v1, v2, v3, _f, _g));
	return R;
}

inline void Vector2::CatmullRom(Vector2 const& _v1, Vector2 const& _v2, Vector2 const& _v3, Vector2 const& _v4, float _t, Vector2& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v3));
	XMVECTOR v4 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v4));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVectorCatmullRom(v1, v2, v3, v4, _t));
}

inline Vector2 Vector2::CatmullRom(Vector2 const& _v1, Vector2 const& _v2, Vector2 const& _v3, Vector2 const& _v4, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v3));
	XMVECTOR v4 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v4));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorCatmullRom(v1, v2, v3, v4, _t));
	return R;
}

inline void Vector2::Hermite(Vector2 const& _v1, Vector2 const& _t1, Vector2 const& _v2, Vector2 const& _t2, float _t, Vector2& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_t1));
	XMVECTOR v3 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMVECTOR v4 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_t2));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVectorHermite(v1, v2, v3, v4, _t));
}

inline Vector2 Vector2::Hermite(Vector2 const& _v1, Vector2 const& _t1, Vector2 const& _v2, Vector2 const& _t2, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_t1));
	XMVECTOR v3 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	XMVECTOR v4 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_t2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorHermite(v1, v2, v3, v4, _t));
	return R;
}

inline void Vector2::Reflect(Vector2 const& _i, Vector2 const& _n, Vector2& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_n));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVector2Reflect(v1, v2));
}

inline Vector2 Vector2::Reflect(Vector2 const& _i, Vector2 const& _n)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_n));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVector2Reflect(v1, v2));
	return R;
}

inline void Vector2::Refract(Vector2 const& _i, Vector2 const& _n, float _refractive_index, Vector2& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_n));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVector2Refract(v1, v2, _refractive_index));
}

inline Vector2 Vector2::Refract(Vector2 const& _i, Vector2 const& _n, float _refractive_index)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_n));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVector2Refract(v1, v2, _refractive_index));
	return R;
}

inline bool Vector2::InBounds(Vector2 const& _bounds) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_bounds));
	return XMVector2InBounds(v1, v2);
}

inline float Vector2::Length() const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	return XMVectorGetX(XMVector2Length(v));
}

inline float Vector2::LengthSquared() const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	return XMVectorGetX(XMVector2LengthSq(v));
}

inline float Vector2::Dot(Vector2 const& _v1) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	return XMVectorGetX(XMVector2Dot(v1, v2));
}

inline void Vector2::Cross(Vector2 const& _v, Vector2& _r) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVector2Cross(v1, v2));
}

inline Vector2 Vector2::Cross(Vector2 const& _v) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVector2Cross(v1, v2));
	return R;
}

inline void Vector2::Normalize(Vector2& _r) const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVector2Normalize(v));
}

inline void Vector2::Normalize()
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(this), XMVector2Normalize(v));
}

inline void Vector2::Clamp(Vector2 const& _v_min, Vector2 const& _v_max, Vector2& _r) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v_min));
	XMVECTOR v3 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v_max));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&_r), XMVectorClamp(v1, v2, v3));
}

inline void Vector2::Clamp(Vector2 const& _v_min, Vector2 const& _v_max)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(this));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v_min));
	XMVECTOR v3 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v_max));
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(this), XMVectorClamp(v1, v2, v3));
}

inline Vector2 operator+(Vector2 const& _v1, Vector2 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorAdd(v1, v2));
	return R;
}

inline Vector2 operator-(Vector2 const& _v1, Vector2 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorSubtract(v1, v2));
	return R;
}

inline Vector2 operator*(Vector2 const& _v1, Vector2 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorMultiply(v1, v2));
	return R;
}

inline Vector2 operator*(Vector2 const& _v, float _s)
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorScale(v, _s));
	return R;
}

inline Vector2 operator/(Vector2 const& _v1, Vector2 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v2));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorAdd(v1, v2));
	return R;
}

inline Vector2 operator/(Vector2 const& _v, float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat2(reinterpret_cast<XMFLOAT2 const*>(&_v));
	Vector2 R{};
	XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&R), XMVectorScale(v, 1.f / _s));
	return R;
}

Vector3 const Vector3::Zero = { 0.f, 0.f, 0.f };
Vector3 const Vector3::One = { 1.f, 1.f, 1.f };
Vector3 const Vector3::UnitX = { 1.f, 0.f, 0.f };
Vector3 const Vector3::UnitY = { 0.f, 1.f, 0.f };
Vector3 const Vector3::UnitZ = { 0.f, 0.f, 1.f };
Vector3 const Vector3::Up = { 0.f, 1.f, 0.f };
Vector3 const Vector3::Down = { 0.f, -1.f, 0.f };
Vector3 const Vector3::Right = { 1.f, 0.f, 0.f };
Vector3 const Vector3::Left = { -1.f, 0.f, 0.f };
Vector3 const Vector3::Forward = { 0.f, 0.f, -1.f };
Vector3 const Vector3::Backward = { 0.f, 0.f, 1.f };

inline Vector3& Vector3::operator+=(Vector3 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(this), XMVectorAdd(v1, v2));
	return *this;
}

inline Vector3& Vector3::operator-=(Vector3 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(this), XMVectorSubtract(v1, v2));
	return *this;
}

inline Vector3& Vector3::operator*=(Vector3 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(this), XMVectorMultiply(v1, v2));
	return *this;
}

inline Vector3& Vector3::operator*=(float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(this), XMVectorScale(v, _s));
	return *this;
}

inline Vector3& Vector3::operator/=(Vector3 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(this), XMVectorDivide(v1, v2));
	return *this;
}

inline Vector3& Vector3::operator/=(float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(this), XMVectorScale(v, 1.f / _s));
	return *this;
}

inline bool Vector3::operator==(Vector3 const& _v) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	return XMVector3Equal(v1, v2);
}

inline bool Vector3::operator!=(Vector3 const& _v) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	return XMVector3NotEqual(v1, v2);
}

inline float Vector3::Distance(Vector3 const& _v1, Vector3 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	return XMVectorGetX(XMVector3Length(XMVectorSubtract(v2, v1)));
}

inline float Vector3::DistanceSquared(Vector3 const& _v1, Vector3 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	return XMVectorGetX(XMVector3LengthSq(XMVectorSubtract(v2, v1)));
}

inline void Vector3::Min(Vector3 const& _v1, Vector3 const& _v2, Vector3& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVectorMin(v1, v2));
}

inline Vector3 Vector3::Min(Vector3 const& _v1, Vector3 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorMin(v1, v2));
	return R;
}

inline void Vector3::Max(Vector3 const& _v1, Vector3 const& _v2, Vector3& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVectorMax(v1, v2));
}

inline Vector3 Vector3::Max(Vector3 const& _v1, Vector3 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorMax(v1, v2));
	return R;
}

inline void Vector3::Lerp(Vector3 const& _v1, Vector3 const& _v2, float _t, Vector3& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVectorLerp(v1, v2, _t));
}

inline Vector3 Vector3::Lerp(Vector3 const& _v1, Vector3 const& _v2, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorLerp(v1, v2, _t));
	return R;
}

inline void Vector3::SmoothStep(const Vector3& _v1, const Vector3& _v2, float _t, Vector3& _r)
{
	using namespace DirectX;
	_t = std::clamp(_t, 0.f, 1.f);
	_t = _t * _t * (3.f - 2.f * _t);
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVectorLerp(v1, v2, _t));
}

inline Vector3 Vector3::SmoothStep(Vector3 const& _v1, Vector3 const& _v2, float _t)
{
	using namespace DirectX;
	_t = std::clamp(_t, 0.f, 1.f);
	_t = _t * _t * (3.f - 2.f * _t);
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorLerp(v1, v2, _t));
	return R;
}

inline void Vector3::Barycentric(Vector3 const& _v1, Vector3 const& _v2, Vector3 const& _v3, float _f, float _g, Vector3& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v3));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVectorBaryCentric(v1, v2, v3, _f, _g));
}

inline Vector3 Vector3::Barycentric(Vector3 const& _v1, Vector3 const& _v2, Vector3 const& _v3, float _f, float _g)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v3));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorBaryCentric(v1, v2, v3, _f, _g));
	return R;
}

inline void Vector3::CatmullRom(Vector3 const& _v1, Vector3 const& _v2, Vector3 const& _v3, Vector3 const& _v4, float _t, Vector3& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v3));
	XMVECTOR v4 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v4));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVectorCatmullRom(v1, v2, v3, v4, _t));
}

inline Vector3 Vector3::CatmullRom(Vector3 const& _v1, Vector3 const& _v2, Vector3 const& _v3, Vector3 const& _v4, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v3));
	XMVECTOR v4 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v4));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorCatmullRom(v1, v2, v3, v4, _t));
	return R;
}

inline void Vector3::Hermite(Vector3 const& _v1, Vector3 const& _t1, Vector3 const& _v2, Vector3 const& _t2, float _t, Vector3& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_t1));
	XMVECTOR v3 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMVECTOR v4 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_t2));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVectorHermite(v1, v2, v3, v4, _t));
}

inline Vector3 Vector3::Hermite(Vector3 const& _v1, Vector3 const& _t1, Vector3 const& _v2, Vector3 const& _t2, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_t1));
	XMVECTOR v3 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	XMVECTOR v4 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_t2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorHermite(v1, v2, v3, v4, _t));
	return R;
}

inline void Vector3::Reflect(Vector3 const& _i, Vector3 const& _n, Vector3& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_n));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVector3Reflect(v1, v2));
}

inline Vector3 Vector3::Reflect(Vector3 const& _i, Vector3 const& _n)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_n));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVector3Reflect(v1, v2));
	return R;
}

inline void Vector3::Refract(Vector3 const& _i, Vector3 const& _n, float _refractive_index, Vector3& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_n));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVector3Refract(v1, v2, _refractive_index));
}

inline Vector3 Vector3::Refract(Vector3 const& _i, Vector3 const& _n, float _refractive_index)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_n));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVector3Refract(v1, v2, _refractive_index));
	return R;
}

inline bool Vector3::InBounds(Vector3 const& _bounds) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_bounds));
	return XMVector3InBounds(v1, v2);
}

inline float Vector3::Length() const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	return XMVectorGetX(XMVector3Length(v));
}

inline float Vector3::LengthSquared() const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	return XMVectorGetX(XMVector3LengthSq(v));
}

inline float Vector3::Dot(Vector3 const& _v1) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	return XMVectorGetX(XMVector3Dot(v1, v2));
}

inline void Vector3::Cross(Vector3 const& _v, Vector3& _r) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVector3Cross(v1, v2));
}

inline Vector3 Vector3::Cross(Vector3 const& _v) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVector3Cross(v1, v2));
	return R;
}

inline void Vector3::Normalize(Vector3& _r) const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVector3Normalize(v));
}

inline void Vector3::Normalize()
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(this), XMVector3Normalize(v));
}

inline void Vector3::Clamp(Vector3 const& _v_min, Vector3 const& _v_max, Vector3& _r) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v_min));
	XMVECTOR v3 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v_max));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&_r), XMVectorClamp(v1, v2, v3));
}

inline void Vector3::Clamp(Vector3 const& _v_min, Vector3 const& _v_max)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(this));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v_min));
	XMVECTOR v3 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v_max));
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(this), XMVectorClamp(v1, v2, v3));
}

inline Vector3 operator+(Vector3 const& _v1, Vector3 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorAdd(v1, v2));
	return R;
}

inline Vector3 operator-(Vector3 const& _v1, Vector3 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorSubtract(v1, v2));
	return R;
}

inline Vector3 operator*(Vector3 const& _v1, Vector3 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorMultiply(v1, v2));
	return R;
}

inline Vector3 operator*(Vector3 const& _v, float _s)
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorScale(v, _s));
	return R;
}

inline Vector3 operator/(Vector3 const& _v1, Vector3 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v2));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorDivide(v1, v2));
	return R;
}

inline Vector3 operator/(Vector3 const& _v, float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat3(reinterpret_cast<XMFLOAT3 const*>(&_v));
	Vector3 R{};
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R), XMVectorScale(v, 1.f / _s));
	return R;
}

Vector4 const Vector4::Zero = { 0.f, 0.f, 0.f, 0.f };
Vector4 const Vector4::One = { 1.f, 1.f, 1.f, 1.f };
Vector4 const Vector4::UnitX = { 1.f, 0.f, 0.f, 0.f };
Vector4 const Vector4::UnitY = { 0.f, 1.f, 0.f, 0.f };
Vector4 const Vector4::UnitZ = { 0.f, 0.f, 1.f, 0.f };
Vector4 const Vector4::UnitW = { 0.f, 0.f, 0.f, 1.f };

inline Vector4& Vector4::operator+=(Vector4 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorAdd(v1, v2));
	return *this;
}

inline Vector4& Vector4::operator-=(Vector4 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorSubtract(v1, v2));
	return *this;
}

inline Vector4& Vector4::operator*=(Vector4 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorMultiply(v1, v2));
	return *this;
}

inline Vector4& Vector4::operator*=(float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorScale(v, _s));
	return *this;
}

inline Vector4& Vector4::operator/=(Vector4 const& _v)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorDivide(v1, v2));
	return *this;
}

inline Vector4& Vector4::operator/=(float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorScale(v, 1.f / _s));
	return *this;
}

inline bool Vector4::operator==(Vector4 const& _v) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v));
	return XMVector4Equal(v1, v2);
}

inline bool Vector4::operator!=(Vector4 const& _v) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v));
	return XMVector4NotEqual(v1, v2);
}

inline float Vector4::Distance(Vector4 const& _v1, Vector4 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	return XMVectorGetX(XMVector4Length(XMVectorSubtract(v2, v1)));
}

inline float Vector4::DistanceSquared(Vector4 const& _v1, Vector4 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	return XMVectorGetX(XMVector4LengthSq(XMVectorSubtract(v2, v1)));
}

inline void Vector4::Min(Vector4 const& _v1, Vector4 const& _v2, Vector4& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVectorMin(v1, v2));
}

inline Vector4 Vector4::Min(Vector4 const& _v1, Vector4 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorMin(v1, v2));
	return R;
}

inline void Vector4::Max(Vector4 const& _v1, Vector4 const& _v2, Vector4& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVectorMax(v1, v2));
}

inline Vector4 Vector4::Max(Vector4 const& _v1, Vector4 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorMax(v1, v2));
	return R;
}

inline void Vector4::Lerp(Vector4 const& _v1, Vector4 const& _v2, float _t, Vector4& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVectorLerp(v1, v2, _t));
}

inline Vector4 Vector4::Lerp(Vector4 const& _v1, Vector4 const& _v2, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorLerp(v1, v2, _t));
	return R;
}

inline void Vector4::SmoothStep(const Vector4& _v1, const Vector4& _v2, float _t, Vector4& _r)
{
	using namespace DirectX;
	_t = std::clamp(_t, 0.f, 1.f);
	_t = _t * _t * (3.f - 2.f * _t);
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVectorLerp(v1, v2, _t));
}

inline Vector4 Vector4::SmoothStep(Vector4 const& _v1, Vector4 const& _v2, float _t)
{
	using namespace DirectX;
	_t = std::clamp(_t, 0.f, 1.f);
	_t = _t * _t * (3.f - 2.f * _t);
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorLerp(v1, v2, _t));
	return R;
}

inline void Vector4::Barycentric(Vector4 const& _v1, Vector4 const& _v2, Vector4 const& _v3, float _f, float _g, Vector4& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v3));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVectorBaryCentric(v1, v2, v3, _f, _g));
}

inline Vector4 Vector4::Barycentric(Vector4 const& _v1, Vector4 const& _v2, Vector4 const& _v3, float _f, float _g)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v3));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorBaryCentric(v1, v2, v3, _f, _g));
	return R;
}

inline void Vector4::CatmullRom(Vector4 const& _v1, Vector4 const& _v2, Vector4 const& _v3, Vector4 const& _v4, float _t, Vector4& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v3));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v4));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVectorCatmullRom(v1, v2, v3, v4, _t));
}

inline Vector4 Vector4::CatmullRom(Vector4 const& _v1, Vector4 const& _v2, Vector4 const& _v3, Vector4 const& _v4, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v3));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v4));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorCatmullRom(v1, v2, v3, v4, _t));
	return R;
}

inline void Vector4::Hermite(Vector4 const& _v1, Vector4 const& _t1, Vector4 const& _v2, Vector4 const& _t2, float _t, Vector4& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_t1));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_t2));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVectorHermite(v1, v2, v3, v4, _t));
}

inline Vector4 Vector4::Hermite(Vector4 const& _v1, Vector4 const& _t1, Vector4 const& _v2, Vector4 const& _t2, float _t)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_t1));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_t2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorHermite(v1, v2, v3, v4, _t));
	return R;
}

inline void Vector4::Reflect(Vector4 const& _i, Vector4 const& _n, Vector4& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_n));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVector4Reflect(v1, v2));
}

inline Vector4 Vector4::Reflect(Vector4 const& _i, Vector4 const& _n)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_n));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVector4Reflect(v1, v2));
	return R;
}

inline void Vector4::Refract(Vector4 const& _i, Vector4 const& _n, float _refractive_index, Vector4& _r)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_n));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVector4Refract(v1, v2, _refractive_index));
}

inline Vector4 Vector4::Refract(Vector4 const& _i, Vector4 const& _n, float _refractive_index)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_i));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_n));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVector4Refract(v1, v2, _refractive_index));
	return R;
}

inline bool Vector4::InBounds(Vector4 const& _bounds) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_bounds));
	return XMVector4InBounds(v1, v2);
}

inline float Vector4::Length() const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	return XMVectorGetX(XMVector4Length(v));
}

inline float Vector4::LengthSquared() const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	return XMVectorGetX(XMVector4LengthSq(v));
}

inline float Vector4::Dot(Vector4 const& _v1) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	return XMVectorGetX(XMVector4Dot(v1, v2));
}

inline void Vector4::Cross(Vector4 const& _v1, Vector4 const& _v2, Vector4& _r) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVector4Cross(v1, v2, v3));
}

inline Vector4 Vector4::Cross(Vector4 const& _v1, Vector4 const& _v2) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVector4Cross(v1, v2, v3));
	return R;
}

inline void Vector4::Normalize(Vector4& _r) const
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVector4Normalize(v));
}

inline void Vector4::Normalize()
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVector4Normalize(v));
}

inline void Vector4::Clamp(Vector4 const& _v_min, Vector4 const& _v_max, Vector4& _r) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v_min));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v_max));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_r), XMVectorClamp(v1, v2, v3));
}

inline void Vector4::Clamp(Vector4 const& _v_min, Vector4 const& _v_max)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(this));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v_min));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v_max));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(this), XMVectorClamp(v1, v2, v3));
}

inline Vector4 operator+(Vector4 const& _v1, Vector4 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorAdd(v1, v2));
	return R;
}

inline Vector4 operator-(Vector4 const& _v1, Vector4 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorSubtract(v1, v2));
	return R;
}

inline Vector4 operator*(Vector4 const& _v1, Vector4 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorMultiply(v1, v2));
	return R;
}

inline Vector4 operator*(Vector4 const& _v, float _s)
{
	using namespace DirectX;
	XMVECTOR v = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorScale(v, _s));
	return R;
}

inline Vector4 operator/(Vector4 const& _v1, Vector4 const& _v2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v1));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v2));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorDivide(v1, v2));
	return R;
}

inline Vector4 operator/(Vector4 const& _v, float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_v));
	Vector4 R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R), XMVectorScale(v, 1.f / _s));
	return R;
}

Matrix const Matrix::Identity = {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};

inline Matrix& Matrix::operator+=(Matrix const& _m)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_41));
	XMVECTOR v5 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._11));
	XMVECTOR v6 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._21));
	XMVECTOR v7 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._31));
	XMVECTOR v8 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._41));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), XMVectorAdd(v1, v5));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), XMVectorAdd(v2, v6));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), XMVectorAdd(v3, v7));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), XMVectorAdd(v4, v8));
	return *this;
}

inline Matrix& Matrix::operator-=(Matrix const& _m)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_41));
	XMVECTOR v5 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._11));
	XMVECTOR v6 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._21));
	XMVECTOR v7 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._31));
	XMVECTOR v8 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._41));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), XMVectorSubtract(v1, v5));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), XMVectorSubtract(v2, v6));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), XMVectorSubtract(v3, v7));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), XMVectorSubtract(v4, v8));
	return *this;
}

inline Matrix& Matrix::operator*=(Matrix const& _m)
{
	using namespace DirectX;
	XMMATRIX m1 = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(this));
	XMMATRIX m2 = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(&_m));
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(this), XMMatrixMultiply(m1, m2));
	return *this;
}

inline Matrix& Matrix::operator*=(float _s)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_41));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), XMVectorScale(v1, _s));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), XMVectorScale(v2, _s));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), XMVectorScale(v3, _s));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), XMVectorScale(v4, _s));
	return *this;
}

inline Matrix& Matrix::operator/=(Matrix const& _m)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_41));
	XMVECTOR v5 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._11));
	XMVECTOR v6 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._21));
	XMVECTOR v7 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._31));
	XMVECTOR v8 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._41));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), XMVectorDivide(v1, v5));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), XMVectorDivide(v2, v6));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), XMVectorDivide(v3, v7));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), XMVectorDivide(v4, v8));
	return *this;
}

inline Matrix& Matrix::operator/=(float _s)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_41));
	float rs = 1.f / _s;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), XMVectorScale(v1, rs));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), XMVectorScale(v2, rs));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), XMVectorScale(v3, rs));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), XMVectorScale(v4, rs));
	return *this;
}

bool Matrix::operator==(Matrix const& _m) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_41));
	XMVECTOR v5 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._11));
	XMVECTOR v6 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._21));
	XMVECTOR v7 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._31));
	XMVECTOR v8 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._41));
	return XMVector4Equal(v1, v5)
		&& XMVector4Equal(v2, v6)
		&& XMVector4Equal(v3, v7)
		&& XMVector4Equal(v4, v8);
}

bool Matrix::operator!=(Matrix const& _m) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_41));
	XMVECTOR v5 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._11));
	XMVECTOR v6 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._21));
	XMVECTOR v7 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._31));
	XMVECTOR v8 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m._41));
	return !(XMVector4Equal(v1, v5)
		&& XMVector4Equal(v2, v6)
		&& XMVector4Equal(v3, v7)
		&& XMVector4Equal(v4, v8));
}

Matrix Matrix::CreateScale(Vector3 const& _scales)
{
	using namespace DirectX;
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixScaling(_scales.x, _scales.y, _scales.z));
	return R;
}

Matrix Matrix::CreateScale(float _xs, float _ys, float _zs)
{
	using namespace DirectX;
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixScaling(_xs, _ys, _zs));
	return R;
}

Matrix Matrix::CreateScale(float _s)
{
	using namespace DirectX;
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixScaling(_s, _s, _s));
	return R;
}

Matrix Matrix::CreateRotationX(float _radians)
{
	using namespace DirectX;
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixRotationX(_radians));
	return R;
}

Matrix Matrix::CreateRotationY(float _radians)
{
	using namespace DirectX;
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixRotationY(_radians));
	return R;
}

Matrix Matrix::CreateRotationZ(float _radians)
{
	using namespace DirectX;
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixRotationZ(_radians));
	return R;
}

Matrix Matrix::CreateFromRollPitchYaw(float _pitch, float _yaw, float _roll)
{
	using namespace DirectX;
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixRotationRollPitchYaw(_pitch, _yaw, _roll));
	return R;
}

Matrix Matrix::CreateFromAxisAngle(Vector3 const& _axis, float _radians)
{
	using namespace DirectX;
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixRotationAxis(_axis, _radians));
	return R;
}

Matrix Matrix::CreateTranslation(Vector3 const& _position)
{
	using namespace DirectX;
	XMMATRIX R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixTranslation(_position.x, _position.y, _position.z));
	return R;
}

Matrix Matrix::CreateTranslation(float _x, float _y, float _z)
{
	using namespace DirectX;
	XMMATRIX R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixTranslation(_x, _y, _z));
	return R;
}

void Matrix::Transpose(Matrix& _r) const
{
	using namespace DirectX;
	XMMATRIX m = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(this));
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&_r), XMMatrixTranspose(m));
}

Matrix Matrix::Transpose() const
{
	using namespace DirectX;
	XMMATRIX m = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(this));
	XMMATRIX R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixTranspose(m));
	return R;
}

void Matrix::Invert(Matrix& _r) const
{
	using namespace DirectX;
	XMMATRIX m = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(this));
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&_r), XMMatrixInverse(nullptr, m));
}

Matrix Matrix::Invert() const
{
	using namespace DirectX;
	XMMATRIX m = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(this));
	XMMATRIX R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixInverse(nullptr, m));
	return R;
}

float Matrix::Determinant() const
{
	using namespace DirectX;
	XMMATRIX m = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(this));
	return XMVectorGetX(XMMatrixDeterminant(m));
}

Matrix operator+(Matrix const& _m1, Matrix const& _m2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._41));
	XMVECTOR v5 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._11));
	XMVECTOR v6 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._21));
	XMVECTOR v7 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._31));
	XMVECTOR v8 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._41));
	Matrix R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), XMVectorAdd(v1, v5));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), XMVectorAdd(v2, v6));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), XMVectorAdd(v3, v7));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), XMVectorAdd(v4, v8));
	return R;
}

Matrix operator-(Matrix const& _m1, Matrix const& _m2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._41));
	XMVECTOR v5 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._11));
	XMVECTOR v6 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._21));
	XMVECTOR v7 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._31));
	XMVECTOR v8 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._41));
	Matrix R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), XMVectorSubtract(v1, v5));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), XMVectorSubtract(v2, v6));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), XMVectorSubtract(v3, v7));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), XMVectorSubtract(v4, v8));
	return R;
}

Matrix operator*(Matrix const& _m1, Matrix const& _m2)
{
	using namespace DirectX;
	XMMATRIX m1 = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(&_m1));
	XMMATRIX m2 = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4 const*>(&_m2));
	Matrix R{};
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&R), XMMatrixMultiply(m1, m2));
	return R;
}

Matrix operator*(Matrix const& _m1, float _s)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._41));
	Matrix R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), XMVectorScale(v1, _s));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), XMVectorScale(v2, _s));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), XMVectorScale(v3, _s));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), XMVectorScale(v4, _s));
	return R;
}

Matrix operator/(Matrix const& _m1, Matrix const& _m2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._41));
	XMVECTOR v5 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._11));
	XMVECTOR v6 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._21));
	XMVECTOR v7 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._31));
	XMVECTOR v8 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m2._41));
	Matrix R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), XMVectorDivide(v1, v5));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), XMVectorDivide(v2, v6));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), XMVectorDivide(v3, v7));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), XMVectorDivide(v4, v8));
	return R;
}

Matrix operator/(Matrix const& _m1, float _s)
{
	using namespace DirectX;
	assert(_s != 0.f);
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4 const*>(&_m1._41));
	float rs = 1.f / _s;
	Matrix R{};
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), XMVectorScale(v1, rs));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), XMVectorScale(v2, rs));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), XMVectorScale(v3, rs));
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), XMVectorScale(v4, rs));
	return R;
}
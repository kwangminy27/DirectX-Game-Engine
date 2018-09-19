#pragma once

namespace DG
{
	namespace Math
	{
		struct DG_MATH_DLL Vector2
		{
			Vector2() = default;
			Vector2(Vector2 const&) = default;
			Vector2(Vector2&&) = default;
			Vector2(float _x, float _y) : x(_x), y(_y) {}
			Vector2(DirectX::FXMVECTOR _v) { DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(this), _v); }
			Vector2(DirectX::XMFLOAT2 const& _v) { this->x = _v.x; this->y = _v.y; }

			operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat2(reinterpret_cast<DirectX::XMFLOAT2 const*>(this)); }

			Vector2& operator=(Vector2 const&) = default;
			Vector2& operator=(Vector2&&) = default;
			Vector2& operator+=(Vector2 const& _v);
			Vector2& operator-=(Vector2 const& _v);
			Vector2& operator*=(Vector2 const& _v);
			Vector2& operator*=(float _s);
			Vector2& operator/=(Vector2 const& _v);
			Vector2& operator/=(float _s);

			bool operator==(Vector2 const& _v) const;
			bool operator!=(Vector2 const& _v) const;

			Vector2 operator+() const { return *this; }
			Vector2 operator-() const { return Vector2(-x, -y); }

			static float Distance(Vector2 const& _v1, Vector2 const& _v2);
			static float DistanceSquared(Vector2 const& _v1, Vector2 const& _v2);

			static void Min(Vector2 const& _v1, Vector2 const& _v2, Vector2& _r);
			static Vector2 Min(Vector2 const& _v1, Vector2 const& _v2);

			static void Max(Vector2 const& _v1, Vector2 const& _v2, Vector2& _r);
			static Vector2 Max(Vector2 const& _v1, Vector2 const& _v2);

			static void Lerp(Vector2 const& _v1, Vector2 const& _v2, float _t, Vector2& _r);
			static Vector2 Lerp(Vector2 const& _v1, Vector2 const& _v2, float _t);

			static void SmoothStep(Vector2 const& _v1, Vector2 const& _v2, float _t, Vector2& _r);
			static Vector2 SmoothStep(Vector2 const& _v1, Vector2 const& _v2, float _t);

			static void Barycentric(Vector2 const& _v1, Vector2 const& _v2, Vector2 const& _v3, float _f, float _g, Vector2& _r);
			static Vector2 Barycentric(Vector2 const& _v1, Vector2 const& _v2, Vector2 const& _v3, float _f, float _g);

			static void CatmullRom(Vector2 const& _v1, Vector2 const& _v2, Vector2 const& _v3, Vector2 const& _v4, float _t, Vector2& _r);
			static Vector2 CatmullRom(Vector2 const& _v1, Vector2 const& _v2, Vector2 const& _v3, Vector2 const& _v4, float _t);

			static void Hermite(Vector2 const& _v1, Vector2 const& _t1, Vector2 const& _v2, Vector2 const& _t2, float _t, Vector2& _r);
			static Vector2 Hermite(Vector2 const& _v1, Vector2 const& _t1, Vector2 const& _v2, Vector2 const& _t2, float _t);

			static void Reflect(Vector2 const& _i, Vector2 const& _n, Vector2& _r);
			static Vector2 Reflect(Vector2 const& _i, Vector2 const& _n);

			static void Refract(Vector2 const& _i, Vector2 const& _n, float _refractive_index, Vector2& _r);
			static Vector2 Refract(Vector2 const& _i, Vector2 const& _n, float _refractive_index);

			bool InBounds(Vector2 const& _bounds) const;

			float Length() const;
			float LengthSquared() const;

			float Dot(Vector2 const& _v) const;
			void Cross(Vector2 const& _v, Vector2& _r) const;
			Vector2 Cross(Vector2 const& _v) const;

			void Normalize(Vector2& _r) const;
			void Normalize();

			void Clamp(Vector2 const& _v_min, Vector2 const& _v_max, Vector2& _r) const;
			void Clamp(Vector2 const& _v_min, Vector2 const& _v_max);

			static Vector2 const Zero;
			static Vector2 const One;
			static Vector2 const UnitX;
			static Vector2 const UnitY;

			float x;
			float y;
		};

		Vector2 DG_MATH_DLL operator+(Vector2 const& _v1, Vector2 const& _v2);
		Vector2 DG_MATH_DLL operator-(Vector2 const& _v1, Vector2 const& _v2);
		Vector2 DG_MATH_DLL operator*(Vector2 const& _v1, Vector2 const& _v2);
		Vector2 DG_MATH_DLL operator*(Vector2 const& _v, float _s);
		Vector2 DG_MATH_DLL operator/(Vector2 const& _v1, Vector2 const& _v2);
		Vector2 DG_MATH_DLL operator/(Vector2 const& _v, float _s);

		struct DG_MATH_DLL Vector3
		{
			Vector3() = default;
			Vector3(Vector3 const&) = default;
			Vector3(Vector3&&) = default;
			Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
			Vector3(DirectX::FXMVECTOR _v) { DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(this), _v); }
			Vector3(DirectX::XMFLOAT3 const& _v) { this->x = _v.x; this->y = _v.y; this->z = _v.z; }

			operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat3(reinterpret_cast<DirectX::XMFLOAT3 const*>(this)); }

			Vector3& operator=(Vector3 const&) = default;
			Vector3& operator=(Vector3&&) = default;
			Vector3& operator+=(Vector3 const& _v);
			Vector3& operator-=(Vector3 const& _v);
			Vector3& operator*=(Vector3 const& _v);
			Vector3& operator*=(float _s);
			Vector3& operator/=(Vector3 const& _v);
			Vector3& operator/=(float _s);

			bool operator==(Vector3 const& _v) const;
			bool operator!=(Vector3 const& _v) const;

			Vector3 operator+() const { return *this; }
			Vector3 operator-() const { return Vector3(-x, -y, -z); }

			static float Distance(Vector3 const& _v1, Vector3 const& _v2);
			static float DistanceSquared(Vector3 const& _v1, Vector3 const& _v2);

			static void Min(Vector3 const& _v1, Vector3 const& _v2, Vector3& _r);
			static Vector3 Min(Vector3 const& _v1, Vector3 const& _v2);

			static void Max(Vector3 const& _v1, Vector3 const& _v2, Vector3& _r);
			static Vector3 Max(Vector3 const& _v1, Vector3 const& _v2);

			static void Lerp(Vector3 const& _v1, Vector3 const& _v2, float _t, Vector3& _r);
			static Vector3 Lerp(Vector3 const& _v1, Vector3 const& _v2, float _t);

			static void SmoothStep(Vector3 const& _v1, Vector3 const& _v2, float _t, Vector3& _r);
			static Vector3 SmoothStep(Vector3 const& _v1, Vector3 const& _v2, float _t);

			static void Barycentric(Vector3 const& _v1, Vector3 const& _v2, Vector3 const& _v3, float _f, float _g, Vector3& _r);
			static Vector3 Barycentric(Vector3 const& _v1, Vector3 const& _v2, Vector3 const& _v3, float _f, float _g);

			static void CatmullRom(Vector3 const& _v1, Vector3 const& _v2, Vector3 const& _v3, Vector3 const& _v4, float _t, Vector3& _r);
			static Vector3 CatmullRom(Vector3 const& _v1, Vector3 const& _v2, Vector3 const& _v3, Vector3 const& _v4, float _t);

			static void Hermite(Vector3 const& _v1, Vector3 const& _t1, Vector3 const& _v2, Vector3 const& _t2, float _t, Vector3& _r);
			static Vector3 Hermite(Vector3 const& _v1, Vector3 const& _t1, Vector3 const& _v2, Vector3 const& _t2, float _t);

			static void Reflect(Vector3 const& _i, Vector3 const& _n, Vector3& _r);
			static Vector3 Reflect(Vector3 const& _i, Vector3 const& _n);

			static void Refract(Vector3 const& _i, Vector3 const& _n, float _refractive_index, Vector3& _r);
			static Vector3 Refract(Vector3 const& _i, Vector3 const& _n, float _refractive_index);

			bool InBounds(Vector3 const& _bounds) const;

			float Length() const;
			float LengthSquared() const;

			float Dot(Vector3 const& _v) const;
			void Cross(Vector3 const& _v, Vector3& _r) const;
			Vector3 Cross(Vector3 const& _v) const;

			void Normalize(Vector3& _r) const;
			void Normalize();

			void Clamp(Vector3 const& _v_min, Vector3 const& _v_max, Vector3& _r) const;
			void Clamp(Vector3 const& _v_min, Vector3 const& _v_max);

			static Vector3 const Zero;
			static Vector3 const One;
			static Vector3 const UnitX;
			static Vector3 const UnitY;
			static Vector3 const UnitZ;
			static Vector3 const Up;
			static Vector3 const Down;
			static Vector3 const Right;
			static Vector3 const Left;
			static Vector3 const Forward;
			static Vector3 const Backward;

			float x;
			float y;
			float z;
		};

		Vector3 DG_MATH_DLL operator+(Vector3 const& _v1, Vector3 const& _v2);
		Vector3 DG_MATH_DLL operator-(Vector3 const& _v1, Vector3 const& _v2);
		Vector3 DG_MATH_DLL operator*(Vector3 const& _v1, Vector3 const& _v2);
		Vector3 DG_MATH_DLL operator*(Vector3 const& _v, float _s);
		Vector3 DG_MATH_DLL operator/(Vector3 const& _v1, Vector3 const& _v2);
		Vector3 DG_MATH_DLL operator/(Vector3 const& _v, float _s);

		struct DG_MATH_DLL Vector4
		{
			Vector4() = default;
			Vector4(Vector4 const&) = default;
			Vector4(Vector4&&) = default;
			Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
			Vector4(DirectX::FXMVECTOR _v) { DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(this), _v); }
			Vector4(DirectX::XMFLOAT4 const& _v) { this->x = _v.x; this->y = _v.y; this->z = _v.z; this->w = _v.w; }

			operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4 const*>(this)); }

			Vector4& operator=(Vector4 const&) = default;
			Vector4& operator=(Vector4&&) = default;
			Vector4& operator+=(Vector4 const& _v);
			Vector4& operator-=(Vector4 const& _v);
			Vector4& operator*=(Vector4 const& _v);
			Vector4& operator*=(float _s);
			Vector4& operator/=(Vector4 const& _v);
			Vector4& operator/=(float _s);

			bool operator==(Vector4 const& _v) const;
			bool operator!=(Vector4 const& _v) const;

			Vector4 operator+() const { return *this; }
			Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

			static float Distance(Vector4 const& _v1, Vector4 const& _v2);
			static float DistanceSquared(Vector4 const& _v1, Vector4 const& _v2);

			static void Min(Vector4 const& _v1, Vector4 const& _v2, Vector4& _r);
			static Vector4 Min(Vector4 const& _v1, Vector4 const& _v2);

			static void Max(Vector4 const& _v1, Vector4 const& _v2, Vector4& _r);
			static Vector4 Max(Vector4 const& _v1, Vector4 const& _v2);

			static void Lerp(Vector4 const& _v1, Vector4 const& _v2, float _t, Vector4& _r);
			static Vector4 Lerp(Vector4 const& _v1, Vector4 const& _v2, float _t);

			static void SmoothStep(Vector4 const& _v1, Vector4 const& _v2, float _t, Vector4& _r);
			static Vector4 SmoothStep(Vector4 const& _v1, Vector4 const& _v2, float _t);

			static void Barycentric(Vector4 const& _v1, Vector4 const& _v2, Vector4 const& _v3, float _f, float _g, Vector4& _r);
			static Vector4 Barycentric(Vector4 const& _v1, Vector4 const& _v2, Vector4 const& _v3, float _f, float _g);

			static void CatmullRom(Vector4 const& _v1, Vector4 const& _v2, Vector4 const& _v3, Vector4 const& _v4, float _t, Vector4& _r);
			static Vector4 CatmullRom(Vector4 const& _v1, Vector4 const& _v2, Vector4 const& _v3, Vector4 const& _v4, float _t);

			static void Hermite(Vector4 const& _v1, Vector4 const& _t1, Vector4 const& _v2, Vector4 const& _t2, float _t, Vector4& _r);
			static Vector4 Hermite(Vector4 const& _v1, Vector4 const& _t1, Vector4 const& _v2, Vector4 const& _t2, float _t);

			static void Reflect(Vector4 const& _i, Vector4 const& _n, Vector4& _r);
			static Vector4 Reflect(Vector4 const& _i, Vector4 const& _n);

			static void Refract(Vector4 const& _i, Vector4 const& _n, float _refractive_index, Vector4& _r);
			static Vector4 Refract(Vector4 const& _i, Vector4 const& _n, float _refractive_index);

			bool InBounds(Vector4 const& _bounds) const;

			float Length() const;
			float LengthSquared() const;

			float Dot(Vector4 const& _v) const;
			void Cross(Vector4 const& _v1, Vector4 const& _v2, Vector4& _r) const;
			Vector4 Cross(Vector4 const& _v1, Vector4 const& _v2) const;

			void Normalize(Vector4& _r) const;
			void Normalize();

			void Clamp(Vector4 const& _v_min, Vector4 const& _v_max, Vector4& _r) const;
			void Clamp(Vector4 const& _v_min, Vector4 const& _v_max);

			static Vector4 const Zero;
			static Vector4 const One;
			static Vector4 const UnitX;
			static Vector4 const UnitY;
			static Vector4 const UnitZ;
			static Vector4 const UnitW;

			float x;
			float y;
			float z;
			float w;
		};

		Vector4 DG_MATH_DLL operator+(Vector4 const& _v1, Vector4 const& _v2);
		Vector4 DG_MATH_DLL operator-(Vector4 const& _v1, Vector4 const& _v2);
		Vector4 DG_MATH_DLL operator*(Vector4 const& _v1, Vector4 const& _v2);
		Vector4 DG_MATH_DLL operator*(Vector4 const& _v, float _s);
		Vector4 DG_MATH_DLL operator/(Vector4 const& _v1, Vector4 const& _v2);
		Vector4 DG_MATH_DLL operator/(Vector4 const& _v, float _s);

		struct DG_MATH_DLL Matrix
		{
			Matrix() = default;
			Matrix(Matrix const&) = default;
			Matrix(Matrix&&) = default;
			Matrix(
				float _m00, float _m01, float _m02, float _m03,
				float _m10, float _m11, float _m12, float _m13,
				float _m20, float _m21, float _m22, float _m23,
				float _m30, float _m31, float _m32, float _m33) :
				_11(_m00), _12(_m01), _13(_m02), _14(_m03),
				_21(_m10), _22(_m11), _23(_m12), _24(_m13),
				_31(_m20), _32(_m21), _33(_m22), _34(_m23),
				_41(_m30), _42(_m31), _43(_m32), _44(_m33) {}
			Matrix(Vector4 const& _r0, Vector4 const& _r1, Vector4 const& _r2, Vector4 const& _r3) :
				_11(_r0.x), _12(_r0.y), _13(_r0.z), _14(_r0.w),
				_21(_r1.x), _22(_r1.y), _23(_r1.z), _24(_r1.w),
				_31(_r2.x), _32(_r2.y), _33(_r2.z), _34(_r2.w),
				_41(_r3.x), _42(_r3.y), _43(_r3.z), _44(_r3.w) {}
			Matrix(DirectX::FXMMATRIX _m) { DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(this), _m); }
			Matrix(DirectX::XMFLOAT4X4 const& _m) { memcpy_s(this, sizeof(float) * 16, &_m, sizeof(DirectX::XMFLOAT4X4)); }

			operator DirectX::XMMATRIX() const { return DirectX::XMLoadFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4 const*>(this)); }

			Matrix& operator=(Matrix const&) = default;
			Matrix& operator=(Matrix&&) = default;
			Matrix& operator+=(Matrix const& _m);
			Matrix& operator-=(Matrix const& _m);
			Matrix& operator*=(Matrix const& _m);
			Matrix& operator*=(float _s);
			Matrix& operator/=(Matrix const& _m);
			Matrix& operator/=(float _s);

			bool operator==(Matrix const& _m) const;
			bool operator!=(Matrix const& _m) const;

			Matrix operator+() const { return *this; }
			Matrix operator-() const {
				return Matrix(
					-Vector4(_11, _12, _13, _14),
					-Vector4(_21, _22, _23, _24),
					-Vector4(_31, _32, _33, _34),
					-Vector4(_41, _42, _43, _44));
			}

			static Matrix CreateScale(Vector3 const& _scales);
			static Matrix CreateScale(float _xs, float _ys, float _zs);
			static Matrix CreateScale(float _s);

			static Matrix CreateRotationX(float _radians);
			static Matrix CreateRotationY(float _radians);
			static Matrix CreateRotationZ(float _radians);
			static Matrix CreateFromRollPitchYaw(float _pitch, float _yaw, float _roll);
			static Matrix CreateFromAxisAngle(Vector3 const& _axis, float _radians);

			static Matrix CreateTranslation(Vector3 const& _position);
			static Matrix CreateTranslation(float _x, float _y, float _z);
			/*
			// Static functions
			static Matrix CreateBillboard(const Vector3& object, const Vector3& cameraPosition, const Vector3& cameraUp, _In_opt_ const Vector3* cameraForward = nullptr);

			static Matrix CreateConstrainedBillboard(const Vector3& object, const Vector3& cameraPosition, const Vector3& rotateAxis,
													 _In_opt_ const Vector3* cameraForward = nullptr, _In_opt_ const Vector3* objectForward = nullptr);

			static Matrix CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane);
			static Matrix CreatePerspective(float width, float height, float nearPlane, float farPlane);
			static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane);
			static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
			static Matrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

			static Matrix CreateLookAt(const Vector3& position, const Vector3& target, const Vector3& up);
			static Matrix CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up);

			static Matrix CreateFromQuaternion(const Quaternion& quat);

			static Matrix CreateShadow(const Vector3& lightDir, const Plane& plane);

			static Matrix CreateReflection(const Plane& plane);

			static void Lerp(const Matrix& M1, const Matrix& M2, float t, Matrix& result);
			static Matrix Lerp(const Matrix& M1, const Matrix& M2, float t);

			static void Transform(const Matrix& M, const Quaternion& rotation, Matrix& result);
			static Matrix Transform(const Matrix& M, const Quaternion& rotation);
			*/

			//bool Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation);

			void Transpose(Matrix& _r) const;
			Matrix Transpose() const;

			void Invert(Matrix& _r) const;
			Matrix Invert() const;

			float Determinant() const;

			Vector3 Up() const { return Vector3(_21, _22, _23); }
			void Up(Vector3 const& _v) { _21 = _v.x; _22 = _v.y; _23 = _v.z; }

			Vector3 Down() const { return Vector3(-_21, -_22, -_23); }
			void Down(Vector3 const& _v) { _21 = -_v.x; _22 = -_v.y; _23 = -_v.z; }

			Vector3 Right() const { return Vector3(_11, _12, _13); }
			void Right(Vector3 const& _v) { _11 = _v.x; _12 = _v.y; _13 = _v.z; }

			Vector3 Left() const { return Vector3(-_11, -_12, -_13); }
			void Left(Vector3 const& _v) { _11 = -_v.x; _12 = -_v.y; _13 = -_v.z; }

			Vector3 Forward() const { return Vector3(_31, _32, _33); }
			void Forward(Vector3 const& _v) { _31 = _v.x; _32 = _v.y; _33 = _v.z; }

			Vector3 Backward() const { return Vector3(-_31, -_32, -_33); }
			void Backward(Vector3 const& _v) { _31 = -_v.x; _32 = -_v.y; _33 = -_v.z; }

			Vector3 Translation() const { return Vector3(_41, _42, _43); }
			void Translation(Vector3 const& _v) { _41 = _v.x; _42 = _v.y; _43 = _v.z; }

			static Matrix const Identity;

			union
			{
				struct
				{
					float _11, _12, _13, _14;
					float _21, _22, _23, _24;
					float _31, _32, _33, _34;
					float _41, _42, _43, _44;
				};
				float m[4][4];
			};
		};

		Matrix DG_MATH_DLL operator+(Matrix const& _m1, Matrix const& _m2);
		Matrix DG_MATH_DLL operator-(Matrix const& _m1, Matrix const& _m2);
		Matrix DG_MATH_DLL operator*(Matrix const& _m1, Matrix const& _m2);
		Matrix DG_MATH_DLL operator*(Matrix const& _m, float _s);
		Matrix DG_MATH_DLL operator/(Matrix const& _m1, Matrix const& _m2);
		Matrix DG_MATH_DLL operator/(Matrix const& _m, float _s);
	}
}
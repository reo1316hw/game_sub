#include "Collision.h"
#include <algorithm>
#include <array>

/*
@param	線分の開始地点のポジション
@param	線分の終了地点のポジション
*/
LineSegment::LineSegment(const Vector3 & _start, const Vector3 & _end)
	: m_start(_start)
	, m_end(_end)
{
}

/*
@brief	線分上の点を返す
@param	入力値 t（L(t) = Start + (End - Start)t）
@return 線分上の点のポジション
*/
Vector3 LineSegment::PointOnSegment(float _t) const
{
	return m_start + (m_end - m_start) * _t;
}

/*
@brief	点と線分の間の最短距離を返す
@param	任意の点のポジション
@return 最短距離
*/
float LineSegment::MinDistanceSquared(const Vector3 & _point) const
{
	Vector3 ab = m_end - m_start;
	Vector3 ba = -1.0f * ab;
	Vector3 ac = _point - m_start;
	Vector3 bc = _point - m_end;

	if (Vector3::Dot(ab, ac) < 0.0f)
	{
		return ac.LengthSq();
	}
	else if (Vector3::Dot(ba, bc) < 0.0f)
	{
		return bc.LengthSq();
	}
	else
	{
		float scalar = Vector3::Dot(ac, ab) / Vector3::Dot(ab, ab);
		Vector3 p = scalar * ab;
		return (ac - p).LengthSq();
	}
}

/*
@brief	線分と線分の間の最短距離を返す
@param	判定する線分の構造体１
@param	判定する線分の構造体２
@return 最短距離
*/
float LineSegment::MinDistanceSquared(const LineSegment & _line1, const LineSegment & _line2)
{
	Vector3 u = _line1.m_end - _line1.m_start;
	Vector3 v = _line2.m_end - _line2.m_start;
	Vector3 w = _line1.m_start - _line2.m_start;
	float   a = Vector3::Dot(u, u);
	float   b = Vector3::Dot(u, v);
	float   c = Vector3::Dot(v, v);
	float   d = Vector3::Dot(u, w);
	float   e = Vector3::Dot(v, w);
	float   D = a * c - b * b;
	float   sc, sN, sD = D;
	float   tc, tN, tD = D;

	if (Math::NearZero(D))
	{
		sN = 0.0f;
		sD = 1.0f;
		tN = e;
		tD = c;
	}
	else
	{
		sN = (b*e - c * d);
		tN = (a*e - b * d);
		if (sN < 0.0)
		{
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD)
		{
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (Math::NearZero(sN) ? 0.0f : sN / sD);
	tc = (Math::NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	Vector3   dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

	return dP.LengthSq();   // return the closest distance squared
}

/*
@param	平面の法線ベクトル
@param	平面と原点の符号つき最短距離
*/
Plane::Plane(const Vector3 & _normal, float _distance)
	: m_normal(_normal)
	, m_distance(_distance)
{
}

/*
@param	平面上の点1
@param	平面上の点2
@param	平面上の点3
*/
Plane::Plane(const Vector3 & _vec1, const Vector3 & _vec2, const Vector3 & _vec3)
{
	Vector3 ab = _vec2 - _vec1;
	Vector3 ac = _vec3 - _vec1;

	m_normal = Vector3::Cross(ab, ac);
	m_normal.Normalize();

	m_distance = -Vector3::Dot(_vec1, m_normal);

}

/*
@brief	点と平面の最短距離を返す
@param	任意の点のポジション
@return 符号つき最短距離
*/
float Plane::SignedDistance(const Vector3& _point)
{
	return Vector3::Dot(_point, m_normal) - m_distance;
}

/*
@param	球体の中心座標
@param	球体の半径
*/
Sphere::Sphere(const Vector3 & _center, const float _radius)
	: m_center(_center)
	, m_radius(_radius)
{
}

/*
@brief	球体に点が含まれているかどうか
@param	任意の点
@return true : 当たっている , false : 当たっていない
*/
bool Sphere::Contains(const Vector3 & _point) const
{
	float distansSquared = (m_center - _point).LengthSq();
	return distansSquared <= (m_radius * m_radius);
}

/*
@param	最小のx,y,zの値のポジション
@param	最大のx,y,zの値のポジション
*/
AABB::AABB(const Vector3 & _min, const Vector3 & _max)
	: m_min(_min),
	  m_max(_max)
{
}

/*
@brief	最小値と最大値を各成分ごとに更新する
@param	任意の点のポジション
*/
void AABB::UpdateMinMax(const Vector3 & _point)
{
	m_min.x = Math::Min(m_min.x, _point.x);
	m_min.y = Math::Min(m_min.y, _point.y);
	m_min.z = Math::Min(m_min.z, _point.z);

	m_max.x = Math::Max(m_max.x, _point.x);
	m_max.y = Math::Max(m_max.y, _point.y);
	m_max.z = Math::Max(m_max.z, _point.z);
}

/*
@brief	当たり判定ボックスの回転
@param	回転軸と回転表す値（Quaternion）
*/
void AABB::Rotate(const Quaternion & _quaternion)
{
	std::array<Vector3, 8> points;

	points[0] = m_min;

	points[1] = Vector3(m_max.x, m_min.y, m_min.z);
	points[2] = Vector3(m_min.x, m_max.y, m_min.z);
	points[3] = Vector3(m_min.x, m_min.y, m_max.z);

	points[4] = Vector3(m_min.x, m_max.y, m_max.z);
	points[5] = Vector3(m_max.x, m_min.y, m_max.z);
	points[6] = Vector3(m_max.x, m_max.y, m_min.z);

	points[7] = Vector3(m_max);

	Vector3 p = Vector3::Transform(points[0], _quaternion);

	m_min = p;
	m_max = p;

	for (std::size_t i = 1; i < points.size(); i++)
	{
		p = Vector3::Transform(points[i], _quaternion);
		UpdateMinMax(p);
	}
}

/*
@brief	ボックスに点が含まれているかどうか
@param	任意の点
@return true : 当たっている , false : 当たっていない
*/
bool AABB::Contains(const Vector3 & _point) const
{
	bool outside =
        _point.x < m_min.x ||
        _point.y < m_min.y ||
        _point.z < m_min.x ||
        _point.x > m_max.x ||
        _point.y > m_max.y ||
        _point.z > m_max.z;
	//どれも真でなければボックスの中に点がある
	return !outside;
}

/*
@brief	点とボックスの最短距離を返す
@param	任意の点
@return 最短距離
*/
float AABB::MinDistanceSquared(const Vector3 & _point) const
{
	float dx = Math::Max(m_min.x - _point.x, 0.0f);
	dx = Math::Max(dx, _point.x - m_max.x);
	float dy = Math::Max(m_min.y - _point.y, 0.0f);
	dy = Math::Max(dy, _point.y - m_max.y);
	float dz = Math::Max(m_min.z - _point.z, 0.0f);
	dz = Math::Max(dz, _point.z - m_max.z);

	return dx * dx + dy * dy + dz * dz;
}

/*
@param	始点となる点の座標
@param	終点となる点の座標
@param	カプセルの半径
*/
Capsule::Capsule(const Vector3 & _start, const Vector3 & _end, float _radius)
	: m_segment(_start, _end)
	, m_radius(_radius)
{
}

/*
@brief	カプセルの始点と終点の線分上の点を返す
@param	入力値 t（L(t) = Start + (End - Start)t）
@return 線分上の点のポジション
*/
Vector3 Capsule::PointOnSegment(float _t) const
{
	return m_segment.PointOnSegment(_t);
}

/*
@brief	カプセルに点が含まれているかどうか
@param	任意の点
@return true : 当たっている , false : 当たっていない
*/
bool Capsule::Contains(const Vector3 & _point) const
{
	float distanceSquared = m_segment.MinDistanceSquared(_point);
	return distanceSquared <= (m_radius * m_radius);
}

/*
@brief	２次元のポリゴンに点が含まれているかどうか
@param	任意の点
@return true : 当たっている , false : 当たっていない
*/
bool ConvexPolygon::Contains(const Vector2 & _point) const
{
	float sum = 0.0f;
	Vector2 a, b;
	for (std::size_t i = 0; i < m_vertices.size() - 1; i++)
	{
		a = m_vertices[i] - _point;
		a.Normalize();

		b = m_vertices[i + 1] - _point;
		b.Normalize();

		sum += Math::Acos(Vector2::Dot(a, b));
	}

	a = m_vertices.back() - _point;
	a.Normalize();
	b = m_vertices.front() - _point;
	b.Normalize();
	sum += Math::Acos(Vector2::Dot(a, b));

	return Math::NearZero(sum - Math::TwoPi);
}

/*
@brief	球と球の当たり判定
@param	球の構造体１
@param	球の構造体２
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const Sphere & _sphere1, const Sphere & _sphere2)
{
	float distanceSquared = (_sphere1.m_center - _sphere2.m_center).LengthSq();
	float sum_radius = _sphere1.m_radius + _sphere2.m_radius;
	return distanceSquared <= (sum_radius * sum_radius);
}

/*
@brief	ボックスとボックスの当たり判定
@param	ボックスの構造体１
@param	ボックスの構造体２
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const AABB & _AABB1, const AABB & _AABB2)
{
	bool no =
        _AABB1.m_max.x < _AABB2.m_min.x ||
        _AABB1.m_max.y < _AABB2.m_min.y ||
        _AABB1.m_max.z < _AABB2.m_min.z ||
        _AABB2.m_max.x < _AABB1.m_min.x ||
        _AABB2.m_max.y < _AABB1.m_min.y ||
        _AABB2.m_max.z < _AABB1.m_min.z;
	//これらのどれも真でなければ、交差している
	return !no;
}

/*
@brief	カプセルとカプセルの当たり判定
@param	カプセルの構造体１
@param	カプセルの構造体２
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const Capsule & _capsule1, const Capsule & _capsule2)
{
	float distanceSquared = LineSegment::MinDistanceSquared(_capsule1.m_segment,
        _capsule2.m_segment);
	float sum_radius = _capsule1.m_radius + _capsule2.m_radius;
	return distanceSquared <= (sum_radius * sum_radius);
}

/*
@brief	球とボックスの当たり判定
@param	球の構造体
@param	ボックスの構造体
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const Sphere & _sphere, const AABB & _AABB)
{
	bool hit = _AABB.Contains(_sphere.m_center);
	if (hit)
	{
		printf("%f,%f\n",_sphere.m_center,_sphere.m_radius);
		printf("%f,%f\n", _AABB.m_min, _AABB.m_max);
		return true;
	}
	float distanceSquared = _AABB.MinDistanceSquared(_sphere.m_center);
	return distanceSquared <= (_sphere.m_radius * _sphere.m_radius);
}

/*
@brief	線分と球の当たり判定
@param	線分の構造体
@param	球の構造体
@param	線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const LineSegment & _line, const Sphere & _sphere, float & _outT)
{
	Vector3 X = _line.m_start - _sphere.m_center;
    Vector3 Y = _line.m_end - _line.m_start;
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float c = Vector3::Dot(X, X) - _sphere.m_radius * _sphere.m_radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		discriminant = Math::Sqrt(discriminant);

		float tMin = (-b - discriminant) / (2.0f * a);
		float tMax = (-b + discriminant) / (2.0f * a);

		if (tMin >= 0.0f && tMin <= 1.0f)
		{
			_outT = tMin;
			return true;
		}
		else if (tMax >= 0.0f && tMax <= 1.0f)
		{
			_outT = tMax;
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*
@brief	線分と平面の当たり判定
@param	線分の構造体
@param	平面の構造体
@param	線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const LineSegment & _line, const Plane & _plane, float & _outT)
{
	float denom = Vector3::Dot(_line.m_end - _line.m_start,
		_plane.m_normal);
	if (Math::NearZero(denom))
	{
		if (Math::NearZero(Vector3::Dot(_line.m_start, _plane.m_normal) - _plane.m_distance))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float numer = -Vector3::Dot(_line.m_start, _plane.m_normal) - _plane.m_distance;
		_outT = numer / denom;
		if (_outT >= 0.0f && _outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*
@brief	各軸での面と線分の当たり判定
@param	線分の始点
@param	線分の終点
@param	平面上の点の値
@param	平面の法線ベクトル
@param	当たった物を格納する可変長コンテナ
@return true : 当たっている , false : 当たっていない
*/
bool TestSidePlane(float _start, float _end, float _negd, const Vector3& _norm,
	std::vector<std::pair<float, Vector3>>& _out)
{
	float denom = _end - _start;
	if (Math::NearZero(denom))
	{
		return false;
	}
	else
	{
		float numer = -_start + _negd;
		float t = numer / denom;
		// Test that t is within bounds
		if (t >= 0.0f && t <= 1.0f)
		{
			_out.emplace_back(t, _norm);
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*
@brief	線分とボックスの当たり判定
@param	線分の構造体
@param	ボックスの構造体
@param	線分の始点から接触している点までの値tを格納する
@param	線分の始点から接触した面の法線ベクトルを格納する
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const LineSegment & _line, const AABB & _AABB, float & _outT, Vector3 & _outNorm)
{
	std::vector<std::pair<float, Vector3>> values;

	TestSidePlane(_line.m_start.x, _line.m_end.x, _AABB.m_min.x, Vector3::NegUnitX, values);
	TestSidePlane(_line.m_start.x, _line.m_end.x, _AABB.m_max.x, Vector3::UnitX, values);
	TestSidePlane(_line.m_start.y, _line.m_end.y, _AABB.m_min.y, Vector3::NegUnitY, values);
	TestSidePlane(_line.m_start.y, _line.m_end.y, _AABB.m_max.y, Vector3::UnitY, values);
	TestSidePlane(_line.m_start.z, _line.m_end.z, _AABB.m_min.z, Vector3::NegUnitZ, values);
	TestSidePlane(_line.m_start.z, _line.m_end.z, _AABB.m_max.z, Vector3::UnitZ, values);

	std::sort(values.begin(), values.end(), [](
		const std::pair<float, Vector3>& a,
		const std::pair<float, Vector3>& b) {
			return a.first < b.first;
		});
	Vector3 point;
	for (auto& t : values)
	{
		point = _line.PointOnSegment(t.first);
		if (_AABB.Contains(point))
		{
            _outT = t.first;
            _outNorm = t.second;
			return true;
		}
	}
	return false;
}

/*
@fn	球スイープの当たり判定
@param	１フレーム前の球１の構造体
@param	現在のフレームの球１の構造体
@param	１フレーム前の球２の構造体
@param	現在のフレームの球２の構造体
@param	線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない
*/
bool SweptSphere(const Sphere & _sphere1, const Sphere & _sphere2, const Sphere & _sphere3, const Sphere & _sphere4, float & _outT)
{
	Vector3 X = _sphere1.m_center - _sphere3.m_center;
	Vector3 Y = _sphere2.m_center - _sphere1.m_center - (_sphere4.m_center - _sphere3.m_center);
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float sum_radius = _sphere1.m_radius + _sphere3.m_radius;
	float c = Vector3::Dot(X, X) - sum_radius * sum_radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		discriminant = Math::Sqrt(discriminant);

        _outT = (-b - discriminant) / (2.0f * a);
		if (_outT >= 0.0f && _outT <= 0.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

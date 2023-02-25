#include <iostream>
#include <cmath>

/*
    메모리 절약에는 struct가 속도에는 class가 좋다.
    class는 힘 메모리 영역에 선언되기 떄문에 garbage collection이 필요해 메모리를 더 많이 사용한다.
    struct는 스택 메모리에 영역에 선언되어 너무 많은 데이터를 가지고 있을 수는 없으나
    garbage collection 등이 불필요하다.

    struct는 생성시 값복사는 하고 class는 참조복사를 한다.

    그리고 struct는 기본적으로 public으로 권한이 설정되고 class는 private, public 등으로 해주지 않는다면 private이 기볹거으로 된다.

    즉 변수의 크기가 작거나, 수명이 짧고, 자주 할당되는 객체들은 struct로 만들어주면 좋다.
    (position, color, quaternion, rotation, scale 등)


*/
struct Vector2
{

public:
    Vector2(float x, float y);
};

Vector2 operator*(const Vector2 &v1, const Vector2 &v2);

struct Matrix2x2
{

public:
    Matrix2x2(Vector2 x, Vector2 y);
    Matrix2x2 Transpose();
    Matrix2x2 operator*(const float &scalar);
    Matrix2x2 operator*(const Matrix2x2 &m);
    Vector2 operator*(const Vector2 &v2);
};

int main()
{

    // 열벡터 (2.0,3.0)과 (4.0, 5.0)을 사용해 2 x 2 정방행렬을 생성하고 변수 mat1에 저장한다.
    Matrix2x2 mat1(Vector2(2.f, 3.f), Vector2(4.f, 5.f));
    // 행렬 mat1의 Traspose 함수를 사용해 전치행렬을 생성하고 변수 traposed에 저장
    Matrix2x2 transposed = mat1.Transpose(); // (2.f, 4.f) (3.f, 5.f)

    // 실수형 변수 scalar를 선언하고 10.0을 대입한다.
    float scalar = 10.f;
    // 행렬 mat1에 실수 scalar를 곱해 모든 요소가 10배로 늘린다.
    Matrix2x2 scalarMul = mat1 * scalar; // (20.f, 30.f) (40.f, 50.f)

    // 벡터 선언
    Vector2 vec1(5.f, .6f);
    // 행렬 mat1dhk  벡터 vec1을 서로 곱한 결과를 변수 vectorMul에 저장한다.
    Vector2 vectorMul = mat1 * vec1; // (34.f, 45.f)

    // 열벡터를 사용해 2x2 정방행렬을 생성하고 변수 mat2에 저장
    Matrix2x2 mat2(Vector2(6.f, 7.f), Vector2(8.f, 9.f));
    // 행렬 mat1과 mat2를 서로 곱한 후 결과를 변수 matMul에 저장한다.
    Matrix2x2 matMul = mat1 * mat2; // (40.f, 53.f) (52.f, 69.f)

    return 0;
}
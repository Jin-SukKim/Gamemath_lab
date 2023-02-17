/*
    3차원 공간의 회전을 표현하는 대표적인 방법 : 오일러 각(Euler's angle)

    오일러 각은 표준기저벡터를 중심으로 진행되는 세 번의 연속적인 회전을 의미한다.

    게임 엔진에서 오릴러 각을 사용해 물체의 방향을 표시할 때는 표준기저벡터를 사용한다.
    그래서 오일러 각은 표준기저벡터를 중심으로 회전하는 각의 크기로 지정된다.

    세 표준기저벡터를 중심으로 회전하는 각을 모으면 3차원 벡터로 표현 가능하다
    
    (x각도, y각도, z각도)

    각의 값은 실수이기 때문에 오일러 각은 Vector3 구조체를 사용해 관리할 수 있다.
    (0~360으로 표현)

    하지만 각 소프트웨어마다 세 축의 용도가 다르기에 오일러 각의 정보를
    모든 프로그램에서 범용적으로 사용할 순 없다.
    그렇기에 x,y,z축 대신 회전의 움직임으로 회전 동작을 구분하고 각을 지정하는 방법을 사용한다.

    표준기저벡터를 축으로 하는 회전의 움직임은 방향에 따라 Yaw, Roll, Pitch라 불린다.
    (항공기의 회전을 표현할 때 사용하는 용어와 같다.)

    Yaw : 위, y축
    Roll : 앞, z축
    Pitch : 오른쪽, x축

    오일러 각을 사용해 3차우너 공간의 회전을 표현할 수 있게 됬지만
    렌더링 과정에서 3차우너 공간의 회전을 사용하기 위해서는 회전행렬을 생성해야 된다.

    오일러 각은 세 번의 연속적인 회전을 의미한다.
    x축 회전은 yz 평면의 회전을 의미하는데 이 경우 x값은 변하지 않고 오직
    y축과 z축의 값만 변한다.
        ㅡ                 ㅡ
        | 1    0       0    |
    Rx =| 0 cos각도 -sin각도 |
        | 0 sin각도  cos각도 |
        ㅡ                 ㅡ

    동일하게 y축과 z축의 회전 행렬도 만들 수 있다.

        ㅡ                  ㅡ
        |  cos각도 0  sin각도 |
    Ry =|     0    1    0    |
        | -sin각도 0  cos각도 |
        ㅡ                  ㅡ

        ㅡ                 ㅡ
        | cos각도 -sin각도 0 |
    Rz =| sin각도  cos각도 0 |
        |    0       0    1 |
        ㅡ                 ㅡ    

    y축의 회전행렬 Ry는 다른 행렬과 좀 다르다.
    다른 행렬은 모두 우측 상단의 sin 함수가 음의 부호인 반면
    회전행렬 Ry는 좌측 하단의 sin함수가 음의 부호를 가진다.

    3차원 공간에서는 x -> y -> z -> x -> y의 순서로 세 축이 순환되기 때문에 
    y축에 직교하는 평면은 xz평면이 아닌 zx평면이다.

    각 지저 축의 회전행렬을 구했다면 최종 행렬을 만들어야 하는데 총 6가지 경우가 생긴다.

    예로 z -> x -> y (롤 -> 피치 -> 요)의 순서를 채택했다면 (언리얼 엔진의 오일러 각도 동일한 순서이다)

    R = Ryaw * Rpitch * Rroll, 의 최종 회전행렬을 만들 수 있다.

    yaw, pitch, roll 각의 값을 각각 a, b, c라고 한다면

                        ㅡ               ㅡ  ㅡ             ㅡ   ㅡ              ㅡ
                        |  cos a 0  sin a | | 1 0       0    |  | cos c -sin c 0 |
    Ra * Rb * Rc =      |     0  1    0   | | 0 cos b -sin b |  | sin c  cos c 0 |
                        | -sin a 0  cos a | | 0 sin b  cos b |  |   0     0    1 |
                        ㅡ               ㅡ  ㅡ             ㅡ   ㅡ              ㅡ 

                        ㅡ                                                                                                  ㅡ
                        |  cos a * cos c + sin a* sin b * sin c     -cos a * sin c + sin a * sin b * cos c      sin a * cos b |
                 =      |  cos b * sin c                            cos b * cos c                               -sin b        |
                        | -sin a * cos c + cos a * sin b * sin c    sin a * sin c + cos a * sin v * cos c       cos a * cos b |
                        ㅡ                                                                                                   ㅡ 

    이 회전행렬의 열벡터는 표준기저벡터가 회전변환된 로컬 축을 의미한다.
    겱국 오릴러 각으로 변환된 각 로컬 축의 값은 이렇게 계산할 수 있다.

    Xlocal = (cos a * cos c + sin a * sin b * sin c, cos b * sin c, -sin a * cos c + cos a * sin b * sin c)
    Ylocal = (-cos a * sin c + sin a * sin b * cos c, cos b * cos c, sin a * sin c + cos a * sin v * cos c)
    Zlocal = (sin a * cos b, -sin b, cos a * cos b)

    이렇게 얻은 로컬 축 벡터는 게임 로직에도 사용가능하고 렌더링 로직에 필요한 회전행렬도 바로 만들 수 있따.
    각 X, Y, Z 로컬 축 벡터를 A = (Ax, Ay, Az) 등으로 나타낸다면 아래와  같이 만들 수 있다.
        ㅡ          ㅡ
        | Ax Bx Cx 0 |
    R = | Ay By Cy 0 |
        | Az Bz Cz 0 |
        | 0  0  0  1 |
        ㅡ          ㅡ

    
*/
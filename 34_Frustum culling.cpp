/*
    절두체 표현(Frustum culling)

    평면의 방정식을 활용해 카메라의 시야 영역에서 벗어난
    게임 오브젝트들을 솎아내는 기능인 절두체 컬링을 구현한다.

    절두체의 평면을 무한하게 확장하면 평면의 원점을 품게된다.
    그러면 근평명과 원평면을 제외한 네 평면을 구성하는 평면의 방정식의
    d값은 0이므로 크기가 1인 법선 벡터만 구하면 근평면과 원평면을
    제외한 평면의 방정식을 얻을 수 있다.

    절두체의 상당 평면의 법선 벡터를 구하기 위해 뷰 공간의 측변에서
    평면의 좌표계를 보면 오른쪽 방향은 뷰 공간의 -z에 대응되고
    위쪽 방향을 y축에 대응된다.

    평면에서 오른쪽을 향하는 (0, 0, -1)의 벡터를 반시계 방향으로 각도/2 만큼 회전한 결과는
    (0, sin(각도/2), -cos(각도/2))가 된다.
    그러면 법선 벡터는 90도 더 회전한 값이므로 y값과 z값을 교차시키고 y값에
    반대 부호를 취하면 얻을 수있따.

    d 값은 0이므로 절두체 평면의 법선 벡터 n은
    
    0 = cos(각도/2) * y + sin(각도/2) * z, 절두체 상당 평면 방정식
    0 = -cos(각도/2) * x + sin(각도/2) * z, 절두체 하단 평면 방정식
    0 = cos(각도/2) * x + sin(각도/2) * z, 절두체 좌측 평면 방정식
    0 = -cos(각도/2) * x + sin(각도/2) * z, 절두체 우측 평면 방정식

    이 원점을 지나느 평면의 방정식이 된다.

    근평면의 방정식에선 원점으로부터의 거리가 b일때 
    d의 값이 n이 된다. 법선 벡터의 값은 (0, 0, 1)이다.

    근평면의 방정식이다.

    (0, 0, 1)*(x, y, z) - (0, 0, 1)*(0, 0, -n) = 0
    z + n = 0

    원평면의 방정식은 법선 벡터가 근평면에 반대 방향인 원점에서 멀어지는 (0, 0, -1)이며
    원점으로부터의 거리는 f라 한다.

    원평면의 방정식이다.

    (0, 0, -1)*(x, y, z) - (0, 0, 1)*(0, 0, f) = 0
    -z - f = 0

    평면의 방정식을 다룰 떄 주의할 점은 방향 정보가 수록되어 있기에
    함부로 수식을 옮기면 안된다.
    함부로 수식을 옮기는 경우 거리는 동일하지만 평면의 방향이 달라진다.

*/
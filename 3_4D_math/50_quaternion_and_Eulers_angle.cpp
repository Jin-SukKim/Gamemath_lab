/*
    사원수의 구성 요소 값은 직관적이지 않아 설계가 어렵다.
    3차원 공간에서의 물체의 회전을 설정할 때 오일러 각 방식이
    더 직관적이고 편리하기에 오일러 각의 값을 사원수로 변환해주는
    기능을 만들면 매우 유용하게 사용된다.

    오일러 각에서 사원수로의 변환
    
    오일러 각의 각 회전은 x, y, z 기저 축이 회전축의 역할을 수행한다.
    이것을 사원수로 표현해준다.

    3차원 공간에서 x축을 중심을 각 θ만큼 회전하는 회전 사원수 q
    q = (cos (θ/2), sin (θ/2) * x) = cos (θ/2) + sin (θ/2) * i

    따라서 오일러 각을 구성하는 roll, pitch, yaw 회전에 대응하는 각 사원수
    qroll, qpitch, qyaw는 다음과 같다.

    qroll = cos (θrool / 2) + sin (θroll/2) * k
    qpitch = cos (θpitch / 2) sin (θpitch / 2) * i
    qyaw = cos(θyaw / 2) + sin (θyaw / 2) * j

    오일러 각의 회전 순서를 roll, pitch, yaw 순으로 적용했었다.
    대응하는 사원수도 동일한 순서에 맞춰 곱하면 오일러 각에 대응하는 사원수가 만들어진다.

    yaw, pitch, roll을 각각 y, p, r로 표기한다.
    sin 값을 sy, sp, sr, cos값을 cy, cp, cr로 지정한다.
    
    qroll * qpitch * qyaw = cr * cp * cy + sr * sp * sy +
                            (cr * sp * cy + sr * cp * sy)i +
                            (cr * cp * sy - sr * sp * cy)j +
                            (sr * cp * cy - cr * sp * sy)k

    반대로 사원수에서 오일러 각으로의 변환

    실수부를 w, 허수부를 각각 x, y, z로 치환한다.
    yaw, pitch, roll을 각각 y, p, r로 표기한다.
    sin 값을 sy, sp, sr, cos값을 cy, cp, cr로 지정한다.

    2(wz + xy)를 계산한 결과

    w = cr * cp * cy + sr * sp * sy
    z = sr * cp * cy - cr * sp * sy
    wz = (cy)^2 * cr * (cp)^2 * sr - cy * (cr)^2 * cp * sy *sp +
         cy * cp * sy * (sr)^2 * sp - cr * (sy)^2 * sr * (sp)^2
    x = sy * sr * cp + sp * cy * cr
    y = sy * cp * cr - sp * sr * cy
    xy = cr * (cp)^2 * (sy)^2 *sr - cy * cp * sy *(sr)^2 * sp +
         cy * (cr)^2 * cp *sy *sp - (cy)^2 * cr * sr * (sp)^2

    사원수에서 오일러 각을 구하려면 사원수를 잘 조합해 단일 각에 대한
    삼각함수가 나오도록 식을 설정해야한다.

    roll 회전에 대한 삼각함수를 만들어주는 wz + xy 값을 계산한다

    wz + xy = cr * (cp)^2 * sr - (cy * cp * sy * sp) + cy * cp * sy * sp - (cr * sr * (sp)^2)
            = cr * sr((sp)^2 - (sp)^2)
            = sin (2r) / 2 * cos (2p), 삼각함수의 배각 공식을 사용해 두 배의 각으로 변환

    2(wz + xy)의값은 sin θroll * cos θpitch가 된다.
    1 - 2(z^2 + x^2)를 계싼하면 cos θroll * cos θpitch가 된다.
    그럼 두 값을 나누면 roll 회전의 tan 값이 나온다.

    (sin θroll * cos θpitch) / (cos θroll * cos θpitch) = tan θroll 
    = 2(wz + xy) / (1 - 2(z^2 + x^2))

    roll 회전의 값은 arctan 함수를 사용해 구할 수 있다.

    θroll = atan2(2(wz + xy), 1 - 2(z^2 + x^2))

    pitch 회전각은 pitch 회전에 대한 삼각함수를 만드는 wx - yz 값을 통해 구한다.

    wx - yz = sin (θpitch / 2) * cos (θpitch /2) = 1/2 sin θpitch, sin 함수의 배각 공식으로 간략화

    즉 pitch 회전각은 arcsin 함수를 사용해 구할 수 있다.

    θpitch = asin(2(wx - yz))

    이때 주의점은 arcsin 함수의 정의역은 [-1, 1] 범위로 제한되어 있으므로 wx - yz 값이
    [-0.5, 0.5] 범위를 벗어나지 않는지 확인하고 벗어나는 경우 범위내 가장 가까운 값으로 설정한다.
    즉 -90도나 90도로 설정해준다.

    yaw 회전은 roll 회전과 유사한 방식으로 yaw 회전의 tan 값을 구한 수 arctan 함수를 사용한다.

    θyaw = atan2(2(wy + xz), 1 - 2(x^2 + y^2))

*/
/*
    오일러 각을 사용해 3차원 회전을 관리했지만 짐벌락 현상이 발생하고
    회전 보간이 어렵다는 문제가 있었다.

    하지만 오일러 각의 문제는 임의의 축에 대한 평면의 회전 방식을
    사용하면 해결이 가능하다.
    이 방식을 축-각 회전(Axis-Angle rotation)이라고 한다.
    3차원 공간에서 지정된 임의의 축에 직교하는 평면에서 회전이 진행되는 평태를 띤다.
    
    축-각 회전 공식을 내적과 외적을 사용해 유도할 수 있다.

    벡터 n = 회전이 발생하는 평면에 직교하는 법선벡터 (정규화로 크기 1)
    P = 회전시킬 점, P' = 각도만큼 회전한 최종점
    O = 월드 공간의 원점, O' = 회전 평면의 중심점

    P = (x, y, z, 1)
    벡터 u = 원점 O에서부터 회전시킬 점 P까지의 벡터
    즉 점 P와 벡터 u의 값은 마지막 차원의 값만 다를 뿐 (x,y,z)의 값은 동일하다.
    u = P - O = (x, y, z, 0)
    u' = 회전시킨 벡터
    임의의 축 n에 대해 벡터 u를 각도만큼 회전시켜 벡터 u'를 계산하는 축-각 회전 공식

    u' = cos각도 * u + (1 - cos각도) * (u * n) * n + sin각도 * (n X u)

    원점에서 회전시킬 점으로 향하는 벡터 u를 평면의 회전축에 해당하는 법선 벡터 n에 투영하면
    (u*n)*n이 된다. (정규화 시켜서 크기가 1이다.)
    
    투영벡터 v = (u*n)*n

    회전 평면의 중점 O'에서 점 P로 향하는 벡터는 두 벡터의 차가 되므로 u - v가 된다.

    이 벡터를 회전시킨 벡터 t 를 구하는게 목표이다.
    이 t 를 가로 성분과 세로 성분으로 분리하면, 가로 성분에 해당하는 벡터는
    벡터 (u - v)에 cos각도를 곱해서 얻을 수 있다.

    세로 성분의 벡터룰 구하는 것은 같은 방향으로 향하는 벡터가 필요한데
    법선 벡터 n과 벡터 (u - v)를 외적해서 얻을 수 있다.
    이를 벡터 w라 하면 w = n X (u - v)가 된다.

    벡터 w에 sin 각도를 곱하면 세로 성분에해당하는 벡터를 얻을 수 있다.

    t = cos 각도 * (u - v) + sin 각도 * w
       = cos 각도 * (u - v) + sin 각도 * (n X (u - v))
       = cos 각도 * (u - v) + sin 각도 * (n X u)
    (t = 평면에서 벡터를 회전시킨 벡터)

    최종적으로 원하는 벡터인 u'는 t에 벡터 v를 더해 얻을 수 있다

    u' = v + cos 각도 * (u - v) + sin각도 (n X u)

    로드리게스 회전 공식을 활용하면 오일러 각으로 구현하기 어려운 임의의 축에 대한 회전 변환을 수행할 수 있다.
    하지만 이 방식은 행렬로의 변환이 어려워 구축된 렌더링 파이프라인에 연동하기가 어렵다.
    따라서 로드리게스 회전과 동일한 긴으을 제공하며 간결하고 행렬로 변환이 가능한
    사원수(Quaterian) 을 사용한다.
*/
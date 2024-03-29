/*
    씬(scene) 구성요소
    
    모델링 행렬은 게임 오브젝트의 트랜스폼 정보로부터 설계한다.

    트랜스폼은 크기(S), 회전(R), 이동(T)의 세 가지 데이터로 구성된다.
    이 데이터는 세가지 아핀 변환행렬에 대응된다.

    크기(S): 2차원 벡터 (sx, sy)
    회전(R): 각도
    이동(T): 2차원 벡터(tx, ty)
            ㅡㅡ           ㅡㅡ
            |    sx  -0   0  |
    S =     |    0   sy   0  |
            |    0   0    1  |
            ㅡㅡ           ㅡㅡ

            ㅡㅡ                      ㅡㅡ
            |    cos각도    -sin각도  0  |
    R =     |    sin각도    cos각도   0  |
            |       0         0      1  |
            ㅡㅡ                      ㅡㅡ

            ㅡㅡ          ㅡㅡ
            |    1    0   tx |
    T =     |    0    1   ty |
            |    0    0   1  |
            ㅡㅡ          ㅡㅡ

    행렬 곱은 교환 법칙이 성립하지 않기 때문에 이 세가지 변환행렬은
    총 6가지의 곱하기 순서가 나온다.

    상황에 따라 알맞은 순서를 선택해야 하는데 이 곱의 결과는 모델링 행렬이 된다.

    이동을 먼저하고 회전 변환을 주는 것과 회전을 먼저한 뒤 이동을 하는 것은
    서로 다른 위치로 물체를 이동시킨다.

    이를 반영하면 6가지 수에서 2가지로 압축된다.

    그 다음은 크기 변환과 회전 변환 두 가지 중 어떤 변환을 먼저 할지 결정하는데
    이것도 회전을 한 후 크기를 변환 시키는 것과
    크기를 변환시킨 후 회전을 하는 것은 물체의 형태를 매우 다르게 변환 시킨다.
    
    회전 변환은 물체의 형태를 그대로 보존해주는 강체 변환(Rigid Transform)인데
    크기 변환을 해 물체의 형태를 확정시킨 다음 회전 변환을 주는 것이 
    사용자의 입장에서 가장 직관적이기 때문에 보편적으로 크기 -> 회전 -> 위치 순서로 이루어진다.

    즉 모델링 행렬은 
                    ㅡㅡ                                  ㅡㅡ
                    |    cos각도 * sx    -sin각도 * sy   tx  |
    M = T * R * S = |    sin각도 * sx    cos각도 * sy   ty   |
                    |       0               0            1  |
                    ㅡㅡ                                  ㅡㅡ
    와 같다.
*/
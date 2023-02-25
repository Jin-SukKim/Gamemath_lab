/*
    벡터로부터 회전행렬생성

    임의로 주어진 두 벡터에 직교하는 벡터를 생성하는
    외적의 성질은 카메라의 회전을 설정한느데도 사용된다.

    외적을 사용하면 카메라의 시선 벡터 정보로부터 카메라의 세 가지 로컬 축을 구하고 이로부터
    회전행렬까지 얻을수 있다.

    물체의 위치에서카메라 위치를 뺀 크기를1로 정규화 시킨 시선 벡처 v를 만들면
    이 벡터는 카메라 트랜스폼의 로컬 z축이 된다.

    로컬 x축은 Up Vector인 월드 공간의 y축과 카메라의 로컬 z축을 외적하면 얻을 수 있따.

    로컬 y축은 로컬 z축과 로컬 x축을 외적하면 구할 수 있따.

    정리하자면 시선 벡터 v와 주어지는 업벡터 u로 로컬 공간을 구성하는 세 기저벡터 x, y, z를 구할 수 있따.

    x = (u X z) / (|u X z|)     // 정규화시켜 벡터를 구한다. 

    y = z X x

    z = v / |v|     // 정규화 시켜 시선 벡터 v를 만든다

    카메라 트랜스폼의 회전행렬 R은 로컬 벡터를 열벡터로 지정해 생성할 수 있따.
            ㅡ          ㅡ
            | Xx Yx Zx 0 |
    R   =   | Xy Yy Zy 0 |
            | Xz Yz Zz 0 |
            | 0  0  0  1 |
            ㅡ          ㅡ

    주의할 점으로 카메라가 거꾸로 뒤집혀 있는 상황이 있을수도 있다.
    이 경우 월드 공간의 y축이 반대 방향인 (0, -1, 0)을 사용해야 된다.

    그러므로 외적 계산에 사용할 업벡터의 값을 입력받도록 설계하는 것이 안전하다.

    또 하나 주의할 점은 로컬 z축이 업벡터와 평행할 경우 외적 결과가
    영벡터가 되어 계산을 진행할 수가 없다.
    이 경우 외적을 계산하는 대신 로컬 z축과 직교하는 로컬 x축의 값을 수동으로 지정해야 된다.
    (아마 로컬 x축은 월드 공간의 x축인 라이트벡터(right vector)와 같게 해도 문제가 없지 않을까?)
*/
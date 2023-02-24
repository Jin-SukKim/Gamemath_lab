/*
    x, y, z축이 서로 직교하는 공간을 유클리드 공간(Euclidean space)라고 한다.
    로컬 공간, 월드 공간, 뷰 공간은 모두 유클리드 공간의 형태이다.
    그런데 정육면체 형태의 유클리드 공간은 원근 투영 변환에 의해 사각뿔 형태로 바뀌게 되었는데
    이것을 사영 공간(Projective space)라고 한다.

    사영 공간의 x, y축은 여전히 직교하기에 유클리드 공간과 동일한 성질을 가지지만
    z축은 독립적으롷 행동하지 않고 x, y축 모두에 영향을 준다.
    바로 초점 거리에 따라 x, y축이 만들어내느 투영 평면의 면적이 달라지는 이유이다.

    원근 투영 변환에 대응하는 행렬은 x, y, z축이 모두 직교하는 유클리드 공간과
    체계가 달라지기에 기즘까지의 표준기저벡터의 변화를 관찰하는 방법으로는 생성할 수 없다.

    문제를 단순화 하기 위해 x, y축을 번갈아가며 고정시킨 다름 투영 평면에 상이 맺히는 과정을 생각한다.
    뷰 공간의 점 Pview가 투영 평면에 투영된점을 Pndc라 할때 좌표는

    Pview = (0, vy, vz)
    Pndc = (0, ny) 이다. (x좌표 고정)

    닮은꼴 삼각형 두개를 그리면 

    ny:d = vy:-vz 란 비가 성립된다. (카메라 앞의 점의 z값은 항상 음수 이므로 밑변의 길이는 -vz가 된다.)
    d = 초점거리(카메라부터 Pndc까지의 최단거리, 근평면?)

    즉, ny = (d*vy) / (-vz), 식이 만들어 진다.

    카메라의 좌우상하의 시야각은 동일하므로 반대로 x 값은

    nx = (d*vx) / (-vz) 란 식이 만들어진다.

    따라서 초점거리와 뷰 좌표로부터 Pndc는 다음과같다.

    Pndc = (nx, ny) = ((d*vx) / (-vz), (d*vy) / (-vz)) = -(d/vz)(vx, vy)

    NDC 좌표를 계산했다면 모니터의 최종화면인 스크린 좌표는 화면 해상도만큼 가로와 세로를 늘려주면 완성된다.

    하지만 화면을 늘리면 화면의 비율이 1:1로 균등하지 않기에 물체가 찌그러져 보인다.
    이 화면의 가로세로 비를 종횡비(aspect ratio)라고 한다. (모니터는 보통 16:10, 4:3 비율등을 사용한다.)

    NDC영역에 종횡비를 거꾸로 뒤집은 비율을 적용해 먼저 찌그러트리면 해결된다.
    이 종횡비는 보통 하나의 축을 1의 크기로 지정하고 다른 축의 크기를 상대적으로 측정해 나타낸다.

    종횡비를 a로 표시하고 x축을 변경해 좌우로 찌그러트리면 역수 1/a를 x값에 곱해주면 된다
    종횡비 a = width / height

    Pndc = -d/vz (vx/a, vy) 가 된다.

    최종 NDC 값을 계산하는 원근 투영 행렬 P는 이렇게 설계할 수있다.
    Pview의 x, y값으로 만든 벡터 v = (vx, vy)
                    ㅡ                     ㅡ  ㅡㅡ
    Pndc =  P * v = |(1/a) * (d/-vz)  0     |*|vx|
                    |        0       d/-vz  | |vy|
                    ㅡ                     ㅡ  ㅡㅡ

    다만 문제가 하나 발생하는데 변환할 점의 z값이행렬에 사용되다 보니 
    변환할 점마다 항상 행렬을 새롭게 생성해야 한다는 점이다.

    행렬의 가장 큰 장점은 모든 변환의 행렬을 미리 곱해둔 행렬을 적용함으로써
    반복되는 연산량을 줄이는 것에 있었는데 이러면 장점이 없어지는것이다.

    따라서 원근 투영 행렬을 구성할 때 점의 값을 사용하지 않고 카메라 설정만으로 행렬을 만들어야 된다.

    투영 행렬을 보면 행렬의 구성요소를 모두 -vz값을 분모로 한다.
    그러면 행렬에서 -vz값을 제거하고 대신 행렬의 결괏값에서 -vz를 나누어주면 된다.

    원근 투영 행렬 P를 간단하게 만들고 행렬에 곱하는 벡터의 값을 
    v = (vx, vy, vz)로 지정해 뷰 좌표게의 점과 동일하게 만들어 준다.
           ㅡ        ㅡ ㅡ ㅡ    ㅡ          ㅡ
           | d/a 0  0 || vx |   | (d/a) * vx |
    P*v =  | 0   d  0 || vy | = |   d * vy   |
           | 0   0 -1 || vz |   |     -vz    |
           ㅡ        ㅡ ㅡ ㅡ    ㅡ          ㅡ

    이 행렬 곱에서 생성되는 벡터는 NDC 좌표와는 다르지만 원근 투영 행렬 P는
    점과 무관하게 카메라 설정 값으로만 구성된다.
    즉, 모든 점에 대해 보편적으로 설계된 행렬을 사용할 수 있다는 것이다.

    이렇게 원근 투영 행렬 P로 변환되는 좌표계를 클립좌표(Clip coordinate)라 불린다.

    Pclip = ((d*vx) / a, d*vy, -vz)

    이 클립 좌표의 점 Pclip의 각 요소를 Pclip의 세 번째 값인 -vz로 나누면 NDC의 좌표를 얻을 수 있다.

    Pndc = (((d*vx) / (a*-vz), (d*vy)/-vz, 1))

    하지만 모델링 행렬과 뷰 행렬에서 사용하는 행렬의 크기는 4 x 4 행렬이므로
    행렬 곱을 윟 ㅐ동일한 크기로맞춘다.
    마지막 네 번째 행과 열을 단위 벡터로 채우면 원근 투영 행렬이 완성된다.

            ㅡ          ㅡ 
           | d/a 0  0  0 |
    P   =  | 0   d  0  0 |
           | 0   0 -1  0 |
           | 0   0  0  1 |
           ㅡ           ㅡ
*/
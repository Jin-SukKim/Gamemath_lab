/*
    동차 좌표계(Homogenous coordinate system)

    NDC는 2차원 평면의 좌표지만, 모든 점에사용 가능한 원근 투영 행렬을 사용하도록
    계산 과정을 두 단계로 구분하고 사용하는 벡터의 값도 한 차원 높였다.

    이렇게 한 차원 높인 벡터를 사용하는 것을 게임 제작에서는 보통
    동차 좌표계(Homogenous coordinate system)을 사용한다고 말한다.

    동차 좌표계의 동차는 모든 항의 차수가 같음을 의미하는 수학 용어다.

    사영 공간에서 점과 투영된 점의 좌표는 카메라로부터 멀어질수록
    원점에 가까워지고, 가까워질수록 커지는 반비례 관계를 가진다.

    3차원 사영 공간의 점을 (x', y', z')로 표기하고해당 점이
    투영된 NDC 좌표를 (x, y)로 표기해 보면 NDC 좌표값은 사영 공간의
    마지막 차원 값 z'에 반비례로 영향을 받는다.

    x = x' / z', y = y' / z'

    NDC 공간에 직선을 그으면 y = ax + b
    이 직선이 실은 사영공간의 점들이 투영되어 만들어졌다고 생각한다.
    그렇다면 직선의 방적식을 사영 공간의 좌표로 표현했을 때 사영 공간의 좌표로
    표기한직선의 방정식은 다음과 같다.

    y' / z' = a*(x'/z') + b

    양변에 z'를 곱해주면 세 미지수의 차수가 모두 1차식으로 동일한 수식이 구성된다.

    y' = ax' + b

    이렇게미지수에대한 차수가 모두동일한 방정식을 동차 방정식이라고 부르며
    이런 이유로 사영 공간이 사용하는 좌표계를 동차좌표계라고 불린다.

    원근 투영 행렬 P를 설계하기 위해 계산 과정을두 단계로 나눴는데
    1단계에서 구한 좌표를 클립좌표라불르며 투영 되기 전의 사영 공간의 좌표를 의미한다.
    즉, 사영 공간, 클립 공간 동차 공간은 모두 동일한 공간을 가리키고,
    클립좌표, 동차 좌표 역시 동일한 좌표계를 가리킨다

    사영 공간의 점이카메라로부터 멀어질수록투영된 NDC 좌푯값은 원점 (0,0)에 가까워진다.
    NDC의 원점은 소실점(Vanishing point)에 해당한다.

*/
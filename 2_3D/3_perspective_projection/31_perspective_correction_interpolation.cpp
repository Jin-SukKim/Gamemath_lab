/*
    투영 보정 보간 (Perspective correction interpolation)

    depth 값까지 적용해준 wireframe에 텍스쳐를 입히면 원하는데로 
    입혀지지 않고 얼굴이 쳐지거나 올라가있다.

    텍스쳐를 입힐 때 NDC에서 무게중심좌푤르 계산해서인데
    사영 공간에서 NDC 공간으로 변환할 때 사영공간의 마지막
    요소 w의 값 -vz를 나눴기 때문이다.

    결국 사영 공간과 NDC 공간 사이에 형성된 반비례관계로부터 기인한것이다.

    이를 바로잡기 위해 투영되기 전 사영 공간에서 무게중심좌표를 사용해야 한다.
    투영 과정을 거꾸로 추적해 NDC에서 구한 무게중심좌표로부터
    사영 공간의 무게중심좌표를 계산해야 한다.
    이 과정을 투영 보정 보간이라고 하낟.

    이 과정을 유도하기 위해 반비례함수 y = -1/x의 성질을 이용하면 된다.

    x축 2, 4, 6에 대응된 y -1/2, -1/4, -1/6이 있을 때 x축의 세 수중 가운데 위치한
    4의 무게중심좌표 a는 0.5이다.

    4 - a*2 + (1 - a)*6

    4에 대응하는 y축의 값 -1/4의 무게중심좌표는 0.25이다.

    -1/4 = a*(-1/2) + (1-a)*(-1/6)

    y축의 무게좌표 0.25로부터 x축의 무게중심좌표 0.5를 계산하는 식은 결국
    NDC의 무게중심좌표에서 사영 공간의 무게중심좌표를 찾는 공식일 것이다.

    x와 y축에 두 점이 있다고 가정하고 무게중심좌표를 구하는 식을 만들어 본다.
    무게중심좌표의 정의에서 두 무게중심좌표의 합 q1 + q2의 값은 1이다.
    두 점 y1과 y2사이의 점 y'를 구하는 수식, x1과 x2의 사이 x'를 구하는 수식

    y' = q1*y1 + q2*y2
    x' = t1*x1 + t2*x2
    일때 x'와 y'는 반비례 관계이므로 y를 x값으로 표현한다.

    1/x' = q1*(1/x1) + q2/(1/x2)
    x' = t1*x1 + t2*x2

    두 식을 이용해x' 값은 구한다면

    x' = 1 / (q1 * (1/x1) + q2 * (1/x2))
    x' * (q1 * (1/x1) + q2 * (1/x2)) = 1
    q1 * (x' / x1) + q2 * (x' / x2) = 1

    두 무게중심좌표의 합은 1이므로

    q1 * (x' / x1) + q2 * (x' / x2) = t1 + t2
    t1 = q1 * (x' / x1), t2 = q2 * (x' / x2)  가 된다.

    x값에 2, 6을 q1, q2값에 y의 무게중심ㅈ 좌표인 1/4, 3/4를 적용하면 
    t1과 t2는 0.5가 나온다.

    NDC에서 구한 무게중심좌표를 사영 공간의 무게중심좌표로 변환한다
    세점을 사용하고 NDC로 변활될 때 나누는 ㄱ밧은 뷰 공간의 z값이므로, 
    x를 -z로 치환하면 최종 투영 보정 보간의 식을 얻을 수 있따.

    z' = 1 / (q1 * (1/z1) + q2 * (1/z2) + q3 * (1/z3))
    t1 = q1 * (1/z1), t2 = q2 * (1/z2), t3 = q3 * (1/z3) 가된다

    이 수식을 이용해 이상해지는 텍스쳐를 제대로 입히는 것을 
    원근 보정 매핑(Perpective correction mapping)이라고 한다.

*/
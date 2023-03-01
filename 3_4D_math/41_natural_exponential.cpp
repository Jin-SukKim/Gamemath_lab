/*
    ㅔㄹ온하르트 오일러는 실수와 허수와의 관계에서 더 나아가
    삼각함수와 자연지수함수와의 관계를 나타내는 오일러 공식을 발표했다.
    이 공식은 매우 중요한 전기공학의 신호 처리(signal processing)의 공식이며
    3차원 공간의 회전 문제를 해결하는 징검다리 역할도 해준다.

    무리수 e와 허수 단위 i, 그리고 삼각함수와의 관계를 이용해 나타낸
    오일러 공식이다.

    e^i각도 = cos각도 + i sin각도

    좌변의 자연지수함수 f(x) = e^x와 우변의 두 삼각함수의 미분을 이해하고
    급수로 표현하는 과정을 알아야 한다.

    자연지수함수에 있는 특별한 상수 e는 무리수 e라고 한다

    수학자 야코프 베르누이는 y = (1 + 1/x)^x 란 식을 통해
    복리로 얻을 수 있는 수익을 연구했는데, 굉장히 큰 값을 x에
    대입할수록 결괏값은 특정 상수에 근접한다는 사실을 알아냈다.

    x 값이 증가하면 y값도 증가하나 y값의 증가량이 서서히 줄어든다.
    x가 커질수록 2와 3사이에 있는 어떤 특정한 수에 근접하게 된다.
    이 값은 약 2.6172717..에 근접하는데 이 수를 무리수 e라고 부른다.

    무리수 e는 오일러 상수 e, 상수 e, 자연 상수, 자연 로그 밑등으로 불린다.

    이 무리수 e는 극한(Limit)과 무한대의 개념을 사용해 식으로 표현한다.

    e = lim x->무한 (1 + 1/x)^x

    무한대는 특정 수를 가르키는게 아닌 어떤 실수보다 큰 살태를 의미한다.
    극한이란 어떤 값 x가 지정한 값 a에 한없이 가까워질 때 함수 f(x)가 
    한없이 가까워지는 값 L을 의미한다.

    L = lim x->a f(x)

    극한의 결괏값이 특정한 값에 한없이 가까워지면 이를 어떤 값에 수렴한다(Converge)라고한다.
    반대로 무한대로 증가하거나 여러 값들이 오가면 발산한다(Diverge)라고 한다.

    한없이 커지는 x를 1/h로 바꾸면 0으로 수렴하면 무리수의 극한식을 쓸수있따.
    e = lim h->0 (1 + h)^(1/h)

    자연지수에 대해 알아보자

    지수란 거듭제곱에서 곱하는 횟수를 말한다(exponent), 곱하는 수는 밑(Base)라고 불린다.
    이런 연산의 특집을 지수법칙이라 한다.

    무리수 e를 밑(Base)로 다루는 지수법칙 3가지가 있다.
    f(x) = a^x, 지수함수

    1. a^m * a^n = a^(m+n)

    2. (a^m)^n) = a^mn

    3. a^0 = 1

    이 법칙에 따라 x값이 0이면 출력은 항상 1이다.
    그러므로 밑이 0보다 큰 지수함수의 크래프는 언제나 좌표 (0, 1)을 지난다.

    무리수 e를 밑(base)로 하는 지수함수를 자연지수함수라고 한다.

    f(x) = e^x
    언제나 (0, 1)을 지나며 x가 커질수록 급격히 증가한다.
*/
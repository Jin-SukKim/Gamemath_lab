/*
    급수(Series)

    오일러 공식에 사용되는 자연지수함수와 두 삼각함수의 미분은
    무한번 미분 가능하다는 공통점을 가졌다.
    이를 무한 급수로 표현되면 오일러 공식의 실마리가 풀린다.

    이전에 등비수열(Geometrix sequence)를 알아야 한다.

    수열은 규칙에 따라 순서에 맞게 수를 나열한 것이다.
    자연수집합과 유사하나 집합은 순서의 개념이 없고 중복을 허용하지 않는다.
    이 중에서도 연속된 항들이 일정한 비(Ratio)로 증가하는 수열을
    등비수열이라고 한다.

    등비수열 규칙에 사용된 비를 공비(Common Ratio)라고 한다.
    ex) 1/2, 1/4, 1/8 ..., 연속된 두 항이 1/2배씩 증가하는 규칙, 공비 = 1/2

    수열의 첫 번째 값을 초항(First term)이라 부르며 a로 표기한다.
    공비는 r, n번째 항은 an으로 표기

    등비수열 수식, an = ar^(n-1)
    등비수열의 n+1번째 항과 n번째 항에 공비를 적용하면 다음의 관계가 성립한다.

    a(n+1) = an * r

    급수는 수열의 개념을 확장해 수열의 모든 값을 더한 것이다.
    초항 a0과 n개의 요소로 구성된 수열의 급수는 시그마 기호를 활용해 표현한다. 
    
    등비수열의 급수

    ∞ ∑ k=0 a*r^k 와 같이 표현할 수 있다, k가 0부터 시작해 무한으로 커진다는 의미

    등비수열의 급수를 특별히 기하급수(Gerometric Series)라고 한다.
    기하급수는 무한대로 계쏙 증가하거나 특정 수로 수렴하는 성질이 있다.
    ex) 공비가 1/2인 등비수열의 급수가 어떤 값 s에 수렴한다.
        s = 1/2 + 1/4 + 1/8 ...
        1/2 * s = 1/2 * (1/2 + 1/4 + 1/8 ...)

        위 두식을 빼면

        1/2 * s = 1/2가 남는다.
        이 식을 만족하려면 s는 1이어야 하므로 급수 값은 1에 수렴한다.
        그래프로 표현한다면 지그재그 모양을 하고있다.

    기하급수의 요소는 무한하지만 이를 모두 더한 값은
    가로와 세로의 길이가 1인 정사각형의 넓이 1에 수렴한다.

    기하급수 구하는 과정을 일반화시켜 정리한다.
    등비수열의 초항을 a, 공비가 r일때 n개의 유한한 등비급수를 sn으로 표현한다.

    sn = a + ar + ar^2 .... + ar^n-1
    r * sn = ar + ar^2 + ... + ar^n, 양 변에 공비 r 곱해주기

    위 두식을 빼면
    sn - r*sn = a - ar^n 이 나온다.

    sn(1 - r) = a(1-r^n)
    sn = a(1-r^n) / (1 - r)

    사용할 기하급수는 무한 개의 요소를 가지므로 n에 무한대의 극한을 설정한다.

    lim n->∞ sn = lim n->∞ [a(1-r^n) / (1 - r)]
                = a / (1 - r) * lim n->∞ a(1-r^n), 극한의 성질 2
                = a / (1 - r) - a / (1 - r) * lim n->∞ r^n, 극한의 성질 1

    lim n->∞ sn의 극한값을 구하려면 공비 r이 가질 수 있는 값을 
    여러 개로 분리하고 각각의 극한을 생각해야한다.
    
    공비 r이 1이면 a / (1 - r)의 분모가 0이 되 극한값을 구할 수 없다.
    공비 r이 1인 무한급수의 경우 a를 무한 번 더한 식이 되 급수 값은 무한대로 발산한다.
    sn = a+a+a+a+a+a+a+a+...

    공비 r이 1이 아닌 경우 a / (1 - r)가 상수가 되 lim n->∞ r^n의 값에 따라 극한값이 결정된다.

    공비 r이 1보다 큰경우, |r| > 1, 공비는 곱할수록 크기도 계속 커져 lim n->∞ r^n의 극한값은 발산(Diverge)한다.
    
    공비 r의 크기가 1보다 작다면, |r| < 1, 극한값이 0으로 수렴한다.

    공비 r이 -1이면 lim n->∞ r^n의 값이 일정한 값을 못가져 규칙적으로 1과 -1값을 오고간다.
    이 현상을 진동한다(Oscilate)라고 표현하는데 특정 값으로 수렴하지 않으므로 발산으로 취급한다.

    lim n->∞ sn의 성질(등비급수의 극한값)

    1. r = 1인 경우 발산한다.
    2. |r| > 1인 경우 발산한다.
    3. |r| < 1인 경우 수렴한다.
    4. r = -1인 경우 발산한다.

    기하급수에서 좀 더 확장한 형태의 급수인 멱급수(Power Series)가 있다.
    멱급수는 기하급수처럼 모든 항의 계수 a의 값이 같지않고 항마다 계수가 다른 급수도 있다.

    ∞ ∑ n=0 an*r^n = a1 + a2r + a3r^2 ... an*r^n-1 + ...., 멱급수

    즉 기합급수는 모든 계수의 값이 동일한 멱급수의 한 종류이다.
    
    멱급수도 기하급수와 동일하게 특정 조건에 따라 수렴하거나 발산하는데
    이를 판정하기 위한 비판정법(Ratio test)가 있따.
    이것은 항의 계수가 일정한 규칙으로 전개되는 경우, 다음의 극한값을 구해 파악하는 방법이다.

    L = lim n->∞ |(an+1 / an)|

    3가지 경우

    1. L의 값이 1보다 작으면 급수는 언제나 수렴한다.
    2. L의 값이 1보다 크면 급수는 언제나 발산한다.
    3. L의 값이 1이면 수렴할 수도, 발산할 수도 있다.
    
    기하급수는 모든 계수의 값이 동일한 a이고 공비가 r인 멱급수의 형태이다.

    ∞ ∑ n=0 a*r^n

    이에 비판정법을 정용하면 결과 값은 n과 무관하게 |r|이 나온다.

    L = lim n->∞ |(a * r^(n+1) / (a * r^n))| = |r|
    
    급수가 수렴하기 위해 L의 값이 1보다 작아야하는데 |r| < 1과 같다.
    기하급수의 수렴하기 위한 조건과 같다.

    이것처럼 멱급수가 수렴하기 위해 r이 가져야 할 범위를 수렴구간이라하며,
    범위의 절반인 1의 값을 수렴반지름(Radius of convergence)라 한다.

    각 항의 계수가 서로 다른 멱급수의 수렴 조건

    ∞ ∑ n=0 r^n / n = x + 1/2r^2 +1/3r^3 ...

    비판정법을 적용한다

    L = lim n->∞ |(r^+1 / (n + 1)) / (r^n / n)|
      = lim n->∞ |r| * n / (n+1)
      = |r| * lim n->∞ ((n + 1) - 1) / (n + 1)
      = |r| - |r| * lim n->∞ 1 / (n + 1)
      = |r|

    수렴하기 위한 조건은 L = |r|이 된다.
    즉, 멱급수 또한 기하급수와 동일한 수렴반지름을 가진다.
*/
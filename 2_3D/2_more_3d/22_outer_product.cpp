/*
    벡터의 내적은 모든 차원의 벡터에 적용할 수 있지만
    외적은 3차원 공간의벡터에서만 사용가능한 연산이다.

    외적은 회전의 순환 순서에 맞춰 벡터를 순서대로 나열하는 형태이고
    외적의 결과는 항상 3차원 벡터가 된다.
    이는 연산 결과가 항상 스칼라로 나오는 내적과 다르다.

    u = (Ux, Uy, Uz), v = (Vx, Vy, Vz)

    u X v = (Uy*Vz - Vy*Uz, Uz*Vx - Vz*Ux, Ux*Vy - Vx*Uy)

    외적 계산식의 패턴은 x 성분의 결과를 만들기 위해 x와 관련없는
    나머지 두 성분 y와 z를 결합해 만든다는것이다.

    이것도 항상 같은 성분만 사용하는 내적과 대비된다.

    외적은 뺄셈을 사용하기에 교환법칙이 성립하지 않는다.
    뺄셈에서 두 수의 순서를 바꿔 계산하면 반대수가 나오는 것처럼
    외적도 순서를 바꿔연산하면 반대 방향의벡터가 나온다.

    ex)
        a-b = -(b-a)
        u X v = -v X u

    외적은 결합법칙도 성립하지 않는다.

    u X (v X w) != (u X v) X w

    하지만 덧셈에 대한 분배법칙은 성립한다.

    u X (v + w) = u X v + u X w

    외적과 내적의 차이

                내적            외적

    계산결과    스칼라          벡터
    교환법칙    성립함          성립하지 않음
    결합버칙    성립하지않음    성립하지않음
    분배법칙    성립함          성립함
    연산방법    같은 위치의     다른 위치의 요소만 사용
               요소만 사용

    서로 대립되는 내적과 외적의 성질은 서로 상호보완하는 기능으로 활용된다.
*/
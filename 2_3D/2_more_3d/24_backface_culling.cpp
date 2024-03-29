/*
    게임은 실시간으로 빠르게 렌더링 처리해야 하기 때문에
    시선에 감지되지 않는 메시(Mesh)의 뒷면(Backfase)는 그리지 않고 건너뛰는 것이 효과적이다.
    이렇게 카메라와 마주보지않는 뒷면을 생략하는 기법을 백페이스 컬링(Backface culling)이라고 한다.

    Backface culling은메시의 삼각형을 구성하는 세 정점의 외적을 활용해 구현할 수 있다.

    삼각형의 세 점을 지정하는 인덱스 버퍼에는 점의 순서가 나열되어 있다.
    이것을 사용해 외적 계산을하면 삼각형의 방향을 지정하지 않고도
    삼각형이 향하는 방향을 파악할 수 있따.

    이렇게 정한 삼각형의 방향과 카메라의 시선 방향을 대조해 서로 마주보면
    삼각형을 그리고, 같은 방향을 바라보면 그리기를 생략하는 것이
    Backfase culling의 알고리즘이다.

    해당 면이 카메라와 마주보는지 확인하는 건 내적을 사용한다.
    뷰 공간에서 카메라의 시선 방향은 -z축이므로 (0, 0, -1)과
    내적을 수행한 결과가 음수일 때만 그리면 된다.
*/
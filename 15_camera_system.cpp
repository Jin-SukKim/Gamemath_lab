/*
    게임 콘텐츠의 무대가 되는 월드 공간은 대체로 넓은 역역이다.
    최초 씬을 구축할 떄 넓은 영역에 많은 오브젝트를 배치하지만
    화면에서는 월드 공간의 원점을 기준으로 한정된 공간만 나타낸다.

    화면 밖의 영역을 보기 위해서는 화면에 대응하는 카메라 게임 오브젝트를 새롭게
    만들고 월드 공간에 배치된 카메라를 중심으로 화면이 보이도록 기능을 만들어야 된다.

    카메라(Camera)는 자신이 출력할 화면의 해상도정보를 가지고 월드의 일부를 그려낸다.
    이 화면 크기 정보를 뷰포트(Viewport)라고 부른다.

    이 카메라에 설정된 뷰포트 정보를 바탕으로 월드 공간의 일부분을 렌더링한다.
    이를 위해 카메라를 중심으로 물체의 트랜슾모을 재조정하는 작업이 필요한데,
    카메라를 중심으로 변환한 공간을 뷰 공간(View space)라고 한다.

    모델링 행렬(M)은 로컬 공간의 좌표를 월드 공간의 좌표로 변환해주는 행렬이다.
    이와 같이 월드 좌표를 카메라 중심의 좌표로 변환하는 행렬이 있는데
    이것을 뷰 행렬(V)라고 한다.

    월드 공간과 뷰 공간의 관계를 생각했을 때 카메라 중심에서 월드 원점의
    상대 좌표를 구할 수 있다.(cx, cy)
    만약 월드 공간에 설정된 오브젝트의 위치 좌표가(x, y)일 때
    이 좌표에 상대 좌표를 더해주면 뷰 공간의 좌표를 얻을 수 있음을 의미한다.
    (cx + x, cy + y)

    카메라의 위치를 기준으로 측정한 월드 원점의 상대 좌표가 만약 (10, 10)일 때
    월드 공간에서 측정한 카메라 위치는 (-10, 10)임을 반전시켜 알 수 있는데
    이는 이동 행렬의 역행렬을 사용해 계산한다.

    즉 카메라에 트랜스폼이 설정된 경우, 여기서 이동 행렬의 역생렬을 계산하면 뷰 행렬이 완성된다.
        ㅡ       ㅡ
        | 1 0 -tx |
    V = | 0 1 -ty |
        | 0 0  1  |
        ㅡ       ㅡ

    뷰 행렬 V와 모델링 행렬M을 곱한 행렬 VM은 로컬 공간을 뷰 공간을 변환하는 기능을 수행한다.
    행렬 VM에 메시의 정점을 곱하면 모든 정점의 위치는 카메라를 중심으로 재배치 된다.

    Vview = V * M * Vlocal, Vview = 뷰 공간의 좌표, Vlocal = 로컬 공간의 좌표0
*/
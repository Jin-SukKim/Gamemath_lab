/*
    스켈레탈 애니메이션

    캐릭터 애니메이션은 가상의 뼈대인 본(Bone)을 캐릭터 메시에 심은 후,
    해당 본의 움직에 맞춰 캐릭터 메시가 변형되는 방식이다.

    이것을 스켈레탈 애니메이션(Skeletal animation)이라 한다.

    메시 체계를 확장해 본을 추가해야하나다.
    본은 단순 이동뿐만 아닌 회전, 크기 변경도 되므로 트랜스폼에서 관리한다.

    본의 구성요소

    1. 바인드포즈(Bindpose) :
        메시에 본이 심어질 때 본의 배치 정보는 트랜스폼으로 저장되는데
        최초의 배치 정보는 향후 본이 움직일 떄 상대적인 변화량을
        파악하는 기준으로 사용된다.

    2. 변화하는 본의 트랜스폼 정보를 저장할 공간 :
        시간에 따라 본의 트랜스폼이 변화되면서
        본에 연결된 메시들이 변화하며 캐릭터 애니메이션이 진행된다.

    3. 본을 식별할 수 있는 고유한 이름 정보

    두 종류의 메시

    1. 본이 있는 메시 (Skinned mesh)
        - 애니메이션이 필요한 캐릭터 메시
    2. 본이 없는 메시
        - 애니메이션이 없는 고정된 메시(배경 등)

    메시에 본 정보를 추가한 후에는 본의 움직임에 따라 메시의 정점이
    함계 움직이도록 본과 정점을 연결해야한다.
    이 작업을 리깅(Rigging)이라 한다.
    즉, 뼈에 살을 붙이는 작업과 같다.

    데이터 관점에선 하나의 정점에 대해 어떤 본들이 영향을 미치는지 기록하는 것이다.
    정점에 영향을 미치는 본이 많을수록 메시는 세심하게 변화한다
    하지만 계산량이 늘어나 성능과 품질 사이에 정점에 연결된 본의 수를 적적하게 조절해야한다.

    리깅을 위해 메시의 구조를 확장시킨다.
    정점마다 몇 개의 본으로부터 영향을 받는지 개수를 지정하고,
    영향을 주는 본들은 서로 얼마나 영향력을 주는지 그 비율에 대한 별도의 정보가 필요하다.
    정점에 연결된 본의 모든 정보를 담고, 동일한 개수로 각 본들이 가지는 영향력을 순서대로 저장한다.

    한 정점에 영향을 주는 본들의 연결 정보를 웨이트(weight)라고 한다.
    이 영향력의 값들은 계산상의 편의를 위해 모든 영향력의 총합은 1이 되도록 지정하는게 일반적이다.

    본의 움직임을 구현하기 위해, 게임 엔진은 시간에 따라 값의 변화를
    저장한 키프레임(Keyframe) 데이터를 사용한다.
    키프레임은 점이 찍힌 주요 지점에서 값을 지정하면 나머지 중간 값은
    관련 수식을 통해 보간하여 지정한 시간 동안 끊김 없는 데이터를 제공하도록 구성된다.

    캐릭터 애니메이션은 게임 오브젝트의모든 상태가 최종 결정된 
    게임 로직이 완료된 시점에서 진행되어야 한다.

    ex) 숨쉬기와 걷기 애니메이션이 설정되있으면 y축 입력을 처리하기 전
        캐릭터가 멈춘 것을 판단해 숨쉬는 모션을 재생하며 앞으로 전진한다.

        update3d -> lateUpdate3D -> render3d 워크플로우에선
        lateupdate3d에서 애니메이션을 처리한다.

        update3d : 현재 프레임에서 모든 게임 오브젝트의 상태를 확정
        lateupdate3d : 확정된 게임 오브젝트의 상태를 바탕으로 애니메이션 수행
        render3d : 움직인 본을 참고해 메시 정점을 변환해 렌더링
    
    정점 버퍼의 데이터를 행렬로 바꾸기 전, 본의 움직임을 반영해 최종 위치를 계산한다.




*/
/*
    바운딩 볼륨(Bounding volume)

    절두체 컬링이 잘 동작하지만 카메라를 움질일 때 화면 가장자리에 있는
    오브젝트가 갑자기 사라지거나 튀어나오는 현상이 발생한다.
    원인은 오브젝트의 메시가 차지하는 공간 영역이 있음에도 오브젝트의
    기준 위치만 가지고 절두체 컬링을 수행했기 때문이다.

    즉, 오브젝트가 절두체 영역에 걸쳐있지만 오브젝트의 위치는
    절두체 바깥에 있으므로 없어지는 것이다.

    결국, 오브젝트의 위치를 대상으로 하지 않고, 메시가 차지하는 영역을
    감안해 절두체 컬링을 진행해야 한다.

    메시의 영역을 효과적으로 관리하기 위해 구(Sphere)나 박스(Box)같은
    원시 도형(Primitive shape)을 사용하는데, 이러한 원시 도형으로
    설정한 공간 데이터를 바운딩 볼륨이라고 한다.
    (언리얼 엔진은 메시를 감싸는 노란색의 구와 파란색의 박스가 설정돼 있따.)

    구 바운딩 볼륨의 판점

    손쉽게 사용되는 원시도형인 구는 두 영역이 서로 겹치는지, 떨어져 있는지를
    가장 쉽고 빠르게 파악할 수 있는 도형이다.

    구의 중점에서부터 점까지의 거리와 구의 반지름의 크기를 비교해 점이
    구의 외부에 있는지 여부를 파악한다.

    d > r1

    두 구의 영역이 서로 떨어져있는지 여부는 두 구의 중점 간의 거리와
    두 구의 반지름을 더한 값을 비교하는 것으로 파악한다.

    d > (r1 + r2)

    메시의 모든 영역을 감싸는 구 영역을 생성할 때는 메시를 구성하는
    모든 점의 위치 값을 평균 내 중점 위치를 계산한 후, 중점에서
    가장 먼 점과의 거리를 구의 반지름으로 잡으면된다.

    구의 중점 좌표와 평면의 방정식의 법선 벡터 (a, b, c)와의 
    내적 값에 d값을 더한 값이 0보다 크다면 구는 ㅍ여면의 바깥쪽에 
    위치한다는 의미이다.

    이 값이구의 반지름 r보다 더 크다면 구의 영역은 평면으로부터 완전히 벗어난다.
    평면으로부터의 거리가 구의 반지름 r보다 작거나 같으면 구 영역은
    절두체의 평면과 겹쳐져 있다고 판다할 수 있다.

    절두체 컬링에 사용하는 구 바운딩 볼륨은 로컬 좌표를 기준으로
    생성된 데이터인데 절두체 컬링을 수행하는 공간은 뷰 공간이다.
    그래서 수동으로 구 바운딩 볼륨을 뷰 공간으로 변환하고 절두체 컬링을 진행했다.

    여태 뷰 공간에서의 영역 판정을 위해 원근 투영 행렬을 사용해
    평면의 방정식을 생성헀는데 원근 투영행렬 P, 클립 공간의 좌표 Vclip,
    뷰 공간의 좌표 Vview로 표기하면

    Vclip = (P)Vview 가 된다

    P 행렬을 구성하는 행벡터를 사용해 각 평면의 방정식을 추출했다.
    만약 뷰 공간의 좌표 대신 로컬 공간의 좌표 Vlocal을 사용하면,
    모델링 행렬 M과 뷰 행렬 V를 사용해 다음 수식이 성립된다.

    Vclip = (P * V * M) * Vlocal

    세 행렬 P, V, M을 곱한 값 역시 4x4 행렬이므로 이의 행벡터를 사용해
    평면의 방정식을 생성할 수 있으며, 만들어진 평면은 로컬 공간의 평면이된다.

    그러면 로컬 공간의 바운딩 볼륨 정보로 절두체 컬링을 수행하는 것이 가능하다.

    로컬 공간에서의 평면의 방정식을 생성하기 위해 P*V*M 행렬을 곱해 최종 행렬을 생성하고
    이로부터 6개의 평면을 추출한다.
    이렇게 만든 평면의 방정식은 메시에 저장된 바운딩 볼륨 정보와 바로 비교할 수 있으므로
    더욱 간편하게 절두체 컬링을 수행할 수 있다.

*/